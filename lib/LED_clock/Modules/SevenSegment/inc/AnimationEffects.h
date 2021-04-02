/**
 * \file AnimationEffects.h
 * \author Florian Laschober
 * \brief All avaliable animation effects which can be applied to sone segment are listed here
 */

#ifndef __ANIMATION_EFFECT_H_
#define __ANIMATION_EFFECT_H_

#include <Arduino.h>
#include "AnimatableObject.h"
#include "Segment.h"
#include "Configuration.h"

class AnimationEffects
{
private:
    static void OutToRight(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert);
    static void OutToLeft(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert);
    static void InToRight(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert);
    static void InToLeft(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert);
	static void InToMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert);
	static void OutToMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert);
	static void OutFromMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert);
	static void InFromMiddle(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert);
    static void MiddleDotFlash(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert);
    AnimationEffects();
public:
    ~AnimationEffects();

    static AnimatableObject::AnimationFunction AnimateOutToRight;
    static AnimatableObject::AnimationFunction AnimateOutToBottom;
    static AnimatableObject::AnimationFunction AnimateOutToLeft;
    static AnimatableObject::AnimationFunction AnimateOutToTop;
    static AnimatableObject::AnimationFunction AnimateInToRight;
    static AnimatableObject::AnimationFunction AnimateInToBottom;
    static AnimatableObject::AnimationFunction AnimateInToLeft;
    static AnimatableObject::AnimationFunction AnimateInToTop;
	static AnimatableObject::AnimationFunction AnimateInToMiddle;
	static AnimatableObject::AnimationFunction AnimateOutToMiddle;
	static AnimatableObject::AnimationFunction AnimateOutFromMiddle;
	static AnimatableObject::AnimationFunction AnimateInFromMiddle;
    static AnimatableObject::AnimationFunction AnimateMiddleDotFlash;
};



#endif
