/**
 * \file DisplayConfiguration.cpp
 * \author Florian laschober
 * \brief Configuration for the whole LED setup.
 *
 */

//This configuration is for a 12h display with intermediate segments

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
	SevenSegment::MiddleBottomSegment,
	SevenSegment::MiddleBottomSegment,
	SevenSegment::MiddleBottomSegment,
	SevenSegment::MiddleBottomSegment,
	SevenSegment::MiddleBottomSegment,
	SevenSegment::MiddleBottomSegment,
	SevenSegment::RightBottomSegment,
	SevenSegment::RightTopSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::RightTopSegment,//Right because this is the single 1 segment in the beginning
	SevenSegment::RightBottomSegment,
	SevenSegment::CenterSegment,
	SevenSegment::LeftBottomSegment,
	SevenSegment::LeftTopSegment,
	SevenSegment::CenterSegment,
	SevenSegment::RightBottomSegment,
	SevenSegment::RightTopSegment,
	SevenSegment::CenterSegment,
	SevenSegment::LeftBottomSegment,
	SevenSegment::LeftTopSegment,
	SevenSegment::CenterSegment,
	SevenSegment::RightBottomSegment,
	SevenSegment::RightTopSegment,
	SevenSegment::CenterSegment,
	SevenSegment::LeftBottomSegment,
	SevenSegment::LeftTopSegment,
	SevenSegment::CenterSegment
};

/**
 * \brief Each segment has a direction, this is important for animation.
 * 		  The order of them is the same as #DisplayManager::SegmentPositions and the direction has to match the
 *        sequence in which the LEDs are wired.
 */
Segment::direction DisplayManager::SegmentDirections[NUM_SEGMENTS] = {
	Segment::LEFT_TO_RIGHT,
	Segment::LEFT_TO_RIGHT,
	Segment::LEFT_TO_RIGHT,
	Segment::LEFT_TO_RIGHT,
	Segment::LEFT_TO_RIGHT,
	Segment::LEFT_TO_RIGHT,
	Segment::BOTTOM_TO_TOP,
	Segment::BOTTOM_TO_TOP,
	Segment::RIGHT_TO_LEFT,
	Segment::RIGHT_TO_LEFT,
	Segment::RIGHT_TO_LEFT,
	Segment::RIGHT_TO_LEFT,
	Segment::RIGHT_TO_LEFT,
	Segment::RIGHT_TO_LEFT,
	Segment::TOP_TO_BOTTTOM,
	Segment::TOP_TO_BOTTTOM,
	Segment::LEFT_TO_RIGHT,
	Segment::TOP_TO_BOTTTOM,
	Segment::TOP_TO_BOTTTOM,
	Segment::LEFT_TO_RIGHT,
	Segment::TOP_TO_BOTTTOM,
	Segment::TOP_TO_BOTTTOM,
	Segment::LEFT_TO_RIGHT,
	Segment::TOP_TO_BOTTTOM,
	Segment::TOP_TO_BOTTTOM,
	Segment::LEFT_TO_RIGHT,
	Segment::TOP_TO_BOTTTOM,
	Segment::TOP_TO_BOTTTOM,
	Segment::LEFT_TO_RIGHT,
	Segment::TOP_TO_BOTTTOM,
	Segment::TOP_TO_BOTTTOM,
	Segment::LEFT_TO_RIGHT
};

/**
 * \brief Displays that are present. These define the displays in the order that is set in the #DisplayManager::diplayIndex array.
 */
SevenSegment::SevenSegmentMode DisplayManager::SegmentDisplayModes[NUM_DISPLAYS] = {
	SevenSegment::ONLY_ONE,
	SevenSegment::HALF_SEGMENT,
	SevenSegment::FULL_SEGMENT,
	SevenSegment::HALF_SEGMENT,
	SevenSegment::FULL_SEGMENT,
	SevenSegment::HALF_SEGMENT,
	SevenSegment::FULL_SEGMENT
};

/**
 * \brief These indicies correspond to the index of a Diplay in the array above (#DisplayManager::SegmentDisplayModes).
 * 		  They define which segment belongs to which Display in the order that they are wired in.
 *        The enum #DisplayIDs from \ref Configuration.h can also be used to create a more readable config.
 */
uint8_t DisplayManager::diplayIndex[NUM_SEGMENTS] = {
	FIRST_INTERMEDIATE_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	SECOND_INTERMEDIATE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	THIRD_INTERMEDIATE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	THIRD_INTERMEDIATE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	SECOND_INTERMEDIATE_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	FIRST_INTERMEDIATE_DISPLAY,
	HIGHER_DIGIT_HOUR_DISPLAY,
	HIGHER_DIGIT_HOUR_DISPLAY,
	FIRST_INTERMEDIATE_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	SECOND_INTERMEDIATE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	THIRD_INTERMEDIATE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY
};

/** \}*/
