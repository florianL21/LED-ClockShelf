/**
 * \file Segment.h
 * \author Florian Laschober
 * \brief Class definition of one single segment
 */

#ifndef __SEGMENT_H_
#define __SEGMENT_H_

#include <Arduino.h>
#include "AnimatableObject.h"
#define FASTLED_INTERNAL
#include "FastLED.h"


class AnimationEffects;

/**
 * \brief Single segment class definition. used to store which LEDs belong to one segment and applying animations on it.
 *
 */
class Segment: public AnimatableObject
{
public:
	/**
	 * \brief Direction in which the LED strip is wired in.
	 */
	enum direction {LEFT_TO_RIGHT = false, RIGHT_TO_LEFT = true, TOP_TO_BOTTTOM = false, BOTTOM_TO_TOP = true};

private:
    friend class AnimationEffects;

	uint8_t length;
	bool invertDirection;
	CRGB color;
	CRGB AnimationColor;
	CRGB* leds;

	void writeToLEDs(CRGB colorToSet);

	bool isOn();

public:
	/**
	 * \brief Construct a new Segment object
	 *
	 * \param LEDBuffer Array of all LEDs connected in one string. Substitution of this buffer is done internally
	 * \param indexOfFirstLEDInSegment Index of the first LED in the whole LED string that belongs to this segment
	 * \param segmentLength Number of LEDs which belong to this segment
	 * \param Direction Defines which way the LED segment is wired in
	 * \param segmentColor initial color of the segment
	 */
	Segment(CRGB LEDBuffer[], uint16_t indexOfFirstLEDInSegment, uint8_t segmentLength, direction Direction, CRGB segmentColor = CRGB::Black);

	/**
	 * \brief Destroy the Segment object
	 */
	~Segment();

	/**
	 * \brief Set the current animation state of the segment to a defined value
	 *
	 * \param currentState The current state of the animation starting at 0, relative to it's absolute animation length.
	 * 					   Over and undershoot is also possible.
	 */
	void tick(int32_t currentState);

	/**
	 * \brief sets the color of the segment without displaying the change
	 */
	void setColor(CRGB SegmentColor);

	/**
	 * \brief sets the color of the segment and updates it automatically in case the segment is turned on
	 */
	void updateColor(CRGB SegmentColor);


	/**
	 * \brief Write the current animation color to all LEDs that belong to this segment. Writes to the LED buffer
	 * 		  but relies on an external FastLED.show() call to actually write that change to the LEDs
	 */
	void display();

	/**
	 * \brief Turns off the leds of this segment but doesn't change the stored color of the segment
	 */
	void off();

	/**
	 * \brief Change tha animation color, also possible to do while an animation is in progress.
	 *
	 * \param newColor new color to use in for the current segment and animation
	 */
	void updateAnimationColor(CRGB newColor);
};


#endif
