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
#include "ESPAsyncWebServer.h"
#include "AsyncJson.h"
#include <ArduinoJson.h>
#include "WiFi.h"
#include <ArduinoOTA.h>
#include "BlynkConfig.h"

DisplayManager* ShelfDisplays;
BlynkConfig* BlynkConfiguration;
TimeManager* timeM;
ClockState* states;
ConfigManager* config;
AsyncWebServer server(80);
bool OTAprogressFirstStep = true;

void setupOTA();
void wifiSetup();

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

String saveSettings(ConfigManager::ConfigType type, JsonObject* json)
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

void startWebServer()
{
	server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

	server.onNotFound([](AsyncWebServerRequest *request){
		if(request->url() == "/WIFI" || request->url() == "/BaseSettings" || request->url() == "/Colors" || request->url() == "/HWSetup")
		{
			request->redirect("/");
		} else
		{
			request->send(404, "text/plain", "Not found");
		}
	});

	AsyncCallbackJsonWebHandler* baseConfigHandler = new AsyncCallbackJsonWebHandler("/BaseConfig", [](AsyncWebServerRequest *request, JsonVariant &json)
	{
		JsonObject temp = json.as<JsonObject>();
		request->send(200, "text/plain", saveSettings(ConfigManager::BASE_CONFIG, &temp));
	});
	server.addHandler(baseConfigHandler);

	AsyncCallbackJsonWebHandler* colorConfigHandler = new AsyncCallbackJsonWebHandler("/ColorConfig", [](AsyncWebServerRequest *request, JsonVariant &json)
	{
		JsonObject temp = json.as<JsonObject>();
		request->send(200, "text/plain", saveSettings(ConfigManager::COLOR_CONFIG, &temp));
	});
	server.addHandler(colorConfigHandler);

	AsyncCallbackJsonWebHandler* hwConfigHandler = new AsyncCallbackJsonWebHandler("/HWConfig", [](AsyncWebServerRequest *request, JsonVariant &json)
	{
		JsonObject temp = json.as<JsonObject>();
		request->send(200, "text/plain", saveSettings(ConfigManager::HW_CONFIG, &temp));
	});
	server.addHandler(hwConfigHandler);

	server.begin();
}

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

	Serial.println("Initializing LEDs...");
	ShelfDisplays->InitSegments(0, NUM_LEDS_PER_SEGMENT, WIFI_CONNECTING_COLOR, 50);

	ShelfDisplays->setHourSegmentColors(HOUR_COLOR);
	ShelfDisplays->setMinuteSegmentColors(MINUTE_COLOR);
	ShelfDisplays->setInternalLEDColor(INTERNAL_COLOR);
	ShelfDisplays->setDotLEDColor(SEPERATION_DOT_COLOR);

	Serial.println("Running wifi setup...");
	wifiSetup();
	setupOTA();
	ArduinoOTA.handle(); //give ota the opportunity to update before the main loop starts in case we have a crash in there

	BlynkConfiguration->setup();

	startWebServer();

	Serial.println("Fetching time from NTP server...");
	if(timeM->init() == false)
	{
		Serial.printf("[E]: TimeManager failed to synchronize for the first time with the NTP server. Retrying in %d seconds", TIME_SYNC_INTERVALL);
	}
	timeM->setTimerTickCallback(TimerTick);
	timeM->setTimerDoneCallback(TimerDone);
	timeM->setAlarmCallback(AlarmTriggered);

	Serial.println("Displaying startup animation...");
	startupAnimation();
	Serial.println("Setup done. Main Loop starting...");
	Serial.printf("Free heap: %d\n\r", esp_get_free_heap_size());
}

void loop()
{
	ArduinoOTA.handle();
	states->handleStates(); //updates display states, switches between modes etc.
    ShelfDisplays->handle();
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

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
	Serial.print("WiFi lost connection. Reason: ");
	Serial.println(info.disconnected.reason);
	Serial.println("Trying to Reconnect");
	WiFi.disconnect();
	WiFi.reconnect();
}

void wifiSetup()
{
	#if USE_ESPTOUCH_SMART_CONFIG == true
		WiFi.reconnect(); //try to reconnect
		Serial.println("Trying to reconnect to previous wifi network");
	#else
		WiFi.begin(WIFI_SSID, WIFI_PW);
	#endif
	ShelfDisplays->setAllSegmentColors(WIFI_CONNECTING_COLOR);
	ShelfDisplays->showLoadingAnimation();
	for (int i = 0; i < NUM_RETRIES; i++)
	{
		Serial.print(".");
		#if USE_ESPTOUCH_SMART_CONFIG == true
			if(WiFi.begin() == WL_CONNECTED)
		#else
			if(WiFi.status() == WL_CONNECTED)
		#endif
		{
			Serial.println("Reconnect successful");
			ShelfDisplays->setAllSegmentColors(WIFI_CONNECTION_SUCCESSFUL_COLOR);
			break;
		}
		ShelfDisplays->delay(500);
	}

	if(WiFi.status() != WL_CONNECTED)
	{
		#if USE_ESPTOUCH_SMART_CONFIG == true
			Serial.println("Reconnect failed. starting smart config");
			WiFi.mode(WIFI_AP_STA);
			// start SmartConfig
			WiFi.beginSmartConfig();

			// Wait for SmartConfig packet from mobile
			Serial.println("Waiting for SmartConfig.");
			ShelfDisplays->setAllSegmentColors(WIFI_SMART_CONFIG_COLOR);
			while (!WiFi.smartConfigDone())
			{
				Serial.print(".");
				ShelfDisplays->delay(500);
			}
			ShelfDisplays->setAllSegmentColors(WIFI_CONNECTING_COLOR);
			Serial.println("");
			Serial.println("SmartConfig done.");

			// Wait for WiFi to connect to AP
			Serial.println("Waiting for WiFi");
			while (WiFi.status() != WL_CONNECTED)
			{
				Serial.print(".");
				ShelfDisplays->setAllSegmentColors(WIFI_CONNECTION_SUCCESSFUL_COLOR);
				ShelfDisplays->delay(500);
			}
			Serial.println("WiFi Connected.");
			Serial.print("IP Address: ");
			Serial.println(WiFi.localIP());
		#else
			Serial.println("WIFI connection failed");
			ShelfDisplays->setAllSegmentColors(ERROR_COLOR);
		#endif
		if(WiFi.status() != WL_CONNECTED)
		{
			Serial.println("WIFI connection failed. Aborting execution.");
			abort();
		}
	}
	WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
	ShelfDisplays->stopLoadingAnimation();
	Serial.println("Waiting for loading animation to finish...");
	ShelfDisplays->waitForLoadingAnimationFinish();
	ShelfDisplays->turnAllSegmentsOff();
}

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
