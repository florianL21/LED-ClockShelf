#ifndef _CONFIGURATIONS_H_
#define _CONFIGURATIONS_H_

/*********************************
*
*	Main configuration settings:
*
**********************************/

/**
 * @brief If you want to run the system in a minimal mode to test some basic functionality or
 * 		  debug something it could be useful to disable wifi functionality completley.s
 */
#define RUN_WITHOUT_WIFI 		false

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
#define HOUR_COLOR							CRGB::White

/**
 * @brief Color of the minute segments, this will be the default color if blynk functionality is disabled
 */
#define MINUTE_COLOR						CRGB::Azure

/**
 * @brief Color of the internal LEDs, this will be the default color if blynk functionality is disabled
 */
#define INTERNAL_COLOR						CRGB::Blue

/**
 * @brief Color of the seperation dot LEDs, this will be the default color if blynk functionality is disabled
 */
#define SEPERATION_DOT_COLOR				CRGB::Blue

/**
 * @brief Color of the LEDs for the OTA update progress bar
 */
#define OTA_UPDATE_COLOR					CRGB::Orange

/**
 * @brief Color of the LEDs while searching for a WIFI network
 */
#define WIFI_CONNECTING_COLOR				CRGB::Blue

/**
 * @brief Color of the LEDs signaling a successful WIFI connection
 */
#define WIFI_CONNECTION_SUCCESSFUL_COLOR	CRGB::Green

/**
 * @brief Color of the LEDs if system is waiting for WIFI smart config
 */
#define WIFI_SMART_CONFIG_COLOR				CRGB::Yellow

/**
 * @brief Color of the LEDs signaling an error of some sort
 */
#define ERROR_COLOR							CRGB::Red

/**
 * @brief Server for the time
 */
#define NTP_SERVER "pool.ntp.org"

/**
 * @brief Enter the string for your timezone according to this webpage: https://remotemonitoringsystems.ca/time-zone-abbreviations.php
 */
#define TIMEZONE_INFO "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00"

/**
 * @brief Time in seconds for the intervall in which the time should be synchronized with the time server
 */
#define TIME_SYNC_INTERVALL 1800

/**
 * @brief Flash the current time in case a timer is expired instead of flashing 00:00
 */
#define ALARM_FLASH_TIME false

/**
 * @brief Number of flashes until an alarm is considered complete and the system goes back to normal
 */
#define ALARM_FLASH_COUNT 10

/**
 * @brief How often the time is checked and the displays are updated
 */
#define TIME_UPDATE_INTERVALL	500


/***************************
*
* LED Configuration
*
*****************************/

/**
 * @brief Pin to which the led Strip data pin is connected to
 */
#define LED_DATA_PIN			21

/**
 * @brief Total number of segments that have LEDs in the shelf
 */
#define NUM_SEGMENTS 			32

/**
 * @brief Number of LEDs in each segment
 */
#define NUM_LEDS_PER_SEGMENT	12

/**
 * @brief If you wired the down lighter LEDs to the end of the LED strips set this to true
 */
#define APPEND_DOWN_LIGHTERS	true

/**
 * @brief Number of LEDs For interrior lights
 */
#define ADDITIONAL_LEDS			12

/**
 * @brief Automatically calculated total number of LEDs used
 */
#if APPEND_DOWN_LIGHTERS == true
	#define NUM_LEDS 				(NUM_SEGMENTS * NUM_LEDS_PER_SEGMENT + ADDITIONAL_LEDS)
#else
	#define NUM_LEDS 				(NUM_SEGMENTS * NUM_LEDS_PER_SEGMENT)

	/**
	 * @brief Pin to which the downlight led Strip data pin is connected to
	 */
	#define DOWNLIGHT_LED_DATA_PIN			22
#endif

/**
 * @brief Number of displays in the shelf
 */
#define NUM_DISPLAYS			7

/**
 * @brief These enum definitions are used in the code do address the different Seven segment displays. 
 * 		  The numbers have to match with the place of the display in the SegmentDisplayModes array in the file DisplayConfiguration.cpp
 */
