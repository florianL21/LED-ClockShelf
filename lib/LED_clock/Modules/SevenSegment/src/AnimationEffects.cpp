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

#define AFTERGLOW	0.3

AnimationEffects::AnimationEffects()
{

}

AnimationEffects::~AnimationEffects()
{
}


void AnimationEffects::OutToRight(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    if(invert == true)
    {
        OutToLeft(leds, length, animationColor, totalSteps, currentStep, false);
        return;
    }
    for (uint16_t i = 0; i < length; i++)
    {
        if(map(currentStep, 0, totalSteps, 0, length + 1) <= i)
        {
            leds[i] = animationColor;
        }
        else
        {
            leds[i] = CRGB::Black;
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
    for (uint16_t i = 0; i < length; i++)
    {
        if(map(currentStep, 0, totalSteps, length, -1) <= i)
        {
            leds[i] = CRGB::Black;
        }
        else
        {
            leds[i] = animationColor;
        }
    }
}

void AnimationEffects::InToRight(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
	if(invert == true)
    {
        InToLeft(leds, length, animationColor, totalSteps, currentStep, false);
        return;
    }
    for (uint16_t i = 0; i < length; i++)
    {
        if(map(currentStep, 0, totalSteps, 0, length + 1) <= i)
        {
            leds[i] = CRGB::Black;
        }
        else
        {
            leds[i] = animationColor;
        }
    }
}

void AnimationEffects::InToLeft(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    if(invert == true)
    {
        InToRight(leds, length, animationColor, totalSteps, currentStep, false);
        return;
    }
    for (uint16_t i = 0; i < length; i++)
    {
        if(map(currentStep, 0, totalSteps, length, -1) <= i)
        {
            leds[i] = animationColor;
        }
        else
        {
            leds[i] = CRGB::Black;
        }
    }
}

void AnimationEffects::InToMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    for (uint16_t i = 0; i < length / 2 + 1; i++)
    {
        if(map(currentStep, 0, totalSteps, 0, length / 2 + 1) >= i)
        {
            leds[i] = animationColor;
			leds[length - 1 - i] = animationColor;
        }
        else
        {
            leds[i] = CRGB::Black;
			leds[length - 1 - i] = CRGB::Black;
        }
    }
}

void AnimationEffects::OutToMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    for (uint16_t i = 0; i < length / 2 + 1; i++)
    {
        if(map(currentStep, 0, totalSteps, 0, length / 2 + 1) <= i)
        {
            leds[i] = animationColor;
			leds[length - 1 - i] = animationColor;
        }
        else
        {
            leds[i] = CRGB::Black;
			leds[length - 1 - i] = CRGB::Black;
        }
    }
}

void AnimationEffects::OutFromMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    //TBD
}

void AnimationEffects::InFromMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    //TBD
}