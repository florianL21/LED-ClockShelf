/**
 * \file SevenSegment.h
 * \author Florian Laschober
 * \brief Definition of the SevenSegment class and some helper enums and definitions
 */

#ifndef __SEVEN_SEGMENT_H_
#define __SEVEN_SEGMENT_H_

#include <Arduino.h>
#include "Segment.h"
#include "AnimatableObject.h"
#include "Animator.h"
#include "Configuration.h"
#include "SegmentTransitions.h"
#include "AnimationEffects.h"

/**
 * \brief Enum for addressing certain Segments in the display for animation them
 */
enum SegmentPositions_t {
TOP_LEFT_SEGMENT 		= 0,
TOP_MIDDLE_SEGMENT	 	= 1,
TOP_RIGHT_SEGMENT	 	= 2,
CENTER_SEGMENT		 	= 3,
BOTTOM_LEFT_SEGMENT	 	= 4,
BOTTOM_MIDDLE_SEGMENT 	= 5,
BOTTOM_RIGHT_SEGMENT 	= 6
};

/**
 * \brief Helper for easier readability of the complex animation definitions
 */
#define SEGMENT_OFF		10

/**
 * \brief Class definition for SevenSegment which groups together all Segment objects which
 * 		  belong to together and provides some wrapper functions to manage all seven segments together
 */
class SevenSegment
{
public:
	/**
	 * \brief Segment positions for addressing the internal segment mapping table - Please use #SegmentPositions_t for all external uses instead.
	 */
	enum SegmentPosition {
		LeftTopSegment = 1 << TOP_LEFT_SEGMENT,
		MiddleTopSegment = 1 << TOP_MIDDLE_SEGMENT,
		RightTopSegment = 1 << TOP_RIGHT_SEGMENT,
		CenterSegment = 1 << CENTER_SEGMENT,
		LeftBottomSegment = 1 << BOTTOM_LEFT_SEGMENT,
		MiddleBottomSegment = 1 << BOTTOM_MIDDLE_SEGMENT,
		RightBottomSegment = 1 << BOTTOM_RIGHT_SEGMENT
	};

	/**
	 * \brief The mode of the seven segment display. This also defines which segments ave to be linked and which ones can be left out,
	 * 		  also which digits can be displayed by this paricular instance of the seven segment display
	 */
	enum SevenSegmentMode {
		FULL_SEGMENT, 	/** has 7 segments */
		HALF_SEGMENT, 	/** has only the 3 horizontal segments */
		ONLY_ONE		/** has only the right 2 vertical segments */
	};

private:
	Segment* Segments[7];
	SevenSegmentMode DsiplayMode;
	static uint8_t segmentMap[10];
	uint8_t currentValue;
	bool isAnimationInitialized;
	Animator* AnimationHandler;

	uint8_t getIndexOfSegment(SegmentPosition positionInDisplay);
	bool isConfigComplete();
	void DisplayNumberWithoutAnim(uint8_t value);
	Animator::ComplexAmination* getTransition(uint8_t from, uint8_t to);

public:

	/**
	 * \brief Construct a new Seven Segment object
	 *
	 * \param mode defines which digits can be displayed and which segments will not be assigned
	 * \param DisplayAnimationHandler Animation handler which will be resposible for refreshing this display.
	 */
	SevenSegment(SevenSegmentMode mode, Animator* DisplayAnimationHandler);

	/**
	 * \brief Destroy the Seven Segment object
	 */
	~SevenSegment();

	/**
	 * \brief Add a single segment to the Seven segment display
	 *
	 * \param segmentToAdd Segment which shall be added
	 * \param positionInDisplay Position of the added segment withing the seven segment display
	 */
	void add(Segment* segmentToAdd, SegmentPosition positionInDisplay);

	/**
	 * \brief Display a number on the display. If the display is not able to display the passed number nothing will happen
	 *
	 * \param value Number to display \range 0 - 9
	 */
	void DisplayNumber(uint8_t value);

	/**
	 * \brief Display a character on a Display. NOTE: Currently not implemented (only supports 0-9 as characters)
	 *
	 * \param value Number to display \range '0' - '9'
	 */
	void DisplayChar(char value);

	/**
	 * \brief Plays a fading in and out animation on the middle (or two middle, if segment length is even) LEDs of one or multiple segment/s
	 * 		  The function will internally display the animation on the right segments depending on the #SevenSegment::SevenSegmentMode
	 *
	 * \param numDots Number of dots to display \range 0-2
	 */
	void FlashMiddleDot(uint8_t numDots);

	/**
	 * \brief checks if a particular character can be displayed on this display.
	 *
	 * \param charToCheck Char which shall be checked for
	 * \return true if the char can be displayed
	 * \return false  if the char cannot be displayed
	 */
	bool canDisplay(char charToCheck);

	/**
	 * \brief Sets the animation color which will be displayed on the LEDs the next time an animation ticks
	 *
	 * \param color Color to set
	 */
	void setColor(CRGB color);

	/**
	 * \brief Sets the current and also the animation color which will be displayed on the LEDs the next time the LEDs are updated
	 *
	 * \param color Color to set
	 */
	void updateColor(CRGB color);

	/**
	 * \brief Turn all LEDs in this seven segment display off. will be pushed to the LEDs with the next call of FastLED.show()
	 */
	void off();
};


#endif
