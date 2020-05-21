#include "SevenSegment.h"
/**
 * @brief defines the mapping of a number to the segments
 */
uint8_t SevenSegment::segmentMap[10] = {
	LeftTopSegment | MiddleTopSegment | RightTopSegment | LeftBottomSegment | MiddleBottomSegment | RightBottomSegment, // 0
	RightTopSegment | RightBottomSegment, // 1
	MiddleTopSegment | RightTopSegment | CenterSegment | LeftBottomSegment | MiddleBottomSegment, // 2
	MiddleTopSegment | RightTopSegment | CenterSegment | MiddleBottomSegment | RightBottomSegment, // 3
	LeftTopSegment | RightTopSegment | CenterSegment | RightBottomSegment, // 4
	LeftTopSegment | MiddleTopSegment | CenterSegment | MiddleBottomSegment | RightBottomSegment, // 5
	LeftTopSegment | MiddleTopSegment | CenterSegment | LeftBottomSegment | MiddleBottomSegment | RightBottomSegment, // 6
	MiddleTopSegment | RightTopSegment | RightBottomSegment, // 7
	LeftTopSegment | MiddleTopSegment | RightTopSegment | CenterSegment | LeftBottomSegment | MiddleBottomSegment | RightBottomSegment, // 8
	LeftTopSegment | MiddleTopSegment | RightTopSegment | CenterSegment | MiddleBottomSegment | RightBottomSegment // 9
};

SevenSegment::SevenSegment(SevenSegmentMode mode, Animator* DisplayAnimationHandler)
{
	DsiplayMode = mode;
	AnimationHandler = DisplayAnimationHandler;
	isAnimationInitialized = false;
	for (uint8_t i = 0; i < 7; i++)
	{
		Segments[i] = nullptr;
	}
}

SevenSegment::~SevenSegment()
{
}

bool SevenSegment::isConfigComplete()
{
	if(DsiplayMode == FULL_SEGMENT)
	{
		for (uint8_t i = 0; i < 7; i++)
		{
			if(Segments[i] == nullptr)
			{
				return false;
			}
		}
		return true;
	}
	else if(DsiplayMode == HALF_SEGMENT)
	{
		return Segments[getIndexOfSegment(MiddleTopSegment)] != nullptr && Segments[getIndexOfSegment(CenterSegment)] != nullptr && Segments[getIndexOfSegment(MiddleBottomSegment)] != nullptr;
	}
	else if(DsiplayMode == ONLY_ONE)
	{
		return Segments[getIndexOfSegment(RightBottomSegment)] != nullptr && Segments[getIndexOfSegment(RightTopSegment)] != nullptr;
	}
	return false;
}

void SevenSegment::initAnimations()
{
	//make sure to only ever initialize the animations once otherwise we have a HUGE memory leak.
	//TODO: maybe add a cleanup routine if dynamic changing of segments is required
	if(isAnimationInitialized == false)
	{
		isAnimationInitialized = true;
		InitAnimate0to1(DIGIT_ANIMATION_SPEED);
		InitAnimate1to2(DIGIT_ANIMATION_SPEED);
		InitAnimate2to3(DIGIT_ANIMATION_SPEED);
		InitAnimate2to0(DIGIT_ANIMATION_SPEED);
		InitAnimate2to1(DIGIT_ANIMATION_SPEED);
		InitAnimate3to4(DIGIT_ANIMATION_SPEED);
		InitAnimate4to5(DIGIT_ANIMATION_SPEED);
		InitAnimate5to6(DIGIT_ANIMATION_SPEED);
		InitAnimate5to0(DIGIT_ANIMATION_SPEED);
		InitAnimate6to7(DIGIT_ANIMATION_SPEED);
		InitAnimate7to8(DIGIT_ANIMATION_SPEED);
		InitAnimate8to9(DIGIT_ANIMATION_SPEED);
		InitAnimate9to0(DIGIT_ANIMATION_SPEED);
		InitAnimateOFFto1(DIGIT_ANIMATION_SPEED);
		InitAnimate1toOFF(DIGIT_ANIMATION_SPEED);
	}
	else
	{
		Serial.println("[W] Animations were not initialized again. This should not happen! Check your seven segment init routines!");
	}
}

uint8_t SevenSegment::getIndexOfSegment(SegmentPosition positionInDisplay)
{
	uint8_t segID = 0;
	while(positionInDisplay >> segID != 0x01)
	{
		segID++;
		if(segID >= 7) // make sure we don't get stuck in an endless loop here
		{
			Serial.println("Failed to find segment ID this should not be possible");
			return 6; // and that the value is still valid.
		}
	}
	return segID;
}

void SevenSegment::add(Segment* segmentToAdd, SegmentPosition positionInDisplay)
{
	Segments[getIndexOfSegment(positionInDisplay)] = segmentToAdd;
	AnimationHandler->add(segmentToAdd);
	if(isConfigComplete() == true)
	{
		initAnimations();
	}
}

