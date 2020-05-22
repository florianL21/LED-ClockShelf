#ifndef __DISPLAY_MANAGER_H_
#define __DISPLAY_MANAGER_H_

#include <Arduino.h>
#define FASTLED_INTERNAL
#include "FastLED.h"
#include "Animator.h"
#include "Segment.h"
#include "SevenSegment.h"
#include "TimeManager.h"
#include "Configuration.h"
#include "LinkedList.h"


class DisplayManager
{
public:
	

private:
	//segment configurations
	static SevenSegment::SegmentPosition SegmentPositions[NUM_SEGMENTS];
	static Segment::direction SegmentDirections[NUM_SEGMENTS];
	static SevenSegment::SevenSegmentMode SegmentDisplayModes[NUM_DISPLAYS];
	static uint8_t diplayIndex[NUM_SEGMENTS];

	Animator animationManager;
	Animator* animationManagers[NUM_DISPLAYS];
	Animator* animationManagerTempBuffer[NUM_DISPLAYS];
	Segment* allSegments[NUM_SEGMENTS];
	SevenSegment* Displays[NUM_DISPLAYS];

	#if ENABLE_LIGHT_SENSOR == true
		LinkedList<uint16_t> lightSensorMeasurements;
		uint64_t lastSensorMeasurement;
		uint8_t lightSensorBrightness;
		uint16_t BrightnessOffset;
	#endif

	void AnimationManagersTemporaryOverride(Animator* OverrideanimationManager);
	void restoreAnimationManagers();

	//Animations
	Animator::ComplexAmination LoadingAnimation;
	void InitLoadingAnimation(uint16_t totalAnimationLength);

	CRGB leds[NUM_LEDS];
	#if APPEND_DOWN_LIGHTERS == false
		CRGB DownlightLeds[ADDITIONAL_LEDS];
	#endif

	#if ENABLE_LIGHT_SENSOR == true
		void takeBrightnessMeasurement();
	#endif

public:
	

	DisplayManager();
	~DisplayManager();

	/**
	 * @brief Initialize all the segment using the configutration from DisplayConfiguration.cpp
	 * @param indexOfFirstLed 	Index of the first led in the string that is part of a segment (usually 0)
	 * @param ledsPerSegment 	Sets the number of LEDs that are in one segment. this will be the same for all segments
	 * @param initialColor 		Sets the initial color of all the segments. This does not switch any segments on by it's own
	 */
	void InitSegments(uint16_t indexOfFirstLed, uint8_t ledsPerSegment, CRGB initialColor);

	/**
	 * @brief Sets the color of all segments and updates it immediatley for all segments that are currently switched on
	 * @param color Color to set the LEDs to
	 */
	void setAllSegmentColors(CRGB color);

	/**
	 * @brief Sets the color of the the segments which are displaying hours and updates it immediatley for all segments that are currently switched on
	 * @param color Color to set the LEDs to
	 */
	void setHourSegmentColors(CRGB color);

	/**
	 * @brief Sets the color of the the segments which are displaying minutes and updates it immediatley for all segments that are currently switched on
	 * @param color Color to set the LEDs to
	 */
	void setMinuteSegmentColors(CRGB color);
	
	/**
	 * @brief Attempts to display a string on the seven segment displays
	 * @param text String of text to display
	 */
	void displayText(String text);

	/**
	 * @brief Display the time
	 * @param hours 	Hours in a range of 0 to 24, anything else will generate a debug output and not do anything
	 * @param minutes 	Hours in a range of 0 to 59, anything else will generate a debug output and not do anything
	 */
	void displayTime(uint8_t hours, uint8_t minutes);

	/**
	 * @brief Has to be called in the cyclicly loop to enable live updating of the LEDs
	 */
	void handle();

	/**
	 * @brief Sets the color of the interrior LEDs and displays it immediatley
	 */
	void setInternalLEDColor(CRGB color);

	/**
	 * @brief Starts the loading animation
	 */
	void showLoadingAnimation();

	/**
	 * @brief Stops the currently running animation after it is finished. This causes a looping animation to stop after its current cycle
	 */
	void stopLoadingAnimation();

	/**
	 * @brief Wait until the currently set complex animation is finished.
	 */
	void waitForLoadingAnimationFinish();

	/**
	 * @brief Turns all displays off completely, Does not affect interior lights
	 */
	void turnAllSegmentsOff();

	/**
	 * @brief Display a progress bar on the LEDs
	 * @param progress How much progress was done already
	 * @param progress How much progress there is to do in total
	 */
	void showProgress(uint32_t progress, uint32_t total);
	
	/**
	 * @brief Use this delay instead of the Arduino delay to enable Display updates during the delay.
	 * @param timeInMs Delay time in ms
	 */
	void delay(uint32_t timeInMs);
	/**
	 * @brief Sets the Brightness globally for all leds
	 * @param brightness value between 0 for lowest, and 255 for the highes brightness
	 */
	void setGlobalBrightness(uint8_t brightness);


	
};


#endif