#include "Segment.h"

Segment::Segment(CRGB LEDBuffer[], uint16_t indexOfFirstLEDInSegment, uint8_t segmentLength, direction Direction, CRGB segmentColor) : AnimatableObject(0, 0)
{
	leds = LEDBuffer;
	startIndex = indexOfFirstLEDInSegment;
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
	for (int i = startIndex; i < startIndex + length; i++)
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
	uint16_t index = startIndex;
	//settting the index
	if(effect == ANIMATE_OUT_TO_LEFT || effect == ANIMATE_IN_TO_LEFT || effect == AMINATE_SINGLE_LED_TO_LEFT) // also ANIMATE_OUT_TO_BOTTTOM and ANIMATE_OUT_TO_BOTTTOM and AMINATE_SINGLE_LED_TO_BOTTTOM
	{
		index = startIndex + (length - 1) - getState();
		if(effect == AMINATE_SINGLE_LED_TO_LEFT && getState() != 0)
		{
			leds[index + 1] = CRGB::Black;
		}
		leds[index] = AnimationColor;
	}
	else if(effect == ANIMATE_OUT_TO_RIGHT || effect == ANIMATE_IN_TO_RIGHT || effect == AMINATE_SINGLE_LED_TO_RIGHT) // also ANIMATE_IN_TO_TOP and ANIMATE_IN_TO_BOTTTOM also AMINATE_SINGLE_LED_TO_TOP
	{
		index = startIndex + getState();
		if(effect == AMINATE_SINGLE_LED_TO_RIGHT && getState() != 0)
		{
			leds[index - 1] = CRGB::Black;
		}
		leds[index] = AnimationColor;
	}
	else if(effect == ANIMATE_MIDDLE_DOT_FLASH)
	{
		writeToLEDs(CRGB::Black);
	}
}

void Segment::updateAnimationColor(CRGB newColor)
{
	if(
			effect == ANIMATE_IN_TO_RIGHT // also ANIMATE_IN_TO_TOP
		|| effect == ANIMATE_IN_TO_LEFT // also ANIMATE_IN_TO_BOTTTOM
		|| effect == AMINATE_SINGLE_LED_TO_RIGHT // also AMINATE_SINGLE_LED_TO_TOP
		|| effect == AMINATE_SINGLE_LED_TO_LEFT // also AMINATE_SINGLE_LED_TO_BOTTOM
		)
	{
		AnimationColor = newColor;
	}
}

void Segment::onAnimationStart()
{
	//setting the color 
	if(effect == ANIMATE_OUT_TO_LEFT || effect == ANIMATE_OUT_TO_RIGHT) // also ANIMATE_OUT_TO_TOP and ANIMATE_OUT_TO_BOTTTOM
	{
		setAnimationSteps(length);
		AnimationColor = CRGB::Black;
		if(getState() == 0)//set initial state
		{
			writeToLEDs(color);
		}
	}
	else if(
			effect == ANIMATE_IN_TO_RIGHT // also ANIMATE_IN_TO_TOP
		|| effect == ANIMATE_IN_TO_LEFT // also ANIMATE_IN_TO_BOTTTOM
		|| effect == AMINATE_SINGLE_LED_TO_RIGHT // also AMINATE_SINGLE_LED_TO_TOP
		|| effect == AMINATE_SINGLE_LED_TO_LEFT // also AMINATE_SINGLE_LED_TO_BOTTOM
		) 
	{
		setAnimationSteps(length);
		AnimationColor = color;
		if(getState() == 0)//set initial state
		{
			writeToLEDs(CRGB::Black);
		}
		if(effect == AMINATE_SINGLE_LED_TO_RIGHT)
		{
			leds[startIndex] = AnimationColor;
		}
		else if(effect == AMINATE_SINGLE_LED_TO_LEFT)
		{
			leds[startIndex + length - 1] = AnimationColor;
		}
	}
	else if(effect == ANIMATE_MIDDLE_DOT_FLASH)
	{
		setAnimationSteps(2);
		AnimationColor = color;
		if(getState() == 0)//set initial state
		{
			writeToLEDs(CRGB::Black);
		}
		//if segment length is uneven take the middle LED, if even take the middle 2
		if((length % 2) == 1)
		{
			leds[length / 2 + 1] = CRGB::White;
		}
		else
		{
			leds[length / 2] = CRGB::White;
			leds[length / 2 - 1] = CRGB::White;
		}
	}
}

void Segment::setAnimationEffect(uint8_t newEffect)
{
	if(invertDirection == true && newEffect < __LAST_DIRECTIONAL_EFFECT)
	{
		if(newEffect == ANIMATE_OUT_TO_RIGHT
			|| newEffect == ANIMATE_IN_TO_RIGHT
			|| newEffect == AMINATE_SINGLE_LED_TO_RIGHT)
		{
			effect = newEffect + 1;
		}
		else
		{
			effect = newEffect - 1;
		}
	}
	else
	{
		effect = newEffect;
	}
}