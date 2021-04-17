#include "Animator.h"
unsigned long Animator::lastLEDUpdate=0;
Animator* Animator::currentInstance = nullptr;

Animator::Animator()
{
}

Animator::~Animator()
{
	currentInstance = nullptr;
}

Animator* Animator::getInstance()
{
	if(currentInstance == nullptr)
	{
		currentInstance = new Animator();
	}
	return currentInstance;
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

void Animator::handle(uint32_t state)
{
	for (int i = 0; i < AnimatableObjects.size(); i++)
	{
		AnimatableObjects.get(i)->handle(state);
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
	if(sourceObject->complexAnimationInst == nullptr)
	{
		Serial.println("[E] Complex animation instance of sourceObject was nullpointer. Aborting further execution of complex animation steps");
		return;
	}
	ComplexAnimationInstance* currentAnimation = (ComplexAnimationInstance*) sourceObject->complexAnimationInst;

	if(++currentAnimation->counter < currentAnimation->animation->animations->size())
	{
		startAnimationStep(currentAnimation->counter, currentAnimation);
	}
	else
	{
		if(currentAnimation->loop == true)
		{
			currentAnimation->counter = 0;
			startAnimationStep(currentAnimation->counter, currentAnimation);
		}
		else
		{
			//make sure that no references to this animations are retained before deleting it
			for (int i = 0; i < AnimatableObjects.size(); i++)
			{
				AnimatableObject* currentObject = AnimatableObjects.get(i);
				if(currentObject->complexAnimationInst == currentAnimation)
				{
					currentObject->complexAnimationInst = nullptr;
				}
			}
			delete currentAnimation;
		}
	}
}

void Animator::startAnimationStep(uint16_t stepindex, ComplexAnimationInstance* animationInst)
{
	if(animationInst == nullptr)
	{
		Serial.printf("[E] Complex animation instance was nullpointer. Animation step %d was not started\n\r", stepindex);
		return;
	}

	animationStep* StepToStart = animationInst->animation->animations->get(stepindex);
	bool hasCallbacks = false;
	bool wasEmpty = true;
	AnimatableObject* currentObject;
	for (int j = 0; j < animationInst->animation->animationComplexity; j++)
	{
		if(StepToStart->arrayIndex[j] != -1)
		{
			currentObject = animationInst->objects[StepToStart->arrayIndex[j]];
			setAnimationDuration(currentObject, animationInst->animation->LengthPerAnimation);
			currentObject->ComplexAnimationManager = this;
			if(hasCallbacks == false) //only assign the callbacks to one object as all of them should start and end at the same time
			{
				hasCallbacks = true;
				currentObject->complexAnimationInst = animationInst;
				currentObject->ComplexAnimDoneCallback = &Animator::animationIterationDoneCallback;
				currentObject->ComplexAnimStartCallback = &Animator::animationIterationStartCallback;
			}
			startAnimation(currentObject, StepToStart->animationEffects[j], StepToStart->easingEffects[j]);
			animationInst->running = true;
			wasEmpty = false;
		}
	}
	if(wasEmpty == true)
	{
		Serial.printf("[E] Complex animtation start point was empty. Animation step (%d) was not started.\n\r", stepindex);
	}
}

Animator::ComplexAnimationInstance* Animator::PlayComplexAnimation(ComplexAmination* animation, AnimatableObject* animationObjectsArray[], bool looping)
{
	ComplexAnimationInstance* ComplexAnimation = BuildComplexAnimation(animation, animationObjectsArray, looping);
	if(ComplexAnimation == nullptr)
	{
		return nullptr;
	}
	startAnimationStep(0, ComplexAnimation);
	return ComplexAnimation;
}

void Animator::ComplexAnimationStopLooping(ComplexAnimationInstance* animationInst)
{
	if(animationInst == nullptr)
	{
		Serial.println("[E] Complex animation ID was invalid");
		return;
	}
	animationInst->loop = false;
}

void Animator::WaitForComplexAnimationCompletion(ComplexAnimationInstance* animationInst)
{
	ComplexAnimationStopLooping(animationInst);
	bool animationRunning = true;
	bool animationReferenceFound;
	while(animationRunning == true) //wait until the animation is removed from the list
	{
		animationReferenceFound = false;
		for (int i = 0; i < AnimatableObjects.size(); i++)
		{
			if(AnimatableObjects.get(i)->complexAnimationInst == animationInst)
			{
				animationReferenceFound = true;
			}
		}
		if(animationReferenceFound == false)
		{
			animationRunning = false;
		}
		handle();
	}
}

Animator::ComplexAnimationInstance* Animator::BuildComplexAnimation(ComplexAmination* animation, AnimatableObject* animationObjectsArray[], bool looping)
{
	if(animation->animations == nullptr)
	{
		Serial.println("[E] animation chain was null pointer!");
		return nullptr;
	}
	if(animationObjectsArray == nullptr)
	{
		Serial.println("[E] animation objects was null pointer!");
		return nullptr;
	}

	ComplexAnimationInstance* ComplexAnimation = new ComplexAnimationInstance {
		.animation = animation,
		.loop = looping,
		.counter = 0,
		.objects = animationObjectsArray,
		.running = false
	};
	if(ComplexAnimation == nullptr)
	{
		Serial.println("[E] Animation objet could not be instantiated!");
		return nullptr;
	}
	if(animation->animations->size() >= 1)
	{
		return ComplexAnimation;
	}
	else
	{
		Serial.println("[E] animation chain size was zero this Should not be the case!");
		return nullptr;
	}
}

void Animator::setComplexAnimationStep(ComplexAnimationInstance* animationInst, uint8_t step, uint32_t state)
{
	if(animationInst == nullptr)
	{
		Serial.printf("[E] Complex animation instance was nullpointer. Animation step %d was not started\n\r", step);
		return;
	}
	if(step > animationInst->animation->animations->size() - 1)
	{
		Serial.printf("[E] invalid step (%d) for complex animation; Highest allowed step: %d\n\r", step, animationInst->animation->animations->size());
		return;
	}

	animationStep* StepToStart = animationInst->animation->animations->get(step);
	bool hasCallbacks = false;
	bool wasEmpty = true;
	AnimatableObject* currentObject;
	for (int j = 0; j < animationInst->animation->animationComplexity; j++)
	{
		if(StepToStart->arrayIndex[j] != -1)
		{
			currentObject = animationInst->objects[StepToStart->arrayIndex[j]];
			setAnimationDuration(currentObject, animationInst->animation->LengthPerAnimation);
			currentObject->ComplexAnimationManager = this;
			if(hasCallbacks == false) //only assign the callbacks to one object as all of them should start and end at the same time
			{
				hasCallbacks = true;
				currentObject->complexAnimationInst = animationInst;
			}
			startAnimation(currentObject, StepToStart->animationEffects[j], StepToStart->easingEffects[j]);
			animationInst->running = true;
			wasEmpty = false;
			//make sure to disable all other animations of this animation chain
			for (int i = 0; i < AnimatableObjects.size(); i++)
			{
				AnimatableObject* cObject = AnimatableObjects.get(i);
				cObject->startCallback = nullptr;
				cObject->finishedCallback = nullptr;
				cObject->ComplexAnimDoneCallback = nullptr;
				cObject->ComplexAnimStartCallback = nullptr;
				if(cObject->complexAnimationInst == animationInst)
				{
					if(cObject != currentObject)
					{
						cObject->complexAnimationInst = nullptr;
						cObject->handle(cObject->AnimationDuration);
					}
				}
			}
		}
	}
	handle(state);
	if(wasEmpty == true)
	{
		Serial.printf("[E] Complex animtation start point was empty. Animation step (%d) was not started.\n\r", step);
	}
}
