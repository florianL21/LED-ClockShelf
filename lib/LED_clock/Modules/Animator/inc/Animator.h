/**
 * \file Animator.h
 * \author Florian Laschober
 * \brief Header for class definition of the #Animator
 */

#ifndef __ANIMATOR_H_
#define __ANIMATOR_H_

#include <Arduino.h>
#include <LinkedList.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "AnimatableObject.h"
#include "Configuration.h"

class AnimatableObject;

/**
 * \brief The Animator class is responsible for handling all animations of objects that inherit from #AnimatableObject
 * 		  In the system there can be more than one Animator running at the same time.
 */
class Animator
{
public:
	/**
	 * \brief Configuration structure used in the linked list to construct an animation chain
	 *
	 * \note All three lists have to have the same length. The length also must be consistent across all animation steps.
	 * 		 If the system crashes when calling an animation it is most likeley due to missing arrays or missmatched array lengths.
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

	struct ComplexAnimationInstance {
		ComplexAmination* animation;
		bool loop;
		uint16_t counter;
		AnimatableObject** objects;
		bool running;
	};

private:
	static Animator* currentInstance;
	LinkedList<AnimatableObject*> AnimatableObjects;
	static unsigned long lastLEDUpdate;

	int16_t getIndexInList(AnimatableObject* object);
	void animationIterationStartCallback(AnimatableObject* sourceObject);
	void animationIterationDoneCallback(AnimatableObject* sourceObject);

	void startAnimationStep(uint16_t stepindex, ComplexAnimationInstance* animationInst);

	/**
	 * \brief Construct a new Animator object
	 */
	Animator();

public:
	/**
	 * \brief get an instance of the Animator object
	 */
	static Animator* getInstance();

	/**
	 * \brief Destroy the Animator object
	 */
	~Animator();

	/**
	 * \brief Add an animatable object to the Animator. The object is then updated by it.
	 *
	 * \param animationToAdd Pointer to the object whose animations should be handled by this animator.
	 */
	void add(AnimatableObject* animationToAdd);

	/**
	 * \brief Remove an animatable object from the Animator. The object is then no longer updated by it.
	 *
	 * \pre The object must have been added earlier by using #Animator::add
	 *
	 * \param animationToRemove Pointer to the object whose animations should not be handled anymore by this animator.
	 */
	void remove(AnimatableObject* animationToRemove);

	/**
	 * \brief To be called periodically as fast as possible. Updates all animation states of all #AnimatableObjects assigned to this #Animator
	 *
	 * \param state if not -1 any animations currently running are going to be set to an exact state
	 */
	void handle(uint32_t state = -1);

	/**
	 * \brief Setup all parameters for an animation of an object assigned to this #Animator but do not start it.
	 *
	 * \param object Object for which to change the animation for
	 * \param animationEffect Animation effect that should be used next time an animation for this object is started.
	 * \param duration Total duration of the animation effect once it is started.
	 * \param easing [optional] default = #NO_EASING; Easing effect to apply "on top" of the animation
	 * \param fps [optional] default = #ANIMATION_TARGET_FPS; Target FPS to run the animation at
	 */
	void setAnimation(AnimatableObject* object, AnimatableObject::AnimationFunction animationEffect, uint16_t duration, EasingBase* easing = NO_EASING, uint8_t fps = ANIMATION_TARGET_FPS);

	/**
	 * \brief Setup all parameters for an animation of an object assigned to this #Animator and start it right away.
	 *
	 * \param object Object for which to start the animation for
	 * \param animationEffect Animation effect that should be started
	 * \param duration Total duration of the animation effect
	 * \param easing [optional] default = #NO_EASING; Easing effect to apply "on top" of the animation
	 * \param fps [optional] default = #ANIMATION_TARGET_FPS; Target FPS to run the animation at
	 */
	void startAnimation(AnimatableObject* object, AnimatableObject::AnimationFunction animationEffect, uint16_t duration, EasingBase* easing = NO_EASING, uint8_t fps = ANIMATION_TARGET_FPS);

	/**
	 * \brief Setup the most important parameters for an animation of an object assigned to this #Animator and start it right away.
	 *
	 * \param object Object for which to start the animation for
	 * \param animationEffect Animation effect that should be started
	 * \param easing [optional] default = #NO_EASING; Easing effect to apply "on top" of the animation
	 */
	void startAnimation(AnimatableObject* object, AnimatableObject::AnimationFunction animationEffect, EasingBase* easing = NO_EASING);

	/**
	 * \brief Starts an animation which was previously setup
	 * \pre An animation must already be setup for this object. Either though a call of #Animator::setAnimation or a previous #Animator::startAnimation call.
	 *
	 * \param object Object for which to start the animation for
	 */
	void startAnimation(AnimatableObject* object);

	/**
	 * \brief Set the animation duration of an object assigned to this #Animator
	 *
	 * \param object Object for which to set the suration for
	 * \param duration Total animation duration in ms once it is started.
	 */
	void setAnimationDuration(AnimatableObject* object, uint16_t duration);

	/**
	 * \brief Calls the #AnimatableObject::stop function on the given object.
	 *
	 * \param object Object for which to stop the animation for
	 */
	void stopAnimation(AnimatableObject* object);

	/**
	 * \brief Calls the #AnimatableObject::reset function on the given object.
	 *
	 * \param object Object for which to reset the animation for
	 */
	void resetAnimation(AnimatableObject* object);

	/**
	 * \brief Get the current animation effect of the object
	 *
	 * \param object Object for which to get the current animation for
	 * \return AnimatableObject::AnimationFunction pointer to the current animation effect function
	 */
	AnimatableObject::AnimationFunction getAnimationEffect(AnimatableObject* object);

	/**
	 * \brief Starts a complex chain of animations
	 *
	 * \param animation pointer to the animation that shall be played
	 * \param animationObjectsArray Array of the objects that shall be animated. The indices for the array are defined in the animation itself
	 * \param looping Whether the animation shall be looped or not
	 * \return uint32_t The animation ID of the newly started animation
	 * 					-1 which results to the max 32 bit value represents an error while starting the animation
	 */
	ComplexAnimationInstance* PlayComplexAnimation(ComplexAmination* animation, AnimatableObject* animationObjectsArray[], bool looping = false);

	/**
	 * \brief Builds a complex animation but does not start it.
	 *
	 * \param animation pointer to the animation that shall be played
	 * \param animationObjectsArray Array of the objects that shall be animated. The indices for the array are defined in the animation itself
	 * \param looping Whether the animation shall be looped or not
	 * \return uint32_t The animation ID of the newly started animation
	 * 					-1 which results to the max 32 bit value represents an error while starting the animation
	 */
	ComplexAnimationInstance* BuildComplexAnimation(ComplexAmination* animation, AnimatableObject* animationObjectsArray[], bool looping = false);

	/**
	 * \brief set a complex animation to a specific step and state
	 *
	 * \param animationInst animation to use, retrived by calling #Animator::BuildComplexAnimation
	 * \param step Step of the complex animation which shall be executed
	 * \param state state of the current step
	 */
	void setComplexAnimationStep(ComplexAnimationInstance* animationInst, uint8_t step, uint32_t state);

	/**
	 * \brief disables looping of the complex animation so that it sops running after the current cycle is done running
	 *
	 * \param animationID ID of the animation which shall be stopped
	 */
	void ComplexAnimationStopLooping(ComplexAnimationInstance* animationInst);

	/**
	 * \brief Blocks exectution of further code until the currently running animation is complete
	 *
	 * \param animationID ID of the animation which shall be waited for
	 */
	void WaitForComplexAnimationCompletion(ComplexAnimationInstance* animationInst);

	/**
	 * \brief Delays further execution of code without blocking any currently ongoing animations
	 *
	 * \param delayInMs time to wait before moving on in ms
	 */
	void delay(uint32_t delayInMs);
};

#endif
