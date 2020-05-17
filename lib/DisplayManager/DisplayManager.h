#ifndef __DISPLAY_MANAGER_H_
#define __DISPLAY_MANAGER_H_

#include <Arduino.h>
#define FASTLED_INTERNAL
#include "FastLED.h"
#include "Animator.h"
#include "Segment.h"
#include "SevenSegment.h"
#include "TimeManager.h"

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
#define NUM_SEGMENTS 			23

/**
 * @brief Number of LEDs in each segment
 */
#define NUM_LEDS_PER_SEGMENT	9

/**
 * @brief If you wired the down lighter LEDs to the end of the LED strips set this to true
 */
#define APPEND_DOWN_LIGHTERS	false

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
#define NUM_DISPLAYS			4

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
 * @brief The time it shall take for one iteration of the loading animation
 */
#define NUM_SEGMENTS_PROGRESS		3000

class DisplayManager
{
public:
	/**
	 * @brief These enum definitions are used in the code do address the different Seven segment displays. 
	 * 		  The numbers have to match with the place of the display in the array above.
	 */
	enum DisplayIDs {LOWER_DIGIT_MINUTE_DISPLAY = 0, HIGHER_DIGIT_MINUTE_DISPLAY = 1, LOWER_DIGIT_HOUR_DISPLAY = 2, HIGHER_DIGIT_HOUR_DISPLAY = 3};

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

	void AnimationManagersTemporaryOverride(Animator* OverrideanimationManager);
	void restoreAnimationManagers();

	//Animations
	Animator::ComplexAmination LoadingAnimation;
	void InitLoadingAnimation(uint16_t totalAnimationLength);

	CRGB leds[NUM_LEDS];
	#if APPEND_DOWN_LIGHTERS == false
		CRGB DownlightLeds[ADDITIONAL_LEDS];
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