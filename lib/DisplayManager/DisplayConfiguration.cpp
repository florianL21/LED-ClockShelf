#include "DisplayManager.h"
// Configuration the whole LED setup.

/**
 * @brief Each segment belongs to one some Display. This array defines the segment position within this one display.
 * 		  The order of these has to mach the order in which the LEDs are wired
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
 * @brief Each segemnt has a direction, this is important for animation. 
 * 		  The order of them is important and the direction has to mach the sequence in which the LEDs are wired
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
 * @brief Displays that are present. These define the displays in the order that is set in the diplayIndex array.
 */
SevenSegment::SevenSegmentMode DisplayManager::SegmentDisplayModes[NUM_DISPLAYS] = {
	SevenSegment::FULL_SEGMENT,
	SevenSegment::FULL_SEGMENT,
	SevenSegment::FULL_SEGMENT,
	SevenSegment::ONLY_ONE
};

/**
 * @brief These indecies correspond to the index of a Diplay in the array above.
 * 		  They define which segment belongs to which Display in the order that they are wired in
 */
uint8_t DisplayManager::diplayIndex[NUM_SEGMENTS] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	3,
	3
};