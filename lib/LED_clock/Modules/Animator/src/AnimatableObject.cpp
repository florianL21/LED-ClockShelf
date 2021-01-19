#include "AnimatableObject.h"

AnimatableObject::AnimatableObject()
{
	AnimatableObject(0, 0);
}

AnimatableObject::AnimatableObject(uint16_t OverallDuration, uint16_t steps)
{
	AnimationDuration = OverallDuration;
	timeSinceLastTick = millis();
	tickLength = 20;
	animationStarted = false;
	tickState = 0;
	fps = 0;
	setAnimationSteps(steps);
	finishedCallback = nullptr;
	startCallback = nullptr;
	ComplexAnimStartCallback = nullptr;
	ComplexAnimDoneCallback = nullptr;
	ComplexAnimationManager = nullptr;
    effectFunction = nullptr;
}

AnimatableObject::~AnimatableObject()
{
}

void AnimatableObject::tick()
{
}

void AnimatableObject::setAnimationDuration(uint16_t duration)
{
	AnimationDuration = duration;
}

void AnimatableObject::setAnimationSteps(uint16_t numSteps)
{
	numUnsmoothedStep = numSteps;
	setAnimationFps(fps);
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
	numStates = fps * (getAnimationDuration() / 1000.0);
	if(numStates != 0)
	{
		tickLength = AnimationDuration / numStates;
		if(tickLength == 0)
		{
			tickLength = 1; // dont set it to zero, it will crash trust me
		}
	}
	else
	{
		tickLength = 1; // dont set it to zero, it will crash trust me
	}
}

uint16_t AnimatableObject::getAnimationDuration()
{
	return AnimationDuration;
}

void AnimatableObject::start()
{
	if(animationStarted == true) // only start the animation if it's not already started
	{
		reset();
	}
	animationStarted = true;
	onAnimationStart();
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
	tickState = 0;
}

void AnimatableObject::done()
{
	reset();
	onAnimationDone();
	if(finishedCallback != nullptr)
	{
		finishedCallback();
	}
	if(ComplexAnimDoneCallback != nullptr && ComplexAnimationManager != nullptr)
	{
		CALL_MEMBER_FN(*ComplexAnimationManager, ComplexAnimDoneCallback)(this);
	}
}

uint16_t AnimatableObject::getState()
{
	return tickState;
}

void AnimatableObject::setAnimationDoneCallback(AnimationCallBack* callback)
{
	finishedCallback = callback;
}

void AnimatableObject::setAnimationStartCallback(AnimationCallBack* callback)
{
	startCallback = callback;
}

void AnimatableObject::onAnimationStart()
{
	
}

void AnimatableObject::onAnimationDone()
{
	
}

void AnimatableObject::setAnimationEffect(uint8_t newEffect)
{
	effect = newEffect;
}

void AnimatableObject::setAnimationEffect_new(AnimatableObject::AnimationFunction newEffect)
{
    effectFunction = newEffect;
}
