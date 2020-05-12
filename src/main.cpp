/*********************************
*
*	CONFIGURATION:
*
**********************************/

/**
 * @brief If you want to run the system in a minimal mode to test some basic functionality or 
 * 		  debug something it could be useful to disable wifi functionality completley.s
 */
#define RUN_WITHOUT_WIFI 		true

#if RUN_WITHOUT_WIFI == false
	/**
	 * @brief If you want Blynk functionallity set this to true and set your authentication token. Otherwise set it to false
	 */
	#define IS_BLYNK_ACTIVE 		true

	#if IS_BLYNK_ACTIVE == true
		/**
		 * @brief If you want Blynk functionallity paste your authentication token here.
		 */
		#define BLYNK_AUTH_TOKEN 	"AUTH_TOKEN_GOES_HERE" 

		/**
		 * @brief In case the blynk communication is not working this line causes Blynk to send debug output to the serial port.
		 * 		  If you are not worried about Blynk or have to diagnose some other issue you can comment this line out.
		 */
		#define BLYNK_PRINT 		Serial

		/**
		 * @brief Set the Blynk server address.
		 * @note I had troubles with using the proper blynk domain so I am using the IP adress instead.
		 * 		 Maybe this could create problems in the future so it is recommended to use the official domain.
		 */
		#define BLYNK_SERVER 		"blynk-cloud.com" // "139.59.206.133"

		/**
		 * @brief If you have seperate color controls for HOUR and MINUTE set this to true, if you want to use the same color for both set it to false
		 */
		#define BLYNK_SEPERATE_COLOR_CONTROL 	true
	#endif

	/**
	 * @brief If you ant to use OTA upload instead or in addition to the normal cable upload set this option to true.
	 * To actuall flash something via OTA you have to uncomment the OTA flash lines in the platformio.ini file
	 * This is a nice addition to cable upload but it doesn't replace it completely. 
	 * If the microcontroller crashes because of bad software you still have to use a cable
	 */
	#define ENABLE_OTA_UPLOAD			true

	#if ENABLE_OTA_UPLOAD == true
		/**
		 * @brief The host name that shall be used for OTA updates. If you change this here it must also be changed in the platformio.ini file
		 */
		#define OTA_UPDATE_HOST_NAME	"LED-Shelf"
	#endif

	/**
	 * @brief The number of times the controller tries to connect to wifi before it fails and goes into smartConfig mode (if that is enabled)
	 */
	#define NUM_RETRIES 			50

	/**
	 * @brief Use the ESP smart config to setup the wifi network. If you want to set it manually set this to false
	 */
	#define USE_ESPTOUCH_SMART_CONFIG	true

	#if USE_ESPTOUCH_SMART_CONFIG == false
		/**
		 * @brief WIFI_SSID and WIFI_PW are only needed if smart setup is disabled
		 */
		#define WIFI_SSID	"SET_YOUR_SSID_HERE"
		#define WIFI_PW		"SET_YOUR_PASSWORD_HERE"
	#endif

#endif

/**
 * @brief Color of the hour segments, this will be the default color if blynk functionality is disabled
 */
#define HOUR_COLOR		CRGB::White

/**
 * @brief Color of the minute segments, this will be the default color if blynk functionality is disabled
 */
#define MINUTE_COLOR	CRGB::Azure

/**
 * @brief Server for the time
 */
#define NTP_SERVER "pool.ntp.org"

/**
 * @brief Timezone offset in seconds
 */
#define TIMEZONE_OFFSET		3600

/**
 * @brief Set to 3600 if you have daylight saving hour otherwise set to 0
 */
#define DAYLIGHT_SAVING 3600

/**
 * @brief Time update intervall in milliseconds
 */
#define TIME_UPDATE_INTERVALL 15000


/*********************************
*
*	CODE:
*
**********************************/

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

DisplayManager ShelfDisplays;
TimeManager* timeM = nullptr;
unsigned long lastMillis = millis();

#if ENABLE_OTA_UPLOAD == true
	void setupOTA();
#endif
#if RUN_WITHOUT_WIFI == false
	void wifiSetup();
#endif

void displayTime()
{
	TimeManager::TimeInfo currentTime;
	currentTime = timeM->getCurrentTime();
	ShelfDisplays.displayTime(currentTime.hours, currentTime.minutes);
}

void setup()
{
	Serial.begin(115200);
	
	ShelfDisplays.InitSegments(0, NUM_LEDS_PER_SEGMENT, CRGB::Blue);

	ShelfDisplays.setHourSegmentColors(HOUR_COLOR);
	ShelfDisplays.setMinuteSegmentColors(MINUTE_COLOR);

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

	timeM = new TimeManager(TIMEZONE_OFFSET, DAYLIGHT_SAVING, NTP_SERVER, TIME_UPDATE_INTERVALL);
	displayTime();
}

void loop()
{
	
	#if ENABLE_OTA_UPLOAD == true
		ArduinoOTA.handle();
	#endif

	timeM->update();
	if(lastMillis + 1000 <= millis()) // update the time every second
	{
		lastMillis = millis();
		displayTime();
	}
	ShelfDisplays.handle();

	#if IS_BLYNK_ACTIVE == true
		Blynk.run();
	#endif
}

#if IS_BLYNK_ACTIVE == true
	BLYNK_CONNECTED()
	{
		Blynk.syncVirtual(V0);
		Blynk.syncVirtual(V1);
		Blynk.syncVirtual(V2);
		#if BLYNK_SEPERATE_COLOR_CONTROL == true
			Blynk.syncVirtual(V3);
		#endif
	}

	BLYNK_WRITE(V0) 
	{
		ShelfDisplays.setGlobalBrightness(param[0].asInt());
	}

	BLYNK_WRITE(V1) 
	{
		CRGB currentColor;
		currentColor.r  = param[0].asInt();
		currentColor.g  = param[1].asInt();
		currentColor.b  = param[2].asInt();
		ShelfDisplays.setInternalLEDColor(currentColor);
	}

	BLYNK_WRITE(V2) 
	{
		CRGB currentColor;
		currentColor.r  = param[0].asInt();
		currentColor.g  = param[1].asInt();
		currentColor.b  = param[2].asInt();
		#if BLYNK_SEPERATE_COLOR_CONTROL == true
			ShelfDisplays.setHourSegmentColors(currentColor);
		#else
			ShelfDisplays.setAllSegmentColors(currentColor);
		#endif
		displayTime();
	}

	#if BLYNK_SEPERATE_COLOR_CONTROL == true
		BLYNK_WRITE(V3) 
		{
			CRGB currentColor;
			currentColor.r  = param[0].asInt();
			currentColor.g  = param[1].asInt();
			currentColor.b  = param[2].asInt();
			ShelfDisplays.setMinuteSegmentColors(currentColor);
			displayTime();
		}
	#endif
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
				/* start SmartConfig */
				WiFi.beginSmartConfig();

				/* Wait for SmartConfig packet from mobile */
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

				/* Wait for WiFi to connect to AP */
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

		Serial.println("Ready");
		Serial.print("IP address: ");
		Serial.println(WiFi.localIP());
	}
#endif