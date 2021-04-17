/**
 * \file SevenSegment.cpp
 * \author Florian Laschober
 * \brief Implementations of the member functions of the SevenSegment class
 */

#include "SevenSegment.h"
/**
 * \brief defines the mapping of a number to the segments
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
}

//TODO: maybe put this into a loop, it takes a lot of memory
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

Animator::ComplexAmination* SevenSegment::getTransition(uint8_t from, uint8_t to)
{
	if(from <= 10 && to <= 10)
	{
		return TransformationLookupTable[from][to];
	}
	else
	{
		return nullptr;
	}
}

void SevenSegment::DisplayNumber(uint8_t value)
{
	if(DsiplayMode == HALF_SEGMENT) // do nothing if we are only dealing with a half segment
	{
		return;
	}
	Animator::ComplexAmination* anim = nullptr;
	if(DsiplayMode == ONLY_ONE)
	{
		if(currentValue != 1 && value == 1)
		{
			anim = getTransition(SEGMENT_OFF, 1);
		}else if(currentValue == 1 && value != 1)
		{
			anim = getTransition(1, SEGMENT_OFF);
		}
	}
	else
	{
		anim = getTransition(currentValue, value);
	}
	if(anim != nullptr)
	{
		AnimationHandler->PlayComplexAnimation(anim, (AnimatableObject**)Segments);
	}
	else
	{
		DisplayNumberWithoutAnim(value);
	}
	currentValue = value;
}

void SevenSegment::FlashMiddleDot(uint8_t numDots)
{
	if(DsiplayMode != ONLY_ONE)
	{
		if(numDots == 2)
		{
			AnimationHandler->startAnimation(Segments[getIndexOfSegment(MiddleTopSegment)], AnimationEffects::AnimateMiddleDotFlash, DOT_FLASH_SPEED);
			AnimationHandler->startAnimation(Segments[getIndexOfSegment(MiddleBottomSegment)], AnimationEffects::AnimateMiddleDotFlash, DOT_FLASH_SPEED);
		}
		else
		{
			AnimationHandler->startAnimation(Segments[getIndexOfSegment(CenterSegment)], AnimationEffects::AnimateMiddleDotFlash, DOT_FLASH_SPEED);
		}
	}
	else
	{
		AnimationHandler->startAnimation(Segments[getIndexOfSegment(RightBottomSegment)], AnimationEffects::AnimateMiddleDotFlash, DOT_FLASH_SPEED);
		AnimationHandler->startAnimation(Segments[getIndexOfSegment(RightTopSegment)], AnimationEffects::AnimateMiddleDotFlash, DOT_FLASH_SPEED);
	}
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