void SevenSegment::DisplayNumberWithoutAnim(uint8_t value)
{
	uint8_t currentSegmentMap = 0x00;
	if((value >= 0 && value <= 9 && DsiplayMode == FULL_SEGMENT) || (value == 1 && DsiplayMode == ONLY_ONE)) //check if value can be displayed otherwise turn off all segments
	{
		currentSegmentMap = segmentMap[value];
	}

	Segment* CurrentSegment = Segments[getIndexOfSegment(LeftTopSegment)];
	if(CurrentSegment != nullptr)
	{
		currentSegmentMap & LeftTopSegment ? CurrentSegment->display() : CurrentSegment->off();
	}

	CurrentSegment = Segments[getIndexOfSegment(MiddleTopSegment)];
	if(CurrentSegment != nullptr)
	{
		currentSegmentMap & MiddleTopSegment ? CurrentSegment->display() : CurrentSegment->off();
	}

	CurrentSegment = Segments[getIndexOfSegment(RightTopSegment)];
	if(CurrentSegment != nullptr)
	{
		currentSegmentMap & RightTopSegment ? CurrentSegment->display() : CurrentSegment->off();
	}

	CurrentSegment = Segments[getIndexOfSegment(CenterSegment)];
	if(CurrentSegment != nullptr)
	{
		currentSegmentMap & CenterSegment ? CurrentSegment->display() : CurrentSegment->off();
	}

	CurrentSegment = Segments[getIndexOfSegment(LeftBottomSegment)];
	if(CurrentSegment != nullptr)
	{
		currentSegmentMap & LeftBottomSegment  ? CurrentSegment->display() : CurrentSegment->off();
	}

	CurrentSegment = Segments[getIndexOfSegment(MiddleBottomSegment)];
	if(CurrentSegment != nullptr)
	{
		currentSegmentMap & MiddleBottomSegment ? CurrentSegment->display() : CurrentSegment->off();
	}

	CurrentSegment = Segments[getIndexOfSegment(RightBottomSegment)];
	if(CurrentSegment != nullptr)
	{
		currentSegmentMap & RightBottomSegment ? CurrentSegment->display() : CurrentSegment->off();
	}
}

void SevenSegment::DisplayNumber(uint8_t value)
{
	if(DsiplayMode == HALF_SEGMENT) // do nothing if we are only dealing with a half segment
	{
		return;
	}

	//TODO: fix this hack
	if(DsiplayMode == ONLY_ONE)
	{
		if(currentValue != 1 && value == 1)
		{
			AnimationHandler->PlayComplexAnimation(&AnimateOFFto1);
		}else if(currentValue == 1 && value != 1)
		{
			AnimationHandler->PlayComplexAnimation(&Animate1toOFF);
		} else
		{
			DisplayNumberWithoutAnim(value);
		}
		
	}
	else
	{
		if(currentValue == 0 && value == 1)
		{
			AnimationHandler->PlayComplexAnimation(&Animate0to1);
		}
		else if(currentValue == 1 && value == 2)
		{
			AnimationHandler->PlayComplexAnimation(&Animate1to2);
		}
		else if(currentValue == 2 && value == 3)
		{
			AnimationHandler->PlayComplexAnimation(&Animate2to3);
		}
		else if(currentValue == 2 && value == 0)
		{
			AnimationHandler->PlayComplexAnimation(&Animate2to0);
		}
		else if(currentValue == 2 && value == 1)
		{
			AnimationHandler->PlayComplexAnimation(&Animate2to1);
		}
		else if(currentValue == 3 && value == 4)
		{
			AnimationHandler->PlayComplexAnimation(&Animate3to4);
		}
		else if(currentValue == 4 && value == 5)
		{
			AnimationHandler->PlayComplexAnimation(&Animate4to5);
		}
		else if(currentValue == 5 && value == 6)
		{
			AnimationHandler->PlayComplexAnimation(&Animate5to6);
		}
		else if(currentValue == 5 && value == 0)
		{
			AnimationHandler->PlayComplexAnimation(&Animate5to0);
		}
		else if(currentValue == 6 && value == 7)
		{
			AnimationHandler->PlayComplexAnimation(&Animate6to7);
		}
		else if(currentValue == 7 && value == 8)
		{
			AnimationHandler->PlayComplexAnimation(&Animate7to8);
		}
		else if(currentValue == 8 && value == 9)
		{
			AnimationHandler->PlayComplexAnimation(&Animate8to9);
		}
		else if(currentValue == 9 && value == 0)
		{
			AnimationHandler->PlayComplexAnimation(&Animate9to0);
		} else
		{
			DisplayNumberWithoutAnim(value);
		}
	}
	currentValue = value;
}

void SevenSegment::setColor(CRGB color)
{
	for (uint8_t i = 0; i < 7; i++)
	{
		if(Segments[i] != nullptr)
		{
			Segments[i]->setColor(color);
		}
	}
}

void SevenSegment::updateColor(CRGB color)
{
	for (uint8_t i = 0; i < 7; i++)
	{
		if(Segments[i] != nullptr)
		{
			Segments[i]->updateColor(color);
		}
	}
}

void SevenSegment::displayColor(CRGB color)
{
	setColor(color);
	DisplayNumber(currentValue);
}

void SevenSegment::off()
{
	for (uint8_t i = 0; i < 7; i++)
	{
		if(Segments[i] != nullptr)
		{
			Segments[i]->off();
		}
	}
}

void SevenSegment::addAnimator(Animator* AnimationManager)
{
	for (uint8_t i = 0; i < 7; i++)
	{
		if(Segments[i] != nullptr)
		{
			AnimationManager->add(Segments[i]);
		}
	}
}

bool SevenSegment::canDisplay(char charToCheck)
{
	if(charToCheck > 127)
	{
		return false;
	}
	switch (DsiplayMode)
	{
	case FULL_SEGMENT:
		return charToCheck <= 9;
	case ONLY_ONE:
		return charToCheck == 1;
	case HALF_SEGMENT:
		return charToCheck == ':';
	default:
		return false;
	}
}

void SevenSegment::DisplayChar(char value)
{
	if(value >= '0' && value <= '9')
	{
		DisplayNumber(value - '0');
	}
}