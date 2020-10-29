#include "Configuration.h"
#include <Arduino.h>
#include "DisplayManager.h"

#if RUN_WITHOUT_WIFI == false
	#include "WiFi.h"
#endif
#if ENABLE_OTA_UPLOAD == true
	#include <ArduinoOTA.h>
#endif
#if IS_BLYNK_ACTIVE == true
	/**
	 * @note if you use a different controller make sure to change the include here
	 */
	#include <BlynkSimpleEsp32.h>
#endif

#define TIME_UPDATE_INTERVALL	500

DisplayManager ShelfDisplays;
TimeManager* timeM = nullptr;
unsigned long lastMillis = millis();
bool blynkUIUpdateRequired = false;
enum ClockStates {CLOCK_MODE, TIMER_MODE, ALARM_MODE};
ClockStates MainState = CLOCK_MODE;
uint8_t clockBrightness = 128;
bool currentAlarmSignalState = false;
uint16_t arlarmToogleCount = 0;
enum ColorSelector {CHANGE_INTERRIOR_COLOR, CHANGE_HOURS_COLOR, CHANGE_MINUTES_COLOR};
ColorSelector ColorSelection = CHANGE_HOURS_COLOR;
CRGB InternalColor;
CRGB HourColor;
CRGB MinuteColor;


TaskHandle_t core0Loop;

#if ENABLE_OTA_UPLOAD == true
	void setupOTA();
#endif
#if RUN_WITHOUT_WIFI == false
	void wifiSetup();
#endif

void core0LoopCode( void * pvParameters );
void TimerTick();
void TimerDone();

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

	ShelfDisplays.displayTime(0, 0);
	ShelfDisplays.delay(DIGIT_ANIMATION_SPEED + 10);

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
		ShelfDisplays.displayTime(currHourH * 10 + currHourL, currMinH * 10 + currMinL);
		ShelfDisplays.delay(DIGIT_ANIMATION_SPEED + 10);
	}
}

void setup()
{
	Serial.begin(115200);
	
	ShelfDisplays.InitSegments(0, NUM_LEDS_PER_SEGMENT, CRGB::Blue);

	ShelfDisplays.setHourSegmentColors(HOUR_COLOR);
	ShelfDisplays.setMinuteSegmentColors(MINUTE_COLOR);
	ShelfDisplays.setInternalLEDColor(INTERNAL_COLOR);
	ShelfDisplays.setGlobalBrightness(128);

	#if RUN_WITHOUT_WIFI == false
		wifiSetup();
	#endif
	#if ENABLE_OTA_UPLOAD == true
		setupOTA();
	#endif
	#if RUN_WITHOUT_WIFI == false
		ShelfDisplays.waitForLoadingAnimationFinish();
	#endif

	#if ENABLE_OTA_UPLOAD == true
		ArduinoOTA.handle(); //give ota the opportunity to update before the main loop starts in case we have a crash in there
	#endif

	#if IS_BLYNK_ACTIVE == true
		Blynk.config(BLYNK_AUTH_TOKEN, BLYNK_SERVER, 80);
	#endif

	Serial.println("Fetching time from NTP server...");
	timeM = TimeManager::getInstance();
	timeM->setTimerTickCallback(TimerTick);
	timeM->setTimerDoneCallback(TimerDone);

	Serial.println("Starting blynk on core 0...");
	//Setup the loop task on the second core
	xTaskCreatePinnedToCore(
	core0LoopCode,	// Task function.
	"core0Loop",	// name of task.
	10000,			// Stack size of task
	NULL,			// parameter of the task
	1,				// priority of the task
	&core0Loop,		// Task handle to keep track of created task
	0);				// pin task to core 0

	Serial.println("Displaying startup animation...");
	startupAnimation();
	Serial.println("Setup done. Main Loop starting...");
}

void loop()
{
	#if ENABLE_OTA_UPLOAD == true
		ArduinoOTA.handle();
	#endif
	if(lastMillis + TIME_UPDATE_INTERVALL <= millis()) // update the display only in a certain intervall
	{
		lastMillis = millis();
		TimeManager::TimeInfo currentTime;
		currentTime = timeM->getCurrentTime();
		switch (MainState)
		{
		case CLOCK_MODE:
			ShelfDisplays.displayTime(currentTime.hours, currentTime.minutes);
		break;
		case TIMER_MODE:
			//timers only support up to one hour durations, but really only 19 minutes if the first segment can only display a one
			ShelfDisplays.displayTime(currentTime.minutes, currentTime.seconds);
		break;
		case ALARM_MODE:
			if(currentAlarmSignalState == true)
			{
				ShelfDisplays.setGlobalBrightness(255, false);
			}
			else
			{
				ShelfDisplays.setGlobalBrightness(0, false);
			}
			currentAlarmSignalState = !currentAlarmSignalState;
			arlarmToogleCount++;
			#if ALARM_FLASH_TIME == true
				ShelfDisplays.displayTime(currentTime.hours, currentTime.minutes);
			#else
				ShelfDisplays.displayTime(0, 0);
			#endif
			if(arlarmToogleCount >= ALARM_FLASH_COUNT)
			{
				ShelfDisplays.setGlobalBrightness(clockBrightness);
				ShelfDisplays.displayTime(currentTime.hours, currentTime.minutes);
				arlarmToogleCount = 0;
				MainState = CLOCK_MODE;
			}
		break;
		
		default:
			break;
		}
	}
	ShelfDisplays.handle();
}

void core0LoopCode(void* pvParameters)
{
	Serial.printf("Loop task running on core %d\n\r", xPortGetCoreID());

	for(;;)
	{
		#if IS_BLYNK_ACTIVE == true
			Blynk.run();
			if(blynkUIUpdateRequired == true)
			{
				blynkUIUpdateRequired = false;
				if(MainState == CLOCK_MODE)
				{
					Blynk.virtualWrite(V4, 0);
				}
				else
				{
					// TimeManager::TimeInfo currentTimerValue = timeM->getCurrentTime();
					// int time = currentTimerValue.hours * 3600 + currentTimerValue.minutes * 60 + currentTimerValue.seconds;
					// Blynk.virtualWrite(V4, time, 0);
				}
			}
		#endif
		delay(1); //needed to serve the wdg
	} 
}

void TimerTick()
{
	blynkUIUpdateRequired = true;
}

void TimerDone()
{
	MainState = ALARM_MODE;
	blynkUIUpdateRequired = true;
}

#if IS_BLYNK_ACTIVE == true
	BLYNK_CONNECTED()
	{
		Blynk.syncVirtual(V0);
		#if BLYNK_SEPERATE_COLOR_CONTROL == true
			Blynk.syncVirtual(V1);
		#endif
		Blynk.syncVirtual(V2);
		Blynk.syncVirtual(V3);
		Blynk.virtualWrite(V4, 0);
	}



	BLYNK_WRITE(V0) 
	{
		clockBrightness = param[0].asInt();
		ShelfDisplays.setGlobalBrightness(clockBrightness);
	}

	#if BLYNK_SEPERATE_COLOR_CONTROL == true
		BLYNK_WRITE(V1) 
		{
			switch (param.asInt())
			{
			case 1:
				ColorSelection = CHANGE_HOURS_COLOR;
				Blynk.virtualWrite(V2, HourColor.r, HourColor.g, HourColor.b);
				break;
			case 2:
				ColorSelection = CHANGE_MINUTES_COLOR;
				Blynk.virtualWrite(V2, MinuteColor.r, MinuteColor.g, MinuteColor.b);
				break;
			case 3:
				ColorSelection = CHANGE_INTERRIOR_COLOR;
				Blynk.virtualWrite(V2, InternalColor.r, InternalColor.g, InternalColor.b);
				break;
			}
		}
	#endif

	BLYNK_WRITE(V2) 
	{
		CRGB currentColor;
		currentColor.r  = param[0].asInt();
		currentColor.g  = param[1].asInt();
		currentColor.b  = param[2].asInt();
		#if BLYNK_SEPERATE_COLOR_CONTROL == true
			switch (ColorSelection)
			{
			case CHANGE_HOURS_COLOR:
				ShelfDisplays.setHourSegmentColors(currentColor);
				HourColor = currentColor;
				break;
			case CHANGE_MINUTES_COLOR:
				ShelfDisplays.setMinuteSegmentColors(currentColor);
				MinuteColor = currentColor;
				break;
			case CHANGE_INTERRIOR_COLOR:
				ShelfDisplays.setInternalLEDColor(currentColor);
				InternalColor = currentColor;
				break;
			}
		#else
			ShelfDisplays.setAllSegmentColors(currentColor);
		#endif
	}

	BLYNK_WRITE(V3) 
	{
		TimeManager::TimeInfo TimerDuration;
		TimeInputParam t(param);
		//Timers do not support values larger than 24 minutes, This is a bit of a hack but there is no other way around it :/
		TimerDuration.hours = 0; //t.getStartHour();
		TimerDuration.minutes = t.getStartHour();
		TimerDuration.seconds = t.getStartMinute();
		//Serial.printf("StartTime: %d:%d:%d\n\r", TimerDuration.hours, TimerDuration.minutes, TimerDuration.seconds);
		timeM->setTimerDuration(TimerDuration);
	}

	BLYNK_WRITE(V4)
	{
		if(param[0].asInt() == 1)
		{
			timeM->startTimer();
			Serial.println("Timer Started");
			MainState = TIMER_MODE;
		}
		else
		{
			timeM->stopTimer();
			Serial.println("Timer Stopped");
			Blynk.syncVirtual(V3);
			arlarmToogleCount = 0;
			ShelfDisplays.setGlobalBrightness(clockBrightness);
			MainState = CLOCK_MODE;
		}
	}
#endif


#if RUN_WITHOUT_WIFI == false
	void wifiSetup()
	{
		#if USE_ESPTOUCH_SMART_CONFIG == true
			WiFi.reconnect(); //try to reconnect
			Serial.println("Trying to reconnect to previous wifi network");
		#else
			WiFi.begin(WIFI_SSID, WIFI_PW);
		#endif
		ShelfDisplays.setAllSegmentColors(CRGB::Blue);
		ShelfDisplays.showLoadingAnimation();
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
				ShelfDisplays.setAllSegmentColors(CRGB::Green);
				break;
			}
			ShelfDisplays.delay(500);
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
				ShelfDisplays.setAllSegmentColors(CRGB::Red);
				while (!WiFi.smartConfigDone()) 
				{
					Serial.print(".");
					ShelfDisplays.delay(500);
				}
				ShelfDisplays.setAllSegmentColors(CRGB::Blue);
				Serial.println("");
				Serial.println("SmartConfig done.");

				// Wait for WiFi to connect to AP
				Serial.println("Waiting for WiFi");
				while (WiFi.status() != WL_CONNECTED) 
				{
					Serial.print(".");
					ShelfDisplays.setAllSegmentColors(CRGB::Green);
					ShelfDisplays.delay(500);
				}
				Serial.println("WiFi Connected.");
				Serial.print("IP Address: ");
				Serial.println(WiFi.localIP());
			#else
				Serial.println("WIFI connection failed");
				ShelfDisplays.setAllSegmentColors(CRGB::Red);
			#endif
			if(WiFi.status() != WL_CONNECTED)
			{
				while(1); //Never return from here since running the main loop without wifi connection will crash the controller
			}
		}
		ShelfDisplays.stopLoadingAnimation();
	}
#endif

#if ENABLE_OTA_UPLOAD == true
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
			}
			// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
			Serial.println("Start updating " + type);
			timeM->disableTimer();
			vTaskDelete(core0Loop);
			ShelfDisplays.setAllSegmentColors(CRGB::Orange);
			ShelfDisplays.turnAllSegmentsOff(); //instead of the loading animation show a progress bar
		})
		.onEnd([]() 
		{
			Serial.println("\nOTA End");
		})
		.onProgress([](unsigned int progress, unsigned int total) 
		{
			Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
			ShelfDisplays.showProgress(progress, total);
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
			ShelfDisplays.setAllSegmentColors(CRGB::Red);
		});

		ArduinoOTA.begin();

		Serial.println("OTA update functionality is ready");
		Serial.print("IP address: ");
		Serial.println(WiFi.localIP());
	}
#endif