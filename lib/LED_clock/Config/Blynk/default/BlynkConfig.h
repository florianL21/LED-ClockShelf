/**
 * \file BlynkConfig.h
 * \author Florian Laschober
 * \brief Header for the #BlynkConfig class and all needed \ref #BlynkChannels defines
 */

#ifndef _BLYNK_CONFIG_H_
#define _BLYNK_CONFIG_H_

#include "Configuration.h"

#if IS_BLYNK_ACTIVE == true
	#include <Arduino.h>
	#include <esp_task_wdt.h>
	#define FASTLED_INTERNAL
	#include "FastLED.h"
	#include "ClockState.h"

    /**
     * \addtogroup BlynkChannels
     * \brief These are the channel definitions for Blynk
     * \{
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
	#define BLYNK_CHANNEL_NUM_SEPARATION_DOTS	V9
	#define BLYNK_CHANNEL_HOUR_COLOR_SAVE		V10
	#define BLYNK_CHANNEL_MINUTE_COLOR_SAVE		V11
	#define BLYNK_CHANNEL_INTERNAL_COLOR_SAVE	V12
	#define BLYNK_CHANNEL_DOT_COLOR_SAVE		V13
	#define BLYNK_CHANNEL_SELECTOR_HOURS		V14
	#define BLYNK_CHANNEL_SELECTOR_MINUTES		V15
	#define BLYNK_CHANNEL_SELECTOR_INTERIOR		V16
	#define BLYNK_CHANNEL_SELECTOR_DOT			V17
    /** \} */

    /**
     * \brief Loop function which is executed on the second core of the ESP
     *
     */
	void BlynkLoopCode(void* pvParameters);

    /**
     * \brief Configuration class for storing all Blynk related information
     *
     */
	class BlynkConfig
	{
	private:
		static BlynkConfig* instance;
		TaskHandle_t BlynkLoop;

		BlynkConfig();
	public:
        /**
         * \brief possible selection options of the segmented switch responsible for selecting which color should be
         *        changed in the App
         *
         */
		enum ColorSelector {CHANGE_HOURS_COLOR = 0x01, CHANGE_MINUTES_COLOR = 0x02, CHANGE_INTERIOR_COLOR = 0x04, CHANGE_DOT_COLOR = 0x08};
		uint8_t ColorSelection;
		CRGB InternalColor;
		CRGB HourColor;
		CRGB MinuteColor;
		CRGB DotColor;
		bool blynkUIUpdateRequired;
		DisplayManager* ShelfDisplays;
		bool isClearAction;


		~BlynkConfig();
        /**
         * \brief Get the Instance object.
         *        Use this to get an instance to the Blynk config singleton instead of its constructor.
         *
         * \return BlynkConfig* pointer to the already existing or newly created BlynkConfig object.
         */
		static BlynkConfig* getInstance();

        /**
         * \brief to be called as part of the setup function
         *
         * \pre WIFI connection has to be established already by calling #wifiSetup before this method
         */
		void setup();

        /**
         * \brief Stop the execution of Blynk
         *
         */
		void stop();

        /**
         * \brief Call this if a UI update is needed
         *        Possible cases for this are that the timer ticked or was triggered or the alarm was triggered
         *
         */
		void updateUI();

		/**
		 * \brief Change the selection of the segmented switch responsible for selecting which color should be changed
		 */
		void changeSelection(ColorSelector selector, bool state);
	};

#endif

#endif
