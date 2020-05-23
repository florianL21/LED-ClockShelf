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
	unsigned long currentMillis = millis();
	for (int i = 0; i < AnimatableObjects.size(); i++)
	{
		AnimatableObject* currentAnimation = AnimatableObjects.get(i);
		if(currentAnimation->animationStarted == true)
		{
			if(currentAnimation->timeSinceLastTick + currentAnimation->tickLength < currentMillis)
			{
				//execute all past ticks. this should normally not be more than 1
				for (int i = 0; i < (currentMillis - currentAnimation->timeSinceLastTick) / currentAnimation->tickLength; i++)
				{
					currentAnimation->tick();
				}
				currentAnimation->timeSinceLastTick = currentMillis;
				if(++(currentAnimation->tickState) >= currentAnimation->numStates)
				{
					currentAnimation->done();
				}
			}
		}else
		{
			currentAnimation->timeSinceLastTick = currentMillis;
		}
	}

	if(lastLEDUpdate + FASTLED_SAFE_DELAY_MS < millis())
	{
		lastLEDUpdate = millis();
		FastLED.show();
	}
}

void Animator::setAnimation(AnimatableObject* object, uint8_t animationEffect, uint16_t duration, uint8_t smoothness)
{
	object->setAnimationDuration(duration);
	object->setAnimationSmothing(smoothness);
	object->setAnimationEffect(animationEffect);
}

void Animator::setAnimationDuration(AnimatableObject* object, uint16_t duration)
{
	object->setAnimationDuration(duration);
}

void Animator::startAnimation(AnimatableObject* object, uint8_t animationEffect, uint16_t duration, uint8_t smoothness)
{
	setAnimation(object, animationEffect, duration, smoothness);
	startAnimation(object);
}

void Animator::startAnimation(AnimatableObject* object, uint8_t animationEffect)
{
	startAnimation(object, animationEffect, object->getAnimationDuration());
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

uint8_t Animator::getAnimationEffect(AnimatableObject* object)
{
	return object->effect;
}

void Animator::delay(uint32_t delayInMs)
{
	unsigned long startMillis = millis();
	while(startMillis + delayInMs > millis())
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
	complexAnimationRunning = true;
	for (int j = 0; j < currentComplexAnimation->animationComplexity; j++)
	{
		
		if(StepToStart->objects[j] != nullptr)
		{
			setAnimationDuration(StepToStart->objects[j], currentComplexAnimation->LengthPerAnimation);
			StepToStart->objects[j]->ComplexAnimationManager = this;
			if(hasCallbacks == false) //only assign the callbacks to one object as all of them should start and end at the same time
			{
				hasCallbacks = true;
				StepToStart->objects[j]->ComplexAnimDoneCallback = &Animator::animationIterationDoneCallback;
				StepToStart->objects[j]->ComplexAnimStartCallback = &Animator::animationIterationStartCallback;
			}
			startAnimation(StepToStart->objects[j], StepToStart->animationEffects[j]);
		}
	}
}

void Animator::PlayComplexAnimation(ComplexAmination* animation, bool looping)
{
	complexAnimationCounter = 0;
	currentComplexAnimation = animation;
	loopAnimation = looping;
	complexAnimationRunning = true;
	if(animation->animations == nullptr)
	{
		Serial.println("[E] animation chain was null pointer!");
	}
	else
	{
		if(animation->animations->size() >= 1)
		{
			startAnimationStep(0);
		}
		else
		{
			Serial.println("[E] animation chain size was zero this Should not be the case!");
		}
	}
}

void Animator::ComplexAnimationStopLooping()
{
	loopAnimation = false;
}

void Animator::WaitForComplexAnimationCompletion()
{
	while (complexAnimationRunning == true)
	{
		handle();
	}
}