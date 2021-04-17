/**
 * \file AnimationEffects.cpp
 * \author Florian Laschober
 * \brief Implementation of the basic animations that are avaliable for all segments
 * 		  Requirements to such an animation function:
 * 			- All animations have to have the same prototype
 * 			- An animation function always has to set the state of all LEDs that it is affecting for every step. This is required because an
 * 			   animation can also be played backwards or multiple directions during the lifetime of one animation (for example a bounce easing)
 * 			- The animation always starts when the current step is 0, but undershoot is also possible so it also has to be considered what
 * 			  happens if current step goes negative. This should also result in a logical animation being displayed
 * 			- The current step can go higher than totalSteps, this would then be an overshoot. Same considerations as above should be taken into account.
 */

#include "AnimationEffects.h"

AnimatableObject::AnimationFunction AnimationEffects::AnimateOutToRight = &OutToRight;
AnimatableObject::AnimationFunction AnimationEffects::AnimateOutToBottom = &OutToRight;
AnimatableObject::AnimationFunction AnimationEffects::AnimateOutToLeft = &OutToLeft;
AnimatableObject::AnimationFunction AnimationEffects::AnimateOutToTop = &OutToLeft;
AnimatableObject::AnimationFunction AnimationEffects::AnimateInToRight = &InToRight;
AnimatableObject::AnimationFunction AnimationEffects::AnimateInToBottom = &InToRight;
AnimatableObject::AnimationFunction AnimationEffects::AnimateInToLeft = &InToLeft;
AnimatableObject::AnimationFunction AnimationEffects::AnimateInToTop = &InToLeft;
AnimatableObject::AnimationFunction AnimationEffects::AnimateInToMiddle = &InToMiddle;
AnimatableObject::AnimationFunction AnimationEffects::AnimateOutToMiddle = &OutToMiddle;
AnimatableObject::AnimationFunction AnimationEffects::AnimateOutFromMiddle = &OutFromMiddle;
AnimatableObject::AnimationFunction AnimationEffects::AnimateInFromMiddle = &InFromMiddle;
AnimatableObject::AnimationFunction AnimationEffects::AnimateMiddleDotFlash = &MiddleDotFlash;

void AnimationEffects::OutToRight(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    if(invert == true)
    {
        OutToLeft(leds, length, animationColor, totalSteps, currentStep, false);
        return;
    }
	uint16_t tailLength = length * ANIMATION_AFTERGLOW;
	int32_t lastFullyLitLED = map(currentStep, 0, totalSteps, 0, length + tailLength + 1);
    for (uint16_t i = 0; i < length; i++)
    {
        if(lastFullyLitLED <= i && lastFullyLitLED + length > i)
        {
            leds[i] = animationColor;
        }
        else
		{
			uint16_t microsteps = totalSteps / (length + tailLength);
			int32_t dimmingSteps = microsteps * tailLength;
			CRGB newColor = animationColor;
			if (i < lastFullyLitLED + length)
			{
				uint16_t startToDim = microsteps * i;
				if(currentStep < startToDim)
				{
					leds[i] = animationColor;
				}
				else
				{
					uint8_t dimDegree = constrain((((double)currentStep - startToDim) / ((double)dimmingSteps)) * 255.0, 0, 255);
					leds[i] = newColor.fadeToBlackBy(dimDegree);
				}
			}
			else
			{
				int32_t startToDim = microsteps * (i - length);
				if(currentStep > startToDim)
				{
					leds[i] = animationColor;
				}
				else
				{
					uint8_t dimDegree = constrain(((double)(currentStep - startToDim) / ((double)dimmingSteps) * -255.0), 0, 255);
					leds[i] = newColor.fadeToBlackBy(dimDegree);
				}
			}
		}
    }
}

void AnimationEffects::OutToLeft(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    if(invert == true)
    {
        OutToRight(leds, length, animationColor, totalSteps, currentStep, false);
        return;
    }
    OutToRight(leds, length, animationColor, totalSteps, -currentStep, false);
}

void AnimationEffects::InToRight(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
	if(invert == true)
    {
        InToLeft(leds, length, animationColor, totalSteps, currentStep, false);
        return;
    }
    OutToRight(leds, length, animationColor, totalSteps, currentStep - totalSteps, false);
}

void AnimationEffects::InToLeft(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    if(invert == true)
    {
        InToRight(leds, length, animationColor, totalSteps, currentStep, false);
        return;
    }
    OutToRight(leds, length, animationColor, totalSteps, (-currentStep) + totalSteps, false);
}

void AnimationEffects::InToMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
	//TBD
    InToRight(leds, length / 2, animationColor, totalSteps, currentStep, invert);
	InToLeft(&leds[length / 2], length / 2, animationColor, totalSteps, currentStep, invert);
}

void AnimationEffects::OutToMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    //TBD
}

void AnimationEffects::OutFromMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    //TBD
}

void AnimationEffects::InFromMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    //TBD
}

void AnimationEffects::MiddleDotFlash(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
	CRGB newColor = animationColor;
	uint8_t fadeAmount = 0;
	for (uint16_t i = 0; i < length; i++)
	{
		leds[i] = CRGB::Black;
	}
	if(currentStep < totalSteps / 2)
	{
		fadeAmount = map(currentStep, 0, totalSteps / 2, 255, 0);
	}
	else
	{
		fadeAmount = map(currentStep, totalSteps / 2, totalSteps, 0, 255);
	}
	leds[(length - 1) / 2] = newColor.fadeToBlackBy(fadeAmount);
    if(length % 2 == 0)
	{
		leds[(length - 1) / 2 + 1] = leds[(length - 1) / 2];
	}
}