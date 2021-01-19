#ifndef __ANIMATION_EFFECT_H_
#define __ANIMATION_EFFECT_H_

#include <Arduino.h>
#include "AnimatableObject.h"
#include "Segment.h"

// ANIMATE_IN_TO_RIGHT = 2,
// ANIMATE_IN_TO_BOTTOM = 2,
// ANIMATE_IN_TO_LEFT = 3,
// ANIMATE_IN_TO_TOP = 3,
// AMINATE_SINGLE_LED_TO_RIGHT = 4,
// AMINATE_SINGLE_LED_TO_BOTTOM = 4,
// AMINATE_SINGLE_LED_TO_LEFT = 5,
// AMINATE_SINGLE_LED_TO_TOP = 5,


class AnimationEffects
{
private:
    static void OutToRight(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, uint16_t currentStep, bool invert);
    static void OutToLeft(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, uint16_t currentStep, bool invert);
    static void InToRight(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, uint16_t currentStep, bool invert);
    static void InToLeft(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, uint16_t currentStep, bool invert);
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

    static AnimatableObject::AnimationFunction invert(AnimatableObject::AnimationFunction effectToInvert);
};



#endif
