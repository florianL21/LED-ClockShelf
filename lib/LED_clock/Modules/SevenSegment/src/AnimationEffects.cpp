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

#define AFTERGLOW	0.4

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
	uint16_t tailLength = length * AFTERGLOW;
	int32_t lastFullyLitLED = map(currentStep, 0, totalSteps, 0, length + tailLength + 1);
	uint16_t microsteps = totalSteps / (length + tailLength);
	uint16_t dimmingSteps = microsteps * tailLength;
    for (uint16_t i = 0; i < length; i++)
    {
        if(lastFullyLitLED <= i && lastFullyLitLED+length > i)
        {
            leds[i] = animationColor;
        }
        else if (i < lastFullyLitLED+length)
        {
			CRGB newColor = animationColor;

			uint16_t startToDim = microsteps*i;
			if(currentStep<startToDim){
				leds[i] = animationColor;
			}else{
				uint8_t dimDegree = constrain((((double)currentStep-startToDim) / ((double)dimmingSteps)) * 255.0, 0, 255);
				leds[i] = newColor.fadeToBlackBy(dimDegree);
			}
        }else{
			CRGB newColor = animationColor;

			int32_t startToDim = microsteps*(i-length);
			if(currentStep>startToDim){
				leds[i] = animationColor;
			}else{
				uint8_t dimDegree = constrain(((((double)(currentStep-startToDim)) / ((double)dimmingSteps)) * -255.0), 0, 255);
				leds[i] = newColor.fadeToBlackBy(dimDegree);
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
    InToRight(leds, length / 2, animationColor, totalSteps, currentStep, invert);
	InToLeft(&leds[length / 2], length / 2, animationColor, totalSteps, currentStep, invert);
}

void AnimationEffects::OutToMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    
}

void AnimationEffects::OutFromMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    //TBD
}

void AnimationEffects::InFromMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert)
{
    //TBD
}