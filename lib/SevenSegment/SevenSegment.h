#ifndef __SEVEN_SEGMENT_H_
#define __SEVEN_SEGMENT_H_

#include <Arduino.h>
#include "Segment.h"
#include "AnimatableObject.h"
#include "Animator.h"

/**
 * @brief The time it takes for one digit to morph into another
 */
#define DIGIT_ANIMATION_SPEED 400

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

	//animation inits
	void initAnimations();

	Animator::ComplexAmination Animate0to1;
	void InitAnimate0to1(uint16_t totalAnimationLength);
	Animator::ComplexAmination Animate1to2;
	void InitAnimate1to2(uint16_t totalAnimationLength);
	Animator::ComplexAmination Animate2to3;
	void InitAnimate2to3(uint16_t totalAnimationLength);
	Animator::ComplexAmination Animate3to4;
	void InitAnimate2to0(uint16_t totalAnimationLength);
	Animator::ComplexAmination Animate2to0;
	void InitAnimate2to1(uint16_t totalAnimationLength);
	Animator::ComplexAmination Animate2to1;
	void InitAnimate3to4(uint16_t totalAnimationLength);
	Animator::ComplexAmination Animate4to5;
	void InitAnimate4to5(uint16_t totalAnimationLength);
	Animator::ComplexAmination Animate5to6;
	void InitAnimate5to6(uint16_t totalAnimationLength);
	Animator::ComplexAmination Animate5to0;
	void InitAnimate5to0(uint16_t totalAnimationLength);
	Animator::ComplexAmination Animate6to7;
	void InitAnimate6to7(uint16_t totalAnimationLength);
	Animator::ComplexAmination Animate7to8;
	void InitAnimate7to8(uint16_t totalAnimationLength);
	Animator::ComplexAmination Animate8to9;
	void InitAnimate8to9(uint16_t totalAnimationLength);
	Animator::ComplexAmination Animate9to0;
	void InitAnimate9to0(uint16_t totalAnimationLength);
	Animator::ComplexAmination AnimateOFFto1;
	void InitAnimateOFFto1(uint16_t totalAnimationLength);
	Animator::ComplexAmination Animate1toOFF;
	void InitAnimate1toOFF(uint16_t totalAnimationLength);
	
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