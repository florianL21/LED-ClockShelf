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
	WIFIManager->startWebUI();
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
