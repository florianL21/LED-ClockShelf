#include "Segment.h"

Segment::Segment(CRGB LEDBuffer[], uint16_t indexOfFirstLEDInSegment, uint8_t segmentLength, direction Direction, CRGB segmentColor) : AnimatableObject(0, 0)
{
	leds = &LEDBuffer[indexOfFirstLEDInSegment];
	invertDirection = Direction;
	length = segmentLength;
	color = segmentColor;
	AnimationColor = color;
	isOn = false;
	setAnimationSteps(length);
}

Segment::~Segment()
{

}

void Segment::display()
{
	isOn = true;
	writeToLEDs(color);
}

void Segment::writeToLEDs(CRGB colorToSet)
{
	for (int i = 0; i < length; i++)
	{
		leds[i] = colorToSet;
	}
}

void Segment::updateColor(CRGB SegmentColor)
{
	setColor(SegmentColor);
	updateAnimationColor(color);
	if(isOn == true)
	{
		display();
	}
}

void Segment::setColor(CRGB SegmentColor)
{
	color = SegmentColor;
	updateAnimationColor(color);
}

void Segment::displayColor(CRGB SegmentColor)
{
	setColor(SegmentColor);
	display();
}

void Segment::off()
{
	isOn = false;
	writeToLEDs(CRGB::Black);
}

void Segment::tick()
{
    if(effect != nullptr)
    {
		effect(leds, length, AnimationColor, numStates, getState(), invertDirection);
    }
}

void Segment::updateAnimationColor(CRGB newColor)
{
		AnimationColor = newColor;
}

void Segment::onAnimationStart()
{
	if(easing != nullptr)
	{
		easing->setTotalChangeInPosition(numStates);
		easing->setDuration(AnimationDuration);
	}
}

void Segment::setAnimationEffect(uint8_t newEffect)
{

}
