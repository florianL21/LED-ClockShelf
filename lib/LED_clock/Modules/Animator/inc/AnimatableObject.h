/**
 * \file AnimatableObject.h
 * \author Florian Laschober
 * \brief Header for base class definition of every object that can be animated by the #Animator
 */

#ifndef __ANIMATABLE_OBJECT_H_
#define __ANIMATABLE_OBJECT_H_

#include <Arduino.h>
#define FASTLED_INTERNAL
#include "FastLED.h"
#include "easing.h"

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
/**
 * \brief Macro that should be used as a placeholder when an animation step does not require any easing
 */
#define NO_EASING		nullptr

/**
 * \brief Macro should be used as a placeholder when an animation step is shorter than the animation
 * 		  complexity and no additional segments need to be animated. For that particular position in the step
 * 		  sequence the #animationEffects property should be set to #NO_ANIMATION
 */
#define NO_SEGMENTS		-1

/**
 * \brief Macro should be used as a placeholder when an animation step is set to #NO_SEGMENTS
 */
#define NO_ANIMATION	0

class Animator;
class Segment;

/**
 * \brief Base class which every object that can be animated by the #Animator should inherit from.
 */
class AnimatableObject
{
public:
	/**
	 * \brief Callback typedef to use when an animation starts/finishes
	 */
	typedef void AnimationCallBack(void);

	/**
	 * \brief Typedef for animation effect functions. These should be implemented explicitly for every object that inherits from #AnimatableObject
	 */
    typedef void (*AnimationFunction)(CRGB* leds, uint16_t length, CRGB animationColor, uint16_t totalSteps, int32_t currentStep, bool invert);
private:
    friend class Animator;
    friend class Segment;

	typedef void (Animator::*ComplexAnimationCallBack)(AnimatableObject * sourceObject);

    AnimationFunction effect;
	EasingBase* easing;
	uint16_t AnimationDuration;
	uint64_t AnimationStartTimestamp;
	uint16_t currentAnimationTime;
	double tickLength;
	uint16_t fps;
	uint16_t numStates;
	uint16_t oldState;
	bool animationStarted;
	void* complexAnimationInst;

	AnimationCallBack* finishedCallback;
	AnimationCallBack* startCallback;
	Animator* ComplexAnimationManager;
	ComplexAnimationCallBack ComplexAnimStartCallback;
	ComplexAnimationCallBack ComplexAnimDoneCallback;

	/**
	 * \brief Gets called by #AnimatableObject::handle when the animation is finished.
	 */
	void done();

	/**
	 * \brief Gets the current state of the animation including all easings that might affect it.
	 *
	 * \return int32_t the current state of the animation. Can also be negative in case of an easing that undershoots
	 */
	int32_t getState();

	/**
	 * \brief setting the animation to the state passed as a parameter
	 *
	 * \param currentState "progress" of the current animation that is being displayed
	 */
	virtual void tick(int32_t currentState);

protected:
	AnimatableObject();
	AnimatableObject(uint16_t OverallDuration, uint16_t steps);
	~AnimatableObject();

	/**
	 * \brief Set the overall duration of any animation called on this object
	 *
	 * \param duration animation duration in ms
	 */
	void setAnimationDuration(uint16_t duration);

	/**
	 * \brief Set the overall duration of any animation called on this object
	 *
	 * \param duration animation duration in ms
	 */
	uint16_t getAnimationDuration();

	/**
	 * \brief Set the target Frames Per Second for any animation called on this object.
	 * \note  This does not guarantee that the animation is actually running on that refresh rate.
	 * 	      If it is set too fast the system will run it at the maximum possible framerate instead.
	 *
	 * \param setAnimationFps how often the animation should be updated on the actual LEDs in Frames/Second
	 */
	void setAnimationFps(uint16_t setAnimationFps);

	/**
	 * \brief Enables an animation to run when #AnimatableObject::tick() gets called
	 */
	void start();

	/**
	 * \brief Disables an animation to run when #AnimatableObject::tick() gets called but does not reset it's current state.
	 * 	      Could be thought of as "pausing" it.
	 */
	void stop();

	/**
	 * \brief Stops (if not already done) and resets the animation to its starting point.
	 */
	void reset();

	/**
	 * \brief Gets called by the #Animator #Animator::handle method when the animation is finished.
	 *
	 * \param state if not -1 any animations currently running are going to be set to an exact state
	 */
	void handle(uint32_t state = -1);

	/**
	 * \brief Set the animation effect to the current object
	 *
	 * \param newEffect effect to execute the next time an animation is started on this object
	 */
	virtual void setAnimationEffect(AnimatableObject::AnimationFunction newEffect);

	/**
	 * \brief Set the animation easing effect to the current object
	 *
	 * \param easingEffect effect to apply to the animation as an additional "modifier"
	 */
	virtual void setAnimationEasing(EasingBase* easingEffect);
public:
	/**
	 * \brief Set a callback to be executued once an animation has finished running
	 *
	 * \param callback function to call
	 */
	void setAnimationDoneCallback(AnimationCallBack* callback);

	/**
	 * \brief Set a callback to be executued once an animation is started
	 *
	 * \param callback function to call
	 */
	void setAnimationStartCallback(AnimationCallBack* callback);

};

#endif
