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
	 * @brief Configuration structure used in the linked list to construct an animation chain
	 * 
	 * @note Both lists have to have the same length. The length also must be consistent across all animation steps.
	 * 
	 * @param objects array of objects that shall be animated.
	 * @param animationEffects array of animation effects that shall be played back
	 */
	typedef struct {
		int16_t* arrayIndex;
		uint8_t* animationEffects;
	} animationStep;

	/**
	 * @brief Configuration structure for a complex animation
	 * 
	 * @note All list elements must have the same array length
	 * 
	 * @param animationComplexity Maximum of how many animations can be triggered at the same time
	 * @param LengthPerAnimation How long one of the animations in the chain should last for
	 * @param animations list of animation setps that shall be played in sequence
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

	void setAnimation(AnimatableObject* object, uint8_t animationEffect, uint16_t duration, uint8_t smoothness = 0);
	void startAnimation(AnimatableObject* object, uint8_t animationEffect, uint16_t duration, uint8_t smoothness = 0);
	void startAnimation(AnimatableObject* object, uint8_t animationEffect);
	void setAnimationDuration(AnimatableObject* object, uint16_t duration);
	void startAnimation(AnimatableObject* object);
	void stopAnimation(AnimatableObject* object);
	void resetAnimation(AnimatableObject* object);
	uint8_t getAnimationEffect(AnimatableObject* object);
	/**
	 * @brief Starts a complex chain of animations
	 * 
	 * @note The first set of animations always have the trigger STARTS_WITH the configured trigger is ignored
	 * 
	 * @param NumAnimations number of animations in a row
	 * @param animationComplexity Maximum of how many animations can be triggered at the same time
	 * @param LengthPerAnimation How long one of the animations in the chain should last for
	 * @param objects 2D array of objects that shall be animated.
	 * @param animationEffects 2D array of animation effects that shall be played back
	 */
	void PlayComplexAnimation(ComplexAmination* animation, AnimatableObject* animationObjectsArray[], bool looping = false);
	void ComplexAnimationStopLooping();
	void WaitForComplexAnimationCompletion();

	void delay(uint32_t delayInMs);
};

#endif