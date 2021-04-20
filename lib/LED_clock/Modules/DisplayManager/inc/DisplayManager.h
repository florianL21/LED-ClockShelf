/**
 * \file DisplayManager.h
 * \author Florian Laschober
 * \brief Display manager class definition
 */

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
#include "Animations.h"

/**
 * \brief Macro to shorten then name of the function to make usage easier in the animation config files.
 */
#define SEGMENT(POSITION, DISPLAY)		DisplayManager::getGlobalSegmentIndex(POSITION, DISPLAY)

/**
 * \brief The display manager is responsible to Manage all displays.
 *        It holds an instance to every display avaliable on the clock and manages the
 *        updating of all displays together.
 *
 */
class DisplayManager
{
private:
	//segment configurations
	static SevenSegment::SegmentPosition SegmentPositions[NUM_SEGMENTS];
	static Segment::direction SegmentDirections[NUM_SEGMENTS];
	static SevenSegment::SevenSegmentMode SegmentDisplayModes[NUM_DISPLAYS];
	static uint8_t diplayIndex[NUM_SEGMENTS];
	static DisplayManager* instance;

	Animator* animationManager;
	Segment* allSegments[NUM_SEGMENTS];
	SevenSegment* Displays[NUM_DISPLAYS];
	uint8_t currentLEDBrightness;
	uint8_t LEDBrightnessSmoothingStartPoint;
	uint8_t LEDBrightnessSetPoint;
	uint8_t LEDBrightnessCurrent;
	uint64_t lastBrightnessChange;
    CubicEase* lightSensorEasing;
	Animator::ComplexAnimationInstance* loadingAnimationID;

	uint32_t progressTotal;
	uint32_t currentProgressOffset;
	uint8_t currentProgressStep;
	Animator::ComplexAnimationInstance* loadingAnimationInst;

	typedef struct {
		SegmentPositions_t segmentPosition;
		DisplayIDs Display;
	} SegmentInstanceError;
	static DynamicList<SegmentInstanceError*>* SegmentIndexErrorList;

	CRGB leds[NUM_LEDS];
	#if APPEND_DOWN_LIGHTERS == false
		CRGB DownlightLeds[ADDITIONAL_LEDS];
	#endif

	#if ENABLE_LIGHT_SENSOR == true
		DynamicList<uint16_t> lightSensorMeasurements;
		uint64_t lastSensorMeasurement;
		uint8_t lightSensorBrightness;
		void takeBrightnessMeasurement();
	#endif

	void AnimationManagersTemporaryOverride(Animator* OverrideanimationManager);
	void restoreAnimationManagers();

	DisplayManager();
public:
    /**
     * \brief Destroys the Display Manager object and cause #DisplayManager::getInstance to create a new object the next time it is called
     */
	~DisplayManager();

    /**
     * \brief Get the instance of the DisplayManager object or create it if it was not yet instantiated.
     *
     * \return DisplayManager* returns the address to the DisplayManager object
     */
	static DisplayManager* getInstance();

	/**
	 * \brief Initialize all the segment using the configuration from \ref DisplayConfiguration.cpp
	 * \param indexOfFirstLed 	Index of the first led in the string that is part of a segment (usually 0)
	 * \param ledsPerSegment 	Sets the number of LEDs that are in one segment. this will be the same for all segments
	 * \param initialColor 		Sets the initial color of all the segments. This does not switch any segments on by it's own
	 * \param initBrightness	Sets the initial brightness of all the segments to avoid brigness jumps during startup
	 */
	void InitSegments(uint16_t indexOfFirstLed, uint8_t ledsPerSegment, CRGB initialColor, uint8_t initBrightness = 128);

	/**
	 * \brief Sets the color of all segments and updates it immediately for all segments that are currently switched on
	 * \param color Color to set the LEDs to
	 */
	void setAllSegmentColors(CRGB color);

	/**
	 * \brief Sets the color of the the segments which are displaying hours and updates it immediately for all segments that are currently switched on
	 * \param color Color to set the LEDs to
	 */
	void setHourSegmentColors(CRGB color);

	/**
	 * \brief Sets the color of the the segments which are displaying minutes and updates it immediately for all segments that are currently switched on
	 * \param color Color to set the LEDs to
	 */
	void setMinuteSegmentColors(CRGB color);

	/**
	 * \brief Displays the numbers given as they are on the respective displays
	 * \param Hour Number to show on the hours display
	 * \param Minute Number to show on the minutes display
	 */
	void displayRaw(uint8_t Hour, uint8_t Minute);

	/**
	 * \brief Display the time, Automatically convert between 24h and 12h formats
	 * \param hours 		Hours in a range of 0 to 24
	 * \param minutes 		Hours in a range of 0 to 59
	 */
	void displayTime(uint8_t hours, uint8_t minutes);

	/**
	 * \brief Display the remaining time on the timer. Always displays the highest possible output.
	 * 		  For example: If hour is anything else than 1 minutes will be displayed in the hour spot and seconds on the minute spot
	 * 		  on the display if possible.
	 * \param hours 		Hours in a range of 0 to 24
	 * \param minutes 		Hours in a range of 0 to 59
	 * \param seconds 		Seconds in a range of 0 to 59
	 */
	void displayTimer(uint8_t hours, uint8_t minutes, uint8_t seconds);

	/**
	 * \brief Has to be called cyclicly in the loop to enable live updating of the LEDs
	 */
	void handle();

	/**
	 * \brief Sets the color of the interrior LEDs and displays it immediately
	 */
	void setInternalLEDColor(CRGB color);

	/**
	 * \brief Sets the color of the seperation dot LEDs and displays it immediately
	 */
	void setDotLEDColor(CRGB color);

	/**
	 * \brief Starts the loading animation
	 */
	void showLoadingAnimation();

	/**
	 * \brief Stops the currently running animation after it is finished.
     *        This causes a looping animation to stop after its current cycle.
	 */
	void stopLoadingAnimation();

	/**
	 * \brief Wait until the currently set complex animation is finished.
	 */
	void waitForLoadingAnimationFinish();

	/**
	 * \brief Turns all displays off completely, Does not affect interior lights
	 */
	void turnAllSegmentsOff();

    /**
     * \brief Turn off all LEDs including internal LEDs
     */
	void turnAllLEDsOff();

	/**
	 * \brief start displaying a progress bar on the LEDs
	 * \param total How much progress there is to do in total
	 */
	void displayProgress(uint32_t total);

	/**
	 * \brief Update the progress bar
	 * \pre #DisplayManager::displayProgress has to be called once before updating the progress with this function
	 * \param progress How much progress was done already
	 */
	void updateProgress(uint32_t progress);

	/**
	 * \brief Use this delay instead of the Arduino delay to enable Display updates during the delay.
	 * \param timeInMs Delay time in ms
	 */
	void delay(uint32_t timeInMs);

	/**
	 * \brief Sets the Brightness globally for all leds
	 * \param brightness value between 0 for lowest, and 255 for the highes brightness
	 * \param enableSmoothTransition If true the LEDs will transition to the new value smoothly
	 */
	void setGlobalBrightness(uint8_t brightness, bool enableSmoothTransition = true);

	/**
	 * \brief Calling the Flash dot animation for the appropriate segments in the middle of the clock face
	 */
	void flashSeperationDot(uint8_t numDots);

    /**
     * \brief Used for testing purposes
     */
    void test();

    /**
     * \brief get the index of a segment in regards to it's position on the clock face.
     *  	  This makes writing animations a lot easier as it will act as an abstraction layer between the animation
     *        config and the display config
     *
     * \param segmentPosition Position of a segment in the seven segment display
     * \param Display Which display should be targeted
     * \return int16_t index of the Segment in the #DisplayManager::SegmentPositions array
     */
	static int16_t getGlobalSegmentIndex(SegmentPositions_t segmentPosition, DisplayIDs Display);

    /**
     * \brief Debugging function which will print out any errors that occurred when using the
     *        #DisplayManager::getGlobalSegmentIndex function.
     *        Especially useful for debugging weirdly behaving animations as animations will be configured before the
     *        Serial connection is up. If an error was detected by the #DisplayManager::getGlobalSegmentIndex function a
     *        message will be added to a buffer which can then be printed out using this function.
     */
	static void printAnimationInitErrors();
};


#endif
