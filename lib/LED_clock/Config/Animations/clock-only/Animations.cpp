#include "Animations.h"

Animator::ComplexAmination* InitLoadingAnimation(uint16_t totalAnimationLength);
Animator::ComplexAmination* LoadingAnimation = InitLoadingAnimation(LOADING_ANIMATION_DURATION);

Animator::ComplexAmination* InitLoadingAnimation(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 2
	Animator::animationStep* preStep = new Animator::animationStep;
	preStep->arrayIndex 		= new int16_t[LENGTH]								{SEGMENT(BOTTOM_MIDDLE_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), NO_SEGMENTS};
	preStep->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToRight, 						NO_ANIMATION};
	preStep->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_MIDDLE_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), SEGMENT(BOTTOM_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step0->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 						AnimationEffects::AnimateInToTop};
	step0->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), 	SEGMENT(TOP_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step1->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToTop, 						AnimationEffects::AnimateInToTop};
	step1->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), 	SEGMENT(TOP_MIDDLE_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step2->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToTop, 						AnimationEffects::AnimateInToLeft};
	step2->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};
	Animator::animationStep* step3 = new Animator::animationStep;
	step3->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_MIDDLE_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), 	SEGMENT(TOP_LEFT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step3->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToLeft, 						AnimationEffects::AnimateInToBottom};
	step3->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};
	Animator::animationStep* step4 = new Animator::animationStep;
	step4->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_LEFT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), 		SEGMENT(BOTTOM_LEFT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step4->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom, 						AnimationEffects::AnimateInToBottom};
	step4->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};
	Animator::animationStep* step5 = new Animator::animationStep;
	step5->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_LEFT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), NO_SEGMENTS};
	step5->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom, 						NO_ANIMATION};
	step5->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 												NO_EASING};

	LinkedList<Animator::animationStep*>* allSteps = new LinkedList<Animator::animationStep*>();
	allSteps->add(preStep);
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