#include "WiFiManager.h"

WiFiManager* WiFiManager::currentInstance = nullptr;

WiFiManager* WiFiManager::getInstance()
{
	if(currentInstance == nullptr)
	{
		currentInstance = new WiFiManager();
		Serial.println("[D]: WiFiManager instance created");
	}
	return currentInstance;
}

WiFiManager::WiFiManager()
{
	server = new AsyncWebServer(WEBSERVER_PORT);
	dnsServer = new DNSServer();
	config = ConfigManager::getInstance();
	ShelfDisplays = nullptr;
}

WiFiManager::~WiFiManager()
{
	delete server;
	delete dnsServer;
}

void WiFiManager::setDisplay(DisplayManager* display)
{
	ShelfDisplays = display;
}

bool WiFiManager::autoConnect(DisplayManager* display)
{
	setDisplay(display);
	return autoConnect();
}

void WiFiManager::stopAnimation()
{
	if(ShelfDisplays != nullptr)
	{
		ShelfDisplays->stopLoadingAnimation();
		Serial.println("Waiting for loading animation to finish...");
		ShelfDisplays->waitForLoadingAnimationFinish();
		ShelfDisplays->turnAllSegmentsOff();
	}
}

bool WiFiManager::autoConnect()
{
	if(ShelfDisplays != nullptr)
	{
		ShelfDisplays->setAllSegmentColors(config->getProperty<int>(ConfigManager::COLOR_CONFIG, WIFI_CONNECTING_COLOR_KEY));
		ShelfDisplays->showLoadingAnimation();
	}
	// attempt to connect; should it fail, fall back to AP
	WiFi.mode(WIFI_STA);

	if (connectWifi("", "") == WL_CONNECTED)
	{
		Serial.print("IP Address: ");
		Serial.println(WiFi.localIP());
		//connected
		stopAnimation();
		return true;
	}

	return startConfigPortal();
}

int WiFiManager::connectWifi(String ssid, String pass)
{
	if(ShelfDisplays != nullptr)
	{
		ShelfDisplays->setAllSegmentColors(config->getProperty<int>(ConfigManager::COLOR_CONFIG, WIFI_CONNECTING_COLOR_KEY));
	}
	Serial.println("Connecting as wifi client...");

	//fix for auto connect racing issue
	if (WiFi.status() == WL_CONNECTED)
	{
		Serial.println("Already connected. Bailing out.");
		return WL_CONNECTED;
	}
	//check if we have ssid and pass and force those, if not, try with last saved values
	if (ssid != "")
	{
		WiFi.begin(ssid.c_str(), pass.c_str());
	}
	else
	{
		if (WiFi.SSID())
		{
			Serial.println("Using last saved values");
			//trying to fix connection in progress hanging
			WiFi.disconnect();

			WiFi.begin();
		}
		else
		{
			Serial.println("No saved credentials");
		}
	}

	int connRes = waitForConnectResult();
	Serial.print("Connection result: ");
	Serial.println(connRes);
	return connRes;
}

uint8_t WiFiManager::waitForConnectResult()
{
	Serial.println("Waiting for connection result with time out");
	unsigned long start = millis();
	bool keepConnecting = true;
	uint8_t status;
	while (keepConnecting)
	{
		status = WiFi.status();
		if (millis() - start > CONNECTION_TIMEOUT)
		{
			keepConnecting = false;
			Serial.println("Connection timed out");
		}
		if (status == WL_CONNECTED || status == WL_CONNECT_FAILED)
		{
			keepConnecting = false;
		}
		delay(100);
	}
	return status;
}

void WiFiManager::setupConfigPortal()
{
	server->reset();


	#ifdef AP_PW
		WiFi.softAP(AP_SSID, AP_PW);
	#else
		WiFi.softAP(AP_SSID);
	#endif

	delay(500);

	/* Setup the DNS server redirecting all the domains to the apIP */
	dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
	dnsServer->start(DNS_PORT, "*", WiFi.softAPIP());

	server->serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
	// /* Setup web pages: root, wifi config pages, SO captive portal detectors and not found. */
	server->on("/", std::bind(&WiFiManager::handleRoot, this, std::placeholders::_1));
	server->onNotFound(std::bind(&WiFiManager::handleNotFound, this, std::placeholders::_1));
	AsyncCallbackJsonWebHandler* WIFIConfigHandler = new AsyncCallbackJsonWebHandler("/WIFISettings", std::bind(&WiFiManager::handleWifiSubmit, this, std::placeholders::_1, std::placeholders::_2));
	server->addHandler(WIFIConfigHandler);
	AsyncCallbackJsonWebHandler* baseConfigHandler = new AsyncCallbackJsonWebHandler("/BaseConfig", std::bind(&WiFiManager::handleSaveUnavailable, this, std::placeholders::_1, std::placeholders::_2));
	server->addHandler(baseConfigHandler);
	AsyncCallbackJsonWebHandler* colorConfigHandler = new AsyncCallbackJsonWebHandler("/ColorConfig", std::bind(&WiFiManager::handleSaveUnavailable, this, std::placeholders::_1, std::placeholders::_2));
	server->addHandler(colorConfigHandler);
	AsyncCallbackJsonWebHandler* hwConfigHandler = new AsyncCallbackJsonWebHandler("/HWConfig", std::bind(&WiFiManager::handleSaveUnavailable, this, std::placeholders::_1, std::placeholders::_2));
	server->addHandler(hwConfigHandler);
	server->begin(); // Web server start
	Serial.println("HTTP server started");
}

void WiFiManager::handleSaveUnavailable(AsyncWebServerRequest *request, JsonVariant &json)
{
	request->send(200, "text/plain", "ERROR: Changes not saved. Please connect to a WIFI network first.");
}

void WiFiManager::handleWifiSubmit(AsyncWebServerRequest *request, JsonVariant &json)
{
	JsonObject temp = json.as<JsonObject>();
	if(temp.containsKey("SSID") && temp.containsKey("PW"))
	{
		const char* SSID = temp["SSID"];
		const char* PW = temp["PW"];
		WIFI_SSID = String(SSID);
		WIFI_PW = String(PW);
		connect = true;
		request->send(200, "text/plain", "The device will now attempt to connect to \"" + WIFI_SSID + "\" Connection to the web interface will be lost.");
	}
	else
	{
		request->send(200, "text/plain", "ERROR: All two keys (SSID, PW are mandatory but at least one of them was missing.");
	}
}

void WiFiManager::handleRoot(AsyncWebServerRequest *request)
{
	if(captivePortal(request))
	{
		return;
	}
	request->send(SPIFFS, "/index.html", "text/html");
}

void WiFiManager::handleNotFound(AsyncWebServerRequest *request)
{
	if(captivePortal(request))
	{
		return;
	}
	request->send(SPIFFS, "/index.html", "text/html");
}

bool WiFiManager::startConfigPortal()
{
	if(ShelfDisplays != nullptr)
	{
		ShelfDisplays->setAllSegmentColors(config->getProperty<int>(ConfigManager::COLOR_CONFIG, WIFI_CONFIG_COLOR_KEY));
	}
	//setup AP
	WiFi.mode(WIFI_AP_STA);
	Serial.println("SET AP STA");

	connect = false;
	setupConfigPortal();

	while (1)
	{
		//DNS
		dnsServer->processNextRequest();

		if (connect)
		{
			connect = false;
			delay(2000);
			Serial.println("Connecting to new AP");

			if (connectWifi(WIFI_SSID, WIFI_PW) != WL_CONNECTED)
			{
				Serial.println("Failed to connect.");
			}
			else
			{
				//connected
				WiFi.mode(WIFI_STA);
				stopAnimation();
				break;
			}
		}
		yield();
	}

	server->reset();
	dnsServer->stop();

	return WiFi.status() == WL_CONNECTED;
}

/** Redirect to captive portal if we got a request for another domain. Return true in that case so the page handler do not try to handle the request again. */
bool WiFiManager::captivePortal(AsyncWebServerRequest *request)
{
	if(request->host() != WiFi.softAPIP().toString())
	{
		Serial.printf("Redirecting %s to %s\n\r", request->host().c_str(), WiFi.softAPIP().toString().c_str());
		request->redirect(String("http://") + WiFi.softAPIP().toString() + String("/WIFI"));
		return true;
	}
	return false;
}

String WiFiManager::saveWiFiSettings(ConfigManager::ConfigType type, JsonObject* json)
{
	String FailedKeys = "";
	bool anyErrors = false;
	for (JsonPair kv : *json)
	{
		if(!config->setProperty(kv, type))
		{
			if(anyErrors != false)
			{
				FailedKeys += ", ";
			}
			FailedKeys += kv.key().c_str();
			anyErrors = true;
		}
	}
	config->applyChanges();
	config->saveConfigPersistent(type);
	if(anyErrors == true)
	{
		String ErrorMessage = "ERROR: Following base config properties were not set: " + FailedKeys;
		Serial.print("[W]: ");
		Serial.println(ErrorMessage);
		return ErrorMessage;
	}
	else
	{
		return "Config Saved without errors";
	}
}


// void WiFiManager::startWebInterface()
// {
// 	server->reset();
// 	server->serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

// 	server->onNotFound([](AsyncWebServerRequest *request)
// 	{
// 		request->send(SPIFFS, "/index.html", "text/html");
// 	});

// 	AsyncCallbackJsonWebHandler* baseConfigHandler = new AsyncCallbackJsonWebHandler("/BaseConfig", [](AsyncWebServerRequest *request, JsonVariant &json)
// 	{
// 		JsonObject temp = json.as<JsonObject>();
// 		request->send(200, "text/plain", saveSettings(ConfigManager::BASE_CONFIG, &temp));
// 	});
// 	server->addHandler(baseConfigHandler);

// 	AsyncCallbackJsonWebHandler* colorConfigHandler = new AsyncCallbackJsonWebHandler("/ColorConfig", [](AsyncWebServerRequest *request, JsonVariant &json)
// 	{
// 		JsonObject temp = json.as<JsonObject>();
// 		request->send(200, "text/plain", saveSettings(ConfigManager::COLOR_CONFIG, &temp));
// 	});
// 	server->addHandler(colorConfigHandler);

// 	AsyncCallbackJsonWebHandler* hwConfigHandler = new AsyncCallbackJsonWebHandler("/HWConfig", [](AsyncWebServerRequest *request, JsonVariant &json)
// 	{
// 		JsonObject temp = json.as<JsonObject>();
// 		request->send(200, "text/plain", saveSettings(ConfigManager::HW_CONFIG, &temp));
// 	});
// 	server->addHandler(hwConfigHandler);

// 	AsyncCallbackJsonWebHandler* WIFIConfigHandler = new AsyncCallbackJsonWebHandler("/WIFISettings", std::bind(&WiFiManager::handleWifiSubmit, this, std::placeholders::_1, std::placeholders::_2));
// 	server->addHandler(WIFIConfigHandler);

// 	server->begin();
// 	Serial.println("Web interface should be up and running");
// }