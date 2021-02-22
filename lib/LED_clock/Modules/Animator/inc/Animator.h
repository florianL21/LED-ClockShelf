#ifndef __ANIMATOR_H_
#define __ANIMATOR_H_

#include <Arduino.h>
#include <LinkedList.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "AnimatableObject.h"
#include "Configuration.h"

class AnimatableObject;

class Animator
{
public:
	/**
	 * \brief Configuration structure used in the linked list to construct an animation chain
	 *
	 * \note Both lists have to have the same length. The length also must be consistent across all animation steps.
	 *
	 * \param arrayIndex index of the array position where the objects that shall be animated is located. Set to -1 to ignore
	 * \param animationEffects array of animation effects that shall be played back
	 * \param easingEffects array of easing effect ("modifiers") that shall be applied to the animation
	 */
	typedef struct {
		int16_t* arrayIndex;
		AnimatableObject::AnimationFunction* animationEffects;
		EasingBase** easingEffects;
	} animationStep;

	/**
	 * \brief Configuration structure for a complex animation
	 *
	 * \note All list elements must have the same array length
	 *
	 * \param animationComplexity Maximum of how many animations can be triggered at the same time
	 * \param LengthPerAnimation How long one of the animations in the chain should last for
	 * \param animations list of animation steps that shall be played in sequence
	 */
	typedef struct {
		uint8_t animationComplexity;
		uint16_t LengthPerAnimation;
		LinkedList<animationStep*>* animations;
	} ComplexAmination;

private:
	LinkedList<AnimatableObject*> AnimatableObjects;
	static unsigned long lastLEDUpdate;

	ComplexAmination* currentComplexAnimation;
	bool loopAnimation;
	uint16_t complexAnimationCounter;
	bool complexAnimationRunning;

	AnimatableObject** animationObjects;

	int16_t getIndexInList(AnimatableObject* object);
	void animationIterationStartCallback(AnimatableObject* sourceObject);
	void animationIterationDoneCallback(AnimatableObject* sourceObject);

	void startAnimationStep(uint16_t stepindex);

public:
	Animator();
	~Animator();
	void add(AnimatableObject* animationToAdd);
	void remove(AnimatableObject* animationToRemove);
	void handle();

	void setAnimation(AnimatableObject* object, AnimatableObject::AnimationFunction animationEffect, uint16_t duration, EasingBase* easing = NO_EASING, uint8_t fps = ANIMATION_TARGET_FPS);
	void startAnimation(AnimatableObject* object, AnimatableObject::AnimationFunction animationEffect, uint16_t duration, EasingBase* easing = NO_EASING, uint8_t fps = ANIMATION_TARGET_FPS);
	void startAnimation(AnimatableObject* object, AnimatableObject::AnimationFunction animationEffect, EasingBase* easing = NO_EASING);
	void setAnimationDuration(AnimatableObject* object, uint16_t duration);
	void startAnimation(AnimatableObject* object);
	void stopAnimation(AnimatableObject* object);
	void resetAnimation(AnimatableObject* object);
	AnimatableObject::AnimationFunction getAnimationEffect(AnimatableObject* object);
	/**
	 * \brief Starts a complex chain of animations
	 *
	 * \param animation pointer to the animation that shall be played
	 * \param animationObjectsArray Array of the objects that shall be animated. The indices for the array are defined in the animation itself
	 * \param looping Whether the animation shall be looped or not
	 */
	void PlayComplexAnimation(ComplexAmination* animation, AnimatableObject* animationObjectsArray[], bool looping = false);
	void ComplexAnimationStopLooping();
	void WaitForComplexAnimationCompletion();

	void delay(uint32_t delayInMs);
};

#endif
