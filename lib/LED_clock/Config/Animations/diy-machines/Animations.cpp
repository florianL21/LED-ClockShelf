/**
 * \file Animations.cpp
 * \author Florian Laschober
 * \brief Implementations of all preconfigured animations avaliable.
 * 		  Simplified animations for 12h Displays without intermediate segments
 */

#include "Animations.h"

Animator::ComplexAmination* InitIndefiniteLoadingAnimation(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitLoadingProgressAnimation(uint16_t totalAnimationLength);
/**
 * \brief Initialize the animation in global context to make it usable.
 *
 */
Animator::ComplexAmination* IndefiniteLoadingAnimation 	= InitIndefiniteLoadingAnimation(LOADING_ANIMATION_DURATION);
Animator::ComplexAmination* LoadingProgressAnimation 	= InitLoadingProgressAnimation(LOADING_ANIMATION_DURATION);

/**
 * \brief Initialize the loading animation
 *
 * \param totalAnimationLength Duration of the whole animation in milliseconds
 * \return Animator::ComplexAmination* pointer to the newly created animation
 */
Animator::ComplexAmination* InitIndefiniteLoadingAnimation(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 2
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH]								{SEGMENT(BOTTOM_MIDDLE_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), NO_SEGMENTS};
	step0->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToRight, 						NO_ANIMATION};
	step0->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_MIDDLE_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), SEGMENT(BOTTOM_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step1->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 						AnimationEffects::AnimateInToTop};
	step1->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), 	SEGMENT(TOP_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step2->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToTop, 						AnimationEffects::AnimateInToTop};
	step2->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};
	Animator::animationStep* step3 = new Animator::animationStep;
	step3->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), 	SEGMENT(TOP_MIDDLE_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step3->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToTop, 						AnimationEffects::AnimateInToLeft};
	step3->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};
	Animator::animationStep* step4 = new Animator::animationStep;
	step4->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_MIDDLE_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), 	SEGMENT(TOP_LEFT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step4->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToLeft, 						AnimationEffects::AnimateInToBottom};
	step4->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};
	Animator::animationStep* step5 = new Animator::animationStep;
	step5->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_LEFT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), 		SEGMENT(BOTTOM_LEFT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step5->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom, 						AnimationEffects::AnimateInToBottom};
	step5->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};
	Animator::animationStep* step6 = new Animator::animationStep;
	step6->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_LEFT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), NO_SEGMENTS};
	step6->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom, 						NO_ANIMATION};
	step6->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};

	LinkedList<Animator::animationStep*>* allSteps = new LinkedList<Animator::animationStep*>();
	allSteps->add(step0);
	allSteps->add(step1);
	allSteps->add(step2);
	allSteps->add(step3);
	allSteps->add(step4);
	allSteps->add(step5);
	allSteps->add(step6);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / allSteps->size();
	animation->animations 			= allSteps;
	return animation;
}

Animator::ComplexAmination* InitLoadingProgressAnimation(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 1
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH]									{SEGMENT(BOTTOM_MIDDLE_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step0->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToRight};
	step0->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step1->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToTop};
	step1->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step2->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToTop};
	step2->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING};
	Animator::animationStep* step3 = new Animator::animationStep;
	step3->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_MIDDLE_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step3->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToLeft};
	step3->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING};
	Animator::animationStep* step4 = new Animator::animationStep;
	step4->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_LEFT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step4->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToBottom};
	step4->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING};
	Animator::animationStep* step5 = new Animator::animationStep;
	step5->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_LEFT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step5->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToBottom};
	step5->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING};

	LinkedList<Animator::animationStep*>* allSteps = new LinkedList<Animator::animationStep*>();
	allSteps->add(step0);
	allSteps->add(step1);
	allSteps->add(step2);
	allSteps->add(step3);
	allSteps->add(step4);
	allSteps->add(step5);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / allSteps->size();
	animation->animations 			= allSteps;
	return animation;
}
