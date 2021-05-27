/**
 * \file main.cpp
 * \author Florian Laschober
 * \brief Glue logic to bring together all the modules and some additional stuff
 */

#include "Configuration.h"
#include <Arduino.h>
#include "DisplayManager.h"
#include "ClockState.h"
#include "ConfigManager.h"
#include "WiFiManager.h"
#include <ArduinoOTA.h>
#include "BlynkConfig.h"

#include "ESPAsyncWebServer.h"
#include "AsyncJson.h"
#include <ArduinoJson.h>
#include "WiFi.h"
#include <DNSServer.h>

DisplayManager* ShelfDisplays;
BlynkConfig* BlynkConfiguration;
TimeManager* timeM;
ClockState* states;
ConfigManager* config;
WiFiManager* WIFIManager;

AsyncWebServer server(80);
bool OTAprogressFirstStep = true;
wifi_event_id_t reconnectEvent;
bool wifiReconnectFlag = false;
String WIFI_SSID;
String WIFI_PW;

void setupOTA();
void wifiSetup();
void connectToWIFI(const char* SSID = nullptr, const char* PW = nullptr);

void TimerTick();
void TimerDone();
void AlarmTriggered();

void startupAnimation()
{
	uint8_t currHourH = 0;
	uint8_t currHourL = 0;
	uint8_t currMinH = 0;
	uint8_t currMinL = 0;
	uint8_t targetHourH = 0;
	uint8_t targetHourL = 0;
	uint8_t targetMinH = 0;
	uint8_t targetMinL = 0;

	TimeManager::TimeInfo currentTime;
	currentTime = timeM->getCurrentTime();
	targetHourH = currentTime.hours / 10;
	targetHourL = currentTime.hours % 10;
	targetMinH = currentTime.minutes / 10;
	targetMinL = currentTime.minutes % 10;

	ShelfDisplays->displayTime(0, 0);
	ShelfDisplays->delay(DIGIT_ANIMATION_SPEED + 10);

	while (currHourH != targetHourH || currHourL != targetHourL || currMinH != targetMinH || currMinL != targetMinL)
	{
		if(currHourH < targetHourH)
		{
			currHourH++;
		}
		if(currHourL < targetHourL)
		{
			currHourL++;
		}
		if(currMinH < targetMinH)
		{
			currMinH++;
		}
		if(currMinL < targetMinL)
		{
			currMinL++;
		}
		ShelfDisplays->displayTime(currHourH * 10 + currHourL, currMinH * 10 + currMinL);
		ShelfDisplays->delay(DIGIT_ANIMATION_SPEED + 100);
	}
}

// void startWebServer()
// {
// 	server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

// 	server.onNotFound([](AsyncWebServerRequest *request)
// 	{
// 		request->send(SPIFFS, "/index.html", "text/html");
// 	});

// 	AsyncCallbackJsonWebHandler* baseConfigHandler = new AsyncCallbackJsonWebHandler("/BaseConfig", [](AsyncWebServerRequest *request, JsonVariant &json)
// 	{
// 		JsonObject temp = json.as<JsonObject>();
// 		request->send(200, "text/plain", saveSettings(ConfigManager::BASE_CONFIG, &temp));
// 	});
// 	server.addHandler(baseConfigHandler);

// 	AsyncCallbackJsonWebHandler* colorConfigHandler = new AsyncCallbackJsonWebHandler("/ColorConfig", [](AsyncWebServerRequest *request, JsonVariant &json)
// 	{
// 		JsonObject temp = json.as<JsonObject>();
// 		request->send(200, "text/plain", saveSettings(ConfigManager::COLOR_CONFIG, &temp));
// 	});
// 	server.addHandler(colorConfigHandler);

// 	AsyncCallbackJsonWebHandler* hwConfigHandler = new AsyncCallbackJsonWebHandler("/HWConfig", [](AsyncWebServerRequest *request, JsonVariant &json)
// 	{
// 		JsonObject temp = json.as<JsonObject>();
// 		request->send(200, "text/plain", saveSettings(ConfigManager::HW_CONFIG, &temp));
// 	});
// 	server.addHandler(hwConfigHandler);

// 	AsyncCallbackJsonWebHandler* WIFIConfigHandler = new AsyncCallbackJsonWebHandler("/WIFISettings", [](AsyncWebServerRequest *request, JsonVariant &json)
// 	{
// 		JsonObject temp = json.as<JsonObject>();
// 		if(temp.containsKey("SSID") && temp.containsKey("PW"))
// 		{
// 			const char* SSID = temp["SSID"];
// 			const char* PW = temp["PW"];
// 			WIFI_SSID = String(SSID);
// 			WIFI_PW = String(PW);
// 			wifiReconnectFlag = true;
// 			request->send(200, "text/plain", "The device will now attempt to connect to \"" + WIFI_SSID + "\" Connection to the web interface will be lost.");
// 		}
// 		else
// 		{
// 			request->send(200, "text/plain", "ERROR: All two keys (SSID, PW are mandatory but at least one of them was missing.");
// 		}
// 	});
// 	server.addHandler(WIFIConfigHandler);

// 	server.begin();
// }

void setup()
{
	Serial.begin(115200);

	Serial.println("Loading config...");
	config 				= ConfigManager::getInstance();
	Serial.println("Initializing modules...");
	ShelfDisplays 		= DisplayManager::getInstance();
	BlynkConfiguration 	= BlynkConfig::getInstance();
	timeM 				= TimeManager::getInstance();
	states 				= ClockState::getInstance();
	WIFIManager			= WiFiManager::getInstance();

	Serial.println("Initializing LEDs...");
	ShelfDisplays->InitSegments(0, NUM_LEDS_PER_SEGMENT, WIFI_CONNECTING_COLOR, 50);

	ShelfDisplays->setHourSegmentColors(HOUR_COLOR);
	ShelfDisplays->setMinuteSegmentColors(MINUTE_COLOR);
	ShelfDisplays->setInternalLEDColor(INTERNAL_COLOR);
	ShelfDisplays->setDotLEDColor(SEPERATION_DOT_COLOR);

	Serial.println("Running wifi setup...");
	WIFIManager->autoConnect(ShelfDisplays);
	setupOTA();
	ArduinoOTA.handle(); //give ota the opportunity to update before the main loop starts in case we have a crash in there

	BlynkConfiguration->setup();

	// startWebServer();

	Serial.println("Fetching time from NTP server...");
	if(timeM->init() == false)
	{
		Serial.printf("[E]: TimeManager failed to synchronize for the first time with the NTP server. Retrying in %d seconds", TIME_SYNC_INTERVALL);
	}
	timeM->setTimerTickCallback(TimerTick);
	timeM->setTimerDoneCallback(TimerDone);
	timeM->setAlarmCallback(AlarmTriggered);

	Serial.printf("\tMax allocated heap: %d/%d\n\r\tMax allocatedPSram %d/%d\n\r", ESP.getMaxAllocHeap(), ESP.getHeapSize(), ESP.getMaxAllocPsram(), ESP.getPsramSize());
	Serial.println("Displaying startup animation...");
	startupAnimation();
	Serial.println("Setup done. Main Loop starting...");
}

void loop()
{
	ArduinoOTA.handle();
	states->handleStates(); //updates display states, switches between modes etc.
    ShelfDisplays->handle();
	// if(wifiReconnectFlag == true)
	// {
	// 	Serial.printf("Trying to connect to %s with password %s\n\r", WIFI_SSID.c_str(), WIFI_PW.c_str());
	// 	server.end();
	// 	WiFi.removeEvent(reconnectEvent);
	// 	WiFi.disconnect();
	// 	connectToWIFI(WIFI_SSID.c_str(), WIFI_PW.c_str());
	// 	if(WiFi.status() == WL_CONNECTED)
	// 	{
	// 		Serial.println("Connect successful");
	// 		Serial.println("Resetting contoller to reconnect to the right WIFI network");
	// 	}
	// 	else
	// 	{
	// 		Serial.println("Reconnect failed, maximum number of retries exhausted");
	// 	}
	// 	ESP.restart();
	// }
}

void AlarmTriggered()
{
    states->switchMode(ClockState::ALARM_NOTIFICATION);
	BlynkConfiguration->updateUI();
}

void TimerTick()
{
	BlynkConfiguration->updateUI();
}

void TimerDone()
{
    states->switchMode(ClockState::TIMER_NOTIFICATION);
	BlynkConfiguration->updateUI();
}

// void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
// {
// 	Serial.print("WiFi lost connection. Reason: ");
// 	Serial.println(info.disconnected.reason);
// 	Serial.println("Trying to Reconnect");
// 	WiFi.disconnect();
// 	connectToWIFI();
// }

// void connectToWIFI(const char* SSID, const char* PW)
// {
// 	Serial.println("Trying to connect to wifi network");
// 	ShelfDisplays->setAllSegmentColors(WIFI_CONNECTING_COLOR);
// 	ShelfDisplays->showLoadingAnimation();
// 	wl_status_t connectionStatus;
// 	if(SSID != nullptr && PW != nullptr)
// 	{
// 		connectionStatus = WiFi.begin(SSID, PW);
// 	}
// 	else
// 	{
// 		connectionStatus = WiFi.begin();
// 	}
// 	for (int i = 0; i < NUM_RETRIES; i++)
// 	{
// 		Serial.print(".");
// 		if(SSID != nullptr && PW != nullptr)
// 		{
// 			connectionStatus = WiFi.begin(SSID, PW);
// 		}
// 		else
// 		{
// 			connectionStatus = WiFi.begin();
// 		}
// 		if(connectionStatus == WL_CONNECTED)
// 		{
// 			Serial.println("Reconnect successful");
// 			ShelfDisplays->setAllSegmentColors(WIFI_CONNECTION_SUCCESSFUL_COLOR);
// 			break;
// 		}
// 		ShelfDisplays->delay(1000);
// 	}
// }

// void wifiAPMode()
// {
// 	IPAddress apIP(8,8,4,4); // The default android DNS
// 	DNSServer dnsServer;
// 	const byte DNS_PORT = 53;

// 	WiFi.mode(WIFI_AP);
// 	WiFi.softAP("LED-Pixel clock fallback AP");
// 	WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

// 	dnsServer.start(DNS_PORT, "*", apIP);

// 	startWebServer();

// 	server.onNotFound([](AsyncWebServerRequest *request)
// 	{
// 		request->redirect("/WIFI");
// 	});
// 	while(true) {
// 		ShelfDisplays->delay(500);
// 	}
// }

// void wifiSetup()
// {
// 	connectToWIFI();

// 	if(WiFi.status() != WL_CONNECTED)
// 	{
// 		Serial.println("Reconnect failed Starting fallback AP");
// 		ShelfDisplays->setAllSegmentColors(WIFI_SMART_CONFIG_COLOR);
// 		wifiAPMode();
// 	}
// 	reconnectEvent = WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
// 	ShelfDisplays->stopLoadingAnimation();
// 	Serial.println("Waiting for loading animation to finish...");
// 	ShelfDisplays->waitForLoadingAnimationFinish();
// 	ShelfDisplays->turnAllSegmentsOff();
// }

void setupOTA()
{
	// Port defaults to 3232
	// ArduinoOTA.setPort(3232);

	// Hostname defaults to esp3232-[MAC]
	ArduinoOTA.setHostname(OTA_UPDATE_HOST_NAME);

	// No authentication by default
	//ArduinoOTA.setPassword("admin");

	// Password can be set with it's md5 value as well
	// MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
	// ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

	ArduinoOTA.onStart([]() {
		String type;
		if (ArduinoOTA.getCommand() == U_FLASH)
		{
			type = "sketch";
		}
		else // U_SPIFFS
		{
			type = "filesystem";
			SPIFFS.end();
		}
		// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
		Serial.println("Start updating " + type);
		timeM->disableTimer();
		BlynkConfiguration->stop();
		ShelfDisplays->setAllSegmentColors(OTA_UPDATE_COLOR);
		ShelfDisplays->turnAllLEDsOff(); //instead of the loading animation show a progress bar
		ShelfDisplays->setGlobalBrightness(50);
	})
	.onEnd([]()
	{
		Serial.println("\nOTA End");
	})
	.onProgress([](unsigned int progress, unsigned int total)
	{
		Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
		if(OTAprogressFirstStep == true)
		{
			ShelfDisplays->displayProgress(total);
			OTAprogressFirstStep = false;
		}
		ShelfDisplays->updateProgress(progress);
	})
	.onError([](ota_error_t error)
	{
		Serial.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR)
		{
			Serial.println("Auth Failed");
		}
		else if (error == OTA_BEGIN_ERROR)
		{
			Serial.println("Begin Failed");
		}
		else if (error == OTA_CONNECT_ERROR)
		{
			Serial.println("Connect Failed");
		}
		else if (error == OTA_RECEIVE_ERROR)
		{
			Serial.println("Receive Failed");
		}
		else if (error == OTA_END_ERROR)
		{
			Serial.println("End Failed");
		}
		ShelfDisplays->setAllSegmentColors(ERROR_COLOR);
	});

	ArduinoOTA.begin();

	Serial.println("OTA update functionality is ready");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}
