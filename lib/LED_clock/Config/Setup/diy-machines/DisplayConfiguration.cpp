/**
 * \file DisplayConfiguration.cpp
 * \author Florian laschober
 * \brief Configuration for the whole LED setup.
 */

//This configuration is for a 12h display without intermediate segments

#include "DisplayManager.h"

/**
 * \addtogroup DisplayConfiguration
 * \brief Configuration to tell the system how the LEDs are wired together and arranged.
 *  \{
 */

/**
 * \brief Each segment belongs to some display. This array defines the segment position within this one display.
 * 		  The order of these has to mach the order in which the LEDs are wired.
 */
SevenSegment::SegmentPosition DisplayManager::SegmentPositions[NUM_SEGMENTS] = {
	SevenSegment::RightTopSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::LeftTopSegment,
	SevenSegment::CenterSegment,
	SevenSegment::RightBottomSegment,
	SevenSegment::MiddleBottomSegment,
	SevenSegment::LeftBottomSegment,
	SevenSegment::RightTopSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::LeftTopSegment,
	SevenSegment::CenterSegment,
	SevenSegment::RightBottomSegment,
	SevenSegment::MiddleBottomSegment,
	SevenSegment::LeftBottomSegment,
	SevenSegment::RightTopSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::LeftTopSegment,
	SevenSegment::CenterSegment,
	SevenSegment::RightBottomSegment,
	SevenSegment::MiddleBottomSegment,
	SevenSegment::LeftBottomSegment,
	SevenSegment::RightTopSegment,
	SevenSegment::RightBottomSegment
};

/**
 * \brief Each segment has a direction, this is important for animation.
 * 		  The order of them is the same as #DisplayManager::SegmentPositions and the direction has to match the
 *        sequence in which the LEDs are wired.
 */
Segment::direction DisplayManager::SegmentDirections[NUM_SEGMENTS] = {
	Segment::BOTTOM_TO_TOP,
	Segment::RIGHT_TO_LEFT,
	Segment::TOP_TO_BOTTTOM,
	Segment::LEFT_TO_RIGHT,
	Segment::TOP_TO_BOTTTOM,
	Segment::RIGHT_TO_LEFT,
	Segment::BOTTOM_TO_TOP,
	Segment::BOTTOM_TO_TOP,
	Segment::RIGHT_TO_LEFT,
	Segment::TOP_TO_BOTTTOM,
	Segment::LEFT_TO_RIGHT,
	Segment::TOP_TO_BOTTTOM,
	Segment::RIGHT_TO_LEFT,
	Segment::BOTTOM_TO_TOP,
	Segment::BOTTOM_TO_TOP,
	Segment::RIGHT_TO_LEFT,
	Segment::TOP_TO_BOTTTOM,
	Segment::LEFT_TO_RIGHT,
	Segment::TOP_TO_BOTTTOM,
	Segment::RIGHT_TO_LEFT,
	Segment::BOTTOM_TO_TOP,
	Segment::TOP_TO_BOTTTOM,
	Segment::TOP_TO_BOTTTOM
};

/**
 * \brief Displays that are present. These define the displays in the order that is set in the #DisplayManager::diplayIndex array.
 */
SevenSegment::SevenSegmentMode DisplayManager::SegmentDisplayModes[NUM_DISPLAYS] = {
	SevenSegment::FULL_SEGMENT,
	SevenSegment::FULL_SEGMENT,
	SevenSegment::FULL_SEGMENT,
	SevenSegment::ONLY_ONE
};

/**
 * \brief These indicies correspond to the index of a Diplay in the array above (#DisplayManager::SegmentDisplayModes).
 * 		  They define which segment belongs to which Display in the order that they are wired in.
 *        The enum #DisplayIDs from \ref Configuration.h can also be used to create a more readable config.
 */
uint8_t DisplayManager::diplayIndex[NUM_SEGMENTS] = {
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	HIGHER_DIGIT_HOUR_DISPLAY,
	HIGHER_DIGIT_HOUR_DISPLAY
};

/** \}*/
