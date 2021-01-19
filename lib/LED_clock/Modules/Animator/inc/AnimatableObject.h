#ifndef __ANIMATABLE_OBJECT_H_
#define __ANIMATABLE_OBJECT_H_

#include <Arduino.h>
#define FASTLED_INTERNAL
#include "FastLED.h"

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

class Animator;
class Segment;

class AnimatableObject
{
public:
	typedef void AnimationCallBack(void);
	typedef void (Animator::*ComplexAnimationCallBack)(AnimatableObject * sourceObject);
    typedef void (*AnimationFunction)(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, uint16_t currentStep, bool invert);
private:
    friend class Animator;
    friend class Segment;

    uint8_t effect;
	uint16_t AnimationDuration;
	uint64_t timeSinceLastTick;
	uint16_t tickLength;
	uint16_t tickState;
	uint16_t numStates;
	uint16_t fps;
	uint16_t numUnsmoothedStep;
	bool animationStarted;
    AnimationFunction effectFunction;

	AnimationCallBack* finishedCallback;
	AnimationCallBack* startCallback;
	Animator* ComplexAnimationManager;
	ComplexAnimationCallBack ComplexAnimStartCallback;
	ComplexAnimationCallBack ComplexAnimDoneCallback;

protected:
	AnimatableObject();
	AnimatableObject(uint16_t OverallDuration, uint16_t steps);
	~AnimatableObject();

	void setAnimationDuration(uint16_t duration);
	void setAnimationSteps(uint16_t numSteps);
	void setAnimationFps(uint16_t setAnimationFps);
	uint16_t getAnimationDuration();
	void start();
	void reset();
	void stop();
	void done(); //gets called by animationHandler when the animation is finished
	uint16_t getState();
	virtual void onAnimationStart();
	virtual void onAnimationDone();
	virtual void setAnimationEffect(uint8_t newEffect);
    virtual void setAnimationEffect_new(AnimatableObject::AnimationFunction newEffect);
public:
	virtual void tick();
	void setAnimationDoneCallback(AnimationCallBack* callback);
	void setAnimationStartCallback(AnimationCallBack* callback);

};

#endif
