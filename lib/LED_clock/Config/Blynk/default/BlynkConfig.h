#ifndef _BLYNK_CONFIG_H_
#define _BLYNK_CONFIG_H_

#include "Configuration.h"

#if IS_BLYNK_ACTIVE == true
	#include <Arduino.h>
	#define FASTLED_INTERNAL
	#include "FastLED.h"
	#include "ClockState.h"

	/**
	 * @brief These are the channel definitions for Blynk
	 */
	#define BLYNK_CHANNEL_BRIGHTNESS_SLIDER		V0
	#define BLYNK_CHANNEL_LIGHT_GROUP_SELECTOR	V1
	#define BLYNK_CHANNEL_CURRENT_COLOR_PICKER	V2
	#define BLYNK_CHANNEL_TIMER_TIME_INPUT 		V3
	#define BLYNK_CHANNEL_TIMER_START_BUTTON 	V4
	#define BLYNK_CHANNEL_ALARM_TIME_INPUT 		V5
	#define BLYNK_CHANNEL_ALARM_START_BUTTON 	V6
	#define BLYNK_CHANNEL_NIGHT_MODE_TIME_INPUT	V7
	#define BLYNK_CHANNEL_NIGHT_MODE_BRIGHTNESS	V8
	#define BLYNK_CHANNEL_NUM_SPERATION_DOTS	V9

	#define BLYNK_CHANNEL_HOUR_COLOR_SAVE		V10
	#define BLYNK_CHANNEL_MINUTE_COLOR_SAVE		V11
	#define BLYNK_CHANNEL_INTERNAL_COLOR_SAVE	V12
	#define BLYNK_CHANNEL_DOT_COLOR_SAVE		V13

	void BlynkLoopCode(void* pvParameters);

	class BlynkConfig
	{
	private:
		static BlynkConfig* instance;
		TaskHandle_t BlynkLoop;

		BlynkConfig();
	public:
		enum ColorSelector {CHANGE_INTERRIOR_COLOR, CHANGE_HOURS_COLOR, CHANGE_MINUTES_COLOR, CHANGE_DOT_COLOR};
		ColorSelector ColorSelection = CHANGE_HOURS_COLOR;
		CRGB InternalColor;
		CRGB HourColor;
		CRGB MinuteColor;
		CRGB DotColor;
		bool blynkUIUpdateRequired = false;
		DisplayManager* ShelfDisplays;


		~BlynkConfig();
		static BlynkConfig* getInstance();
		void setup();
		void stop();
		void updateUI();
	};

#endif

#endif