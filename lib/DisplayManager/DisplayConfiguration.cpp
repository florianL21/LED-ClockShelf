#include "DisplayManager.h"
// Configuration the whole LED setup.

// Each segment belongs to one some Display. This array defines the segment position within this one display.
// The order of these has to mach the order in which the LEDs are wired
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
	SevenSegment::RightTopSegment,//Right because this is the single 1 segement in the beginning
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

// Each segemnt has a direction, this is important for animation. 
// The order of them is important and the direction has to mach the sequence in which the LEDs are wired
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

// Displays that are present. These define the displays from left to right of the shelf.
SevenSegment::SevenSegmentMode DisplayManager::SegmentDisplayModes[NUM_DISPLAYS] = {
	SevenSegment::ONLY_ONE,
	SevenSegment::HALF_SEGMENT,
	SevenSegment::FULL_SEGMENT,
	SevenSegment::HALF_SEGMENT,
	SevenSegment::FULL_SEGMENT,
	SevenSegment::HALF_SEGMENT,
	SevenSegment::FULL_SEGMENT
};

// These indecies correspond to the index of a Diplay in the array above. 
// They define which segment belongs to which Display in the order that they are wired in
uint8_t DisplayManager::diplayIndex[NUM_SEGMENTS] = {
	1,
	2,
	3,
	4,
	5,
	6,
	6,
	6,
	6,
	5,
	4,
	3,
	2,
	1,
	0,
	0,
	1,
	2,
	2,
	2,
	2,
	2,
	3,
	4,
	4,
	4,
	4,
	4,
	5,
	6,
	6,
	6
};