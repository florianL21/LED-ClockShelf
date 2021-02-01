#ifndef __SEVEN_SEGMENT_H_
#define __SEVEN_SEGMENT_H_

#include <Arduino.h>
#include "Segment.h"
#include "AnimatableObject.h"
#include "Animator.h"
#include "Configuration.h"
#include "SegmentTransitions.h"
#include "AnimationEffects.h"

enum SegmentPositions_t {
TOP_LEFT_SEGMENT 		= 0,
TOP_MIDDLE_SEGMENT	 	= 1,
TOP_RIGHT_SEGMENT	 	= 2,
CENTER_SEGMENT		 	= 3,
BOTTOM_LEFT_SEGMENT	 	= 4,
BOTTOM_MIDDLE_SEGMENT 	= 5,
BOTTOM_RIGHT_SEGMENT 	= 6
};

#define SEGMENT_OFF		10

class SevenSegment : AnimatableObject
{
public:
	enum SegmentPosition {
		LeftTopSegment = 1 << TOP_LEFT_SEGMENT,
		MiddleTopSegment = 1 << TOP_MIDDLE_SEGMENT,
		RightTopSegment = 1 << TOP_RIGHT_SEGMENT,
		CenterSegment = 1 << CENTER_SEGMENT,
		LeftBottomSegment = 1 << BOTTOM_LEFT_SEGMENT,
		MiddleBottomSegment = 1 << BOTTOM_MIDDLE_SEGMENT,
		RightBottomSegment = 1 << BOTTOM_RIGHT_SEGMENT
	};

	enum SevenSegmentMode {
		FULL_SEGMENT, 	// has 7 segments
		HALF_SEGMENT, 	// has only the 3 horizontal segments
		ONLY_ONE		// has only the right 2 vertical segments
	};

private:
	Segment* Segments[7];
	SevenSegmentMode DsiplayMode;
	static uint8_t segmentMap[10];
	uint8_t currentValue;
	bool isAnimationInitialized;

	uint8_t getIndexOfSegment(SegmentPosition positionInDisplay);
	bool isConfigComplete();
	void DisplayNumberWithoutAnim(uint8_t value);
	Animator::ComplexAmination* getTransition(uint8_t from, uint8_t to);

public:

	Animator* AnimationHandler;

	SevenSegment(SevenSegmentMode mode, Animator* DisplayAnimationHandler);
	~SevenSegment();
	void add(Segment* segmentToAdd, SegmentPosition positionInDisplay);
	void DisplayNumber(uint8_t value);
	void DisplayChar(char value);
	void FlashMiddleDot();
	bool canDisplay(char charToCheck);
	void setColor(CRGB color);
	void updateColor(CRGB color);
	void displayColor(CRGB color);
	void off();
	void addAnimator(Animator* AnimationManager);
};


#endif