enum DisplayIDs {
	HIGHER_DIGIT_HOUR_DISPLAY = 0,
	FIRST_INTERMEDIATE_DISPLAY = 1,
	LOWER_DIGIT_HOUR_DISPLAY = 2,
	SECOND_INTERMEDIATE_DISPLAY = 3,
	HIGHER_DIGIT_MINUTE_DISPLAY = 4,
	THIRD_INTERMEDIATE_DISPLAY = 5,
	LOWER_DIGIT_MINUTE_DISPLAY = 6
};

/**
 * @brief If set to true the display will show 0 at midnight and 12 otherwise
 */
#define DISPLAY_0_AT_MIDNIGHT 		false

/**
 * @brief If set to true the higher displays will turn off in case they would show 0
 */
#define DISPLAY_SWITCH_OFF_AT_0 	false

/**
 * @brief If set to true 24 hour format will be used. For this one additional column is needed in the shelf to display it correctly
 */
#define USE_24_HOUR_FORMAT			false

/**
 * @brief The number of segments to use for displaying a progress bar for the OTA updates
 */
#define NUM_SEGMENTS_PROGRESS		16

/**
 * @brief The time is shall take for one iteration of the loading animation
 */
#define LOADING_ANIMATION_DURATION		3000

/**
 * @brief How fast the brightness interpolation shall react to brightness changes
 */
#define BRIGHTNESS_INTERPOLATION	3000

/**
 * @brief If set to -1 the flashing middle dot is disabled, otherwise this is the index of the Display segment that should display the dot.
 */
#define DISPLAY_FOR_SEPERATION_DOT SECOND_INTERMEDIATE_DISPLAY

/**
 * @brief Target Frames per second for the smoothness of animations
 */
#define ANIMATION_TARGET_FPS		60

/**
 * @brief Length of sooth animation transition from fully on to black and vice versa in percent
 * 		  NOTE: The higher this number the less obvious easing effects like bounce or elastic will be
 */
#define ANIMATION_AFTERGLOW			0.2

/**
 * @brief Lenght of the dot/s fading animation. One flash fades in and out
 */
#define DOT_FLASH_SPEED 2000

/**
 * @brief Intervall in which the dot/s should flash
 */
#define DOT_FLASH_INTERVALL	4000

/**
 * @brief Number of seperation dots to use by default (or if no blynk functionality is avaliable)
 * 		  allowed values are 1, 2 and 0 to turn it off
 */
#define NUM_SEPERATION_DOTS	2


/***************************
*
* Light sensor settings
*
*****************************/

/**
 * @brief Enable automatic brightness adjustments based on a light sensor
 */
#define ENABLE_LIGHT_SENSOR			false

#if ENABLE_LIGHT_SENSOR == true
	/**
	 * @brief ADC pin to which the light sensor is connected to
	 */
	#define LIGHT_SENSOR_PIN			34

	/**
	 * @brief How many measurements shall be avaeraged. Higher number -> smoother but slower change
	 */
	#define LIGHT_SENSOR_AVERAGE		15

	/**
	 * @brief Width of the meadian calculation. Higher number -> smoother change
	 * 		  Should never be higher than the LIGHT_SENSOR_AVERAGE
	 */
	#define LIGHT_SENSOR_MEDIAN_WIDTH	5

	/**
	 * @brief Time that should pass before the light sensor is read again. Higher number -> slower adjustments but also changes will be more sudden
	 */
	#define LIGHT_SENSOR_READ_DELAY		500

	/**
	 * @brief AnalogRead value if the light sensor reads complete darkness
	 */
	#define LIGHT_SENSOR_MIN			0

	/**
	 * @brief AnalogRead value if the light sensor reads the brightest
	 */
	#define LIGHT_SENSOR_MAX			4095

	/**
	 * @brief Value betwee 0 and 255 that determines how much the light sensor values can influence the led brightness
	 */
	#define LIGHT_SENSOR_SENSITIVITY	100

#endif


/*********************************
*
*	Misc settings:
*
**********************************/


/**
 * @brief enable for wifi less operation or to demo all the animations
 */
#define TIME_MANAGER_DEMO_MODE	false

/**
 * @brief The time it takes for one digit to morph into another
 */
#define DIGIT_ANIMATION_SPEED 900

/**
 * @brief the minimum delay between calls of FastLED.show()
 */
#define FASTLED_SAFE_DELAY_MS 20

#endif