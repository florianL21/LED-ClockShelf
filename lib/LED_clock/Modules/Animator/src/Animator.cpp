#include "Animator.h"
unsigned long Animator::lastLEDUpdate=0;

Animator::Animator()
{
	// lastLEDUpdate = millis();
	complexAnimationCounter = 0;
	complexAnimationRunning = false;
}

Animator::~Animator()
{

}

int16_t Animator::getIndexInList(AnimatableObject* object)
{
	for (int i = 0; i < AnimatableObjects.size(); i++)
	{
		if(AnimatableObjects.get(i) == object)
		{
			return i;
		}
	}
	return -1;
}

void Animator::add(AnimatableObject* animationToAdd)
{
	if(getIndexInList(animationToAdd) == -1)
	{
		AnimatableObjects.add(animationToAdd);
	}
}

void Animator::remove(AnimatableObject* animationToRemove)
{
	int16_t indexToRemove = getIndexInList(animationToRemove);
	if(indexToRemove != -1)
	{
		AnimatableObjects.remove(indexToRemove);
	}
}

void Animator::handle()
{
	for (int i = 0; i < AnimatableObjects.size(); i++)
	{
		AnimatableObjects.get(i)->handle();
	}

	if(lastLEDUpdate + FASTLED_SAFE_DELAY_MS < millis())
	{
		lastLEDUpdate = millis();
		FastLED.show();
	}
}

void Animator::setAnimation(AnimatableObject* object, AnimatableObject::AnimationFunction animationEffect, uint16_t duration, EasingBase* easing, uint8_t fps)
{
	object->setAnimationDuration(duration);
	object->setAnimationFps(fps);
	object->setAnimationEffect(animationEffect);
	object->setAnimationEasing(easing);
}

void Animator::setAnimationDuration(AnimatableObject* object, uint16_t duration)
{
	object->setAnimationDuration(duration);
}

void Animator::startAnimation(AnimatableObject* object, AnimatableObject::AnimationFunction animationEffect, uint16_t duration, EasingBase* easing, uint8_t fps)
{
	setAnimation(object, animationEffect, duration, easing, fps);
	startAnimation(object);
}

void Animator::startAnimation(AnimatableObject* object, AnimatableObject::AnimationFunction animationEffect, EasingBase* easing)
{
	startAnimation(object, animationEffect, object->getAnimationDuration(), easing);
}

void Animator::startAnimation(AnimatableObject* object)
{
	object->start();
}

void Animator::stopAnimation(AnimatableObject* object)
{
	object->stop();
}

void Animator::resetAnimation(AnimatableObject* object)
{
	object->reset();
}

AnimatableObject::AnimationFunction Animator::getAnimationEffect(AnimatableObject* object)
{
	return object->effect;
}

void Animator::delay(uint32_t delayInMs)
{
	unsigned long startMillis = millis();
	while(millis() - startMillis < delayInMs)
	{
		handle();
	}
}

void Animator::animationIterationStartCallback(AnimatableObject* sourceObject)
{
	sourceObject->ComplexAnimStartCallback = nullptr;
}

void Animator::animationIterationDoneCallback(AnimatableObject* sourceObject)
{
	sourceObject->ComplexAnimDoneCallback = nullptr;
	if(++complexAnimationCounter < currentComplexAnimation->animations->size())
	{
		startAnimationStep(complexAnimationCounter);
	}
	else
	{
		if(loopAnimation == true)
		{
			complexAnimationCounter = 0;
			startAnimationStep(complexAnimationCounter);
		}
		else
		{
			complexAnimationRunning = false;
		}
	}
}

void Animator::startAnimationStep(uint16_t stepindex)
{
	animationStep* StepToStart = currentComplexAnimation->animations->get(stepindex);
	bool hasCallbacks = false;
	bool wasEmpty = true;
	for (int j = 0; j < currentComplexAnimation->animationComplexity; j++)
	{
		if(StepToStart->arrayIndex[j] != -1)
		{
			setAnimationDuration(animationObjects[StepToStart->arrayIndex[j]], currentComplexAnimation->LengthPerAnimation);
			animationObjects[StepToStart->arrayIndex[j]]->ComplexAnimationManager = this;
			if(hasCallbacks == false) //only assign the callbacks to one object as all of them should start and end at the same time
			{
				hasCallbacks = true;
				animationObjects[StepToStart->arrayIndex[j]]->ComplexAnimDoneCallback = &Animator::animationIterationDoneCallback;
				animationObjects[StepToStart->arrayIndex[j]]->ComplexAnimStartCallback = &Animator::animationIterationStartCallback;
			}
			startAnimation(animationObjects[StepToStart->arrayIndex[j]], StepToStart->animationEffects[j], StepToStart->easingEffects[j]);
			complexAnimationRunning = true;
			wasEmpty = false;
		}
	}
	if(wasEmpty == true)
	{
		Serial.println("[E] Complex animtation start point was empty. Animation was not started.");
	}
}

void Animator::PlayComplexAnimation(ComplexAmination* animation, AnimatableObject* animationObjectsArray[], bool looping)
{
	complexAnimationCounter = 0;
	currentComplexAnimation = animation;
	loopAnimation = looping;
	// complexAnimationRunning = true;
	animationObjects = animationObjectsArray;
	if(animation->animations == nullptr)
	{
		Serial.println("[E] animation chain was null pointer!");
		return;
	}
	if(animationObjectsArray == nullptr)
	{
		Serial.println("[E] animation objects was null pointer!");
		return;
	}
	if(animation->animations->size() >= 1)
	{
		startAnimationStep(0);
	}
	else
	{
		Serial.println("[E] animation chain size was zero this Should not be the case!");
	}
}

void Animator::ComplexAnimationStopLooping()
{
	loopAnimation = false;
}

void Animator::WaitForComplexAnimationCompletion()
{
	ComplexAnimationStopLooping();
	while (complexAnimationRunning == true)
	{
		handle();
	}
}
