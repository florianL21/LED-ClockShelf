#ifndef __SEVEN_SEGMENT_H_
#define __SEVEN_SEGMENT_H_

#include <Arduino.h>
#include "Segment.h"
#include "AnimatableObject.h"
#include "Animator.h"
#include "Configuration.h"
#include "SegmentTransitions.h"

class SevenSegment : AnimatableObject
{
public:
	enum SegmentPosition {
		LeftTopSegment = 0x01,
		MiddleTopSegment = 0x02,
		RightTopSegment = 0x04,
		CenterSegment = 0x08,
		LeftBottomSegment = 0x10,
		MiddleBottomSegment = 0x20,
		RightBottomSegment = 0x40,
		InvalidSegment = 0x50
	};

	enum SevenSegmentMode {
		FULL_SEGMENT,
		HALF_SEGMENT,
		ONLY_ONE
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

public:

	Animator* AnimationHandler;

	SevenSegment(SevenSegmentMode mode, Animator* DisplayAnimationHandler);
	~SevenSegment();
	void add(Segment* segmentToAdd, SegmentPosition positionInDisplay);
	void DisplayNumber(uint8_t value);
	void DisplayChar(char value);
	bool canDisplay(char charToCheck);
	void setColor(CRGB color);
	void updateColor(CRGB color);
	void displayColor(CRGB color);
	void off();
	void addAnimator(Animator* AnimationManager);
};


#endif