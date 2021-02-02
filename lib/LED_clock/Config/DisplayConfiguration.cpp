#include "DisplayManager.h"
// Configuration for the whole LED setup.

/**
 * @brief Each segment belongs to one some Display. This array defines the segment position within this one display.
 * 		  The order of these has to mach the order in which the LEDs are wired
 */
SevenSegment::SegmentPosition DisplayManager::SegmentPositions[NUM_SEGMENTS] = {
	SevenSegment::MiddleBottomSegment,
	SevenSegment::RightBottomSegment,
	SevenSegment::RightTopSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::LeftTopSegment,
	SevenSegment::LeftBottomSegment,
	SevenSegment::CenterSegment,

	SevenSegment::CenterSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::MiddleBottomSegment,

	SevenSegment::MiddleBottomSegment,
	SevenSegment::RightBottomSegment,
	SevenSegment::RightTopSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::LeftTopSegment,
	SevenSegment::LeftBottomSegment,
	SevenSegment::CenterSegment,

	SevenSegment::CenterSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::MiddleBottomSegment,

	SevenSegment::MiddleBottomSegment,
	SevenSegment::RightBottomSegment,
	SevenSegment::RightTopSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::LeftTopSegment,
	SevenSegment::LeftBottomSegment,
	SevenSegment::CenterSegment,

	SevenSegment::CenterSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::MiddleBottomSegment,

	SevenSegment::MiddleBottomSegment,
	SevenSegment::RightBottomSegment,
	SevenSegment::RightTopSegment,
	SevenSegment::MiddleTopSegment,
	SevenSegment::LeftTopSegment,
	SevenSegment::LeftBottomSegment,
	SevenSegment::CenterSegment
};

/**
 * @brief Each segemnt has a direction, this is important for animation.
 * 		  The order of them is important and the direction has to mach the sequence in which the LEDs are wired
 */
Segment::direction DisplayManager::SegmentDirections[NUM_SEGMENTS] = {
	Segment::LEFT_TO_RIGHT,
	Segment::BOTTOM_TO_TOP,
	Segment::BOTTOM_TO_TOP,
	Segment::RIGHT_TO_LEFT,
	Segment::TOP_TO_BOTTTOM,
	Segment::TOP_TO_BOTTTOM,
	Segment::LEFT_TO_RIGHT,

	Segment::LEFT_TO_RIGHT,
	Segment::RIGHT_TO_LEFT,
	Segment::LEFT_TO_RIGHT,

	Segment::LEFT_TO_RIGHT,
	Segment::BOTTOM_TO_TOP,
	Segment::BOTTOM_TO_TOP,
	Segment::RIGHT_TO_LEFT,
	Segment::TOP_TO_BOTTTOM,
	Segment::TOP_TO_BOTTTOM,
	Segment::LEFT_TO_RIGHT,

	Segment::LEFT_TO_RIGHT,
	Segment::RIGHT_TO_LEFT,
	Segment::LEFT_TO_RIGHT,

	Segment::LEFT_TO_RIGHT,
	Segment::BOTTOM_TO_TOP,
	Segment::BOTTOM_TO_TOP,
	Segment::RIGHT_TO_LEFT,
	Segment::TOP_TO_BOTTTOM,
	Segment::TOP_TO_BOTTTOM,
	Segment::LEFT_TO_RIGHT,

	Segment::LEFT_TO_RIGHT,
	Segment::RIGHT_TO_LEFT,
	Segment::LEFT_TO_RIGHT,

	Segment::LEFT_TO_RIGHT,
	Segment::BOTTOM_TO_TOP,
	Segment::BOTTOM_TO_TOP,
	Segment::RIGHT_TO_LEFT,
	Segment::TOP_TO_BOTTTOM,
	Segment::TOP_TO_BOTTTOM,
	Segment::LEFT_TO_RIGHT
};

/**
 * @brief Displays that are present. These define the displays in the order that is set in the diplayIndex array.
 */
SevenSegment::SevenSegmentMode DisplayManager::SegmentDisplayModes[NUM_DISPLAYS] = {
	SevenSegment::FULL_SEGMENT,
	SevenSegment::HALF_SEGMENT,
	SevenSegment::FULL_SEGMENT,
	SevenSegment::HALF_SEGMENT,
	SevenSegment::FULL_SEGMENT,
	SevenSegment::HALF_SEGMENT,
	SevenSegment::FULL_SEGMENT
};

/**
 * @brief These indecies correspond to the index of a Diplay in the array above.
 * 		  They define which segment belongs to which Display in the order that they are wired in
 */
uint8_t DisplayManager::diplayIndex[NUM_SEGMENTS] = {
	HIGHER_DIGIT_HOUR_DISPLAY,
	HIGHER_DIGIT_HOUR_DISPLAY,
	HIGHER_DIGIT_HOUR_DISPLAY,
	HIGHER_DIGIT_HOUR_DISPLAY,
	HIGHER_DIGIT_HOUR_DISPLAY,
	HIGHER_DIGIT_HOUR_DISPLAY,
	HIGHER_DIGIT_HOUR_DISPLAY,

	FIRST_INTERMEDIATE_DISPLAY,
	FIRST_INTERMEDIATE_DISPLAY,
	FIRST_INTERMEDIATE_DISPLAY,

	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,
	LOWER_DIGIT_HOUR_DISPLAY,

	SECOND_INTERMEDIATE_DISPLAY,
	SECOND_INTERMEDIATE_DISPLAY,
	SECOND_INTERMEDIATE_DISPLAY,

	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,
	HIGHER_DIGIT_MINUTE_DISPLAY,

	THIRD_INTERMEDIATE_DISPLAY,
	THIRD_INTERMEDIATE_DISPLAY,
	THIRD_INTERMEDIATE_DISPLAY,

	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY,
	LOWER_DIGIT_MINUTE_DISPLAY
};