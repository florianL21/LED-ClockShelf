/**
 * \file Segment.cpp
 * \author Florian Laschober
 * \brief Implementation of the member functions of the Segment class
 */

#include "Segment.h"

Segment::Segment(CRGB LEDBuffer[], uint16_t indexOfFirstLEDInSegment, uint8_t segmentLength, direction Direction, CRGB segmentColor) : AnimatableObject(0, 0)
{
	leds = &LEDBuffer[indexOfFirstLEDInSegment];
	invertDirection = Direction;
	length = segmentLength;
	color = segmentColor;
	AnimationColor = color;
}

Segment::~Segment()
{

}

void Segment::display()
{
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
	if(animationStarted == false && isOn() == true)
	{
		display();
	}
}

void Segment::setColor(CRGB SegmentColor)
{
	color = SegmentColor;
	updateAnimationColor(color);
}

void Segment::off()
{
	writeToLEDs(CRGB::Black);
}

bool Segment::isOn()
{
	for (int i = 0; i < length; i++)
	{
		if(leds[i].r != 0 || leds[i].g != 0 || leds[i].b != 0 )
		{
			return true;
		}
	}
	return false;
}

void Segment::tick(int32_t currentState)
{
    if(effect != nullptr)
    {
		effect(leds, length, AnimationColor, numStates, currentState, invertDirection);
    }
}

void Segment::updateAnimationColor(CRGB newColor)
{
	AnimationColor = newColor;
}