#include "AnimatableObject.h"

AnimatableObject::AnimatableObject()
{
	AnimatableObject(0, 0);
}

AnimatableObject::AnimatableObject(uint16_t OverallDuration, uint16_t steps)
{
	AnimationDuration = OverallDuration;
	tickLength = 20;
	animationStarted = false;
	fps = 0;
	numStates = 0;
	finishedCallback = nullptr;
	startCallback = nullptr;
	ComplexAnimStartCallback = nullptr;
	ComplexAnimDoneCallback = nullptr;
	ComplexAnimationManager = nullptr;
    effect = nullptr;
	easing = nullptr;
	currentAnimationTime = 0;
	oldState = UINT16_MAX;
	complexAnimationInst = nullptr;
}

AnimatableObject::~AnimatableObject()
{
}

void AnimatableObject::handle(uint32_t state)
{
	unsigned long currentMillis = millis();
	if(animationStarted == true)
	{
		if(state != -1)
		{
			currentAnimationTime = constrain(state, 0, AnimationDuration);
		}
		else
		{
			currentAnimationTime = currentMillis - AnimationStartTimestamp;
		}

		uint16_t currentState = getState();
		if(oldState != currentState)
		{
			tick(currentState);
			oldState = currentState;
		}
		if(currentAnimationTime >= AnimationDuration)
		{
			done();
		}
	}
}

void AnimatableObject::tick(int32_t currentState)
{

}

void AnimatableObject::setAnimationDuration(uint16_t duration)
{
	AnimationDuration = duration;
}

void AnimatableObject::setAnimationFps(uint16_t FramesPerSecond)
{
	if(FramesPerSecond < 0)
	{
		fps = 1;
	} else
	{
		fps = FramesPerSecond;
	}
	numStates = round(fps * ((double)getAnimationDuration() / 1000.0));
}

uint16_t AnimatableObject::getAnimationDuration()
{
	return AnimationDuration;
}

void AnimatableObject::start()
{
	AnimationStartTimestamp = millis();
	if(animationStarted == true) // only start the animation if it's not already started
	{
		reset();
	}
	animationStarted = true;
	if(easing != nullptr)
	{
		easing->setTotalChangeInPosition(numStates);
		easing->setDuration(AnimationDuration);
	}
	if(startCallback != nullptr)
	{
		startCallback();
	}
	if(ComplexAnimStartCallback != nullptr && ComplexAnimationManager != nullptr)
	{
		CALL_MEMBER_FN(*ComplexAnimationManager, ComplexAnimStartCallback)(this);
	}
}

void AnimatableObject::stop()
{
	animationStarted = false;
}

void AnimatableObject::reset()
{
	stop();
	currentAnimationTime = 0;
	oldState = UINT16_MAX;
}

void AnimatableObject::done()
{
	reset();
	if(finishedCallback != nullptr)
	{
		finishedCallback();
	}
	if(ComplexAnimDoneCallback != nullptr && ComplexAnimationManager != nullptr)
	{
		CALL_MEMBER_FN(*ComplexAnimationManager, ComplexAnimDoneCallback)(this);
	}
}

int32_t AnimatableObject::getState()
{
	if(easing != nullptr)
	{
		return easing->ease(currentAnimationTime);
	}
	return map(currentAnimationTime, 0, AnimationDuration, 0, numStates);
}

void AnimatableObject::setAnimationDoneCallback(AnimationCallBack* callback)
{
	finishedCallback = callback;
}

void AnimatableObject::setAnimationStartCallback(AnimationCallBack* callback)
{
	startCallback = callback;
}

void AnimatableObject::setAnimationEffect(AnimatableObject::AnimationFunction newEffect)
{
	effect = newEffect;
}

void AnimatableObject::setAnimationEasing(EasingBase* easingEffect)
{
	easing = easingEffect;
}