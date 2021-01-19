#ifndef __ANIMATABLE_OBJECT_H_
#define __ANIMATABLE_OBJECT_H_

#include <Arduino.h>

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

class Animator;
class Segment;

class AnimatableObject
{
friend class Animator;
friend class Segment;
public:
	typedef void AnimationCallBack(void);
	typedef void (Animator::*ComplexAnimationCallBack)(AnimatableObject * sourceObject);
	uint8_t effect;
private:
	uint16_t AnimationDuration;
	uint64_t timeSinceLastTick;
	uint16_t tickLength;
	uint16_t tickState;
	uint16_t numStates;
	uint16_t smoothness;
	uint16_t numUnsmoothedStep;
	bool animationStarted;
	
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
	void setAnimationSmothing(uint16_t smoothness);
	uint16_t getAnimationDuration();
	void start();
	void reset();
	void stop();
	void done(); //gets called by animationHandler when the animation is finished
	uint16_t getState();
	virtual void onAnimationStart();
	virtual void onAnimationDone();
	virtual void setAnimationEffect(uint8_t newEffect);
public:
	virtual void tick();
	void setAnimationDoneCallback(AnimationCallBack* callback);
	void setAnimationStartCallback(AnimationCallBack* callback);

};

#endif