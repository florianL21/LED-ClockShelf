#include "Animations.h"

Animator::ComplexAmination* InitLoadingAnimation(uint16_t totalAnimationLength);
Animator::ComplexAmination* LoadingAnimation = InitLoadingAnimation(LOADING_ANIMATION_DURATION);

Animator::ComplexAmination* InitLoadingAnimation(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 2
	Animator::animationStep* preStep = new Animator::animationStep;
	preStep->arrayIndex 		= new int16_t[LENGTH]								{SEGMENT(BOTTOM_MIDDLE_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), 	NO_SEGMENTS};
	preStep->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToRight, 							NO_ANIMATION};
	preStep->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_MIDDLE_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), 	SEGMENT(BOTTOM_MIDDLE_SEGMENT, FIRST_INTERMEDIATE_DISPLAY)};
	step0->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 							AnimationEffects::AnimateInToRight};
	step0->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_MIDDLE_SEGMENT, FIRST_INTERMEDIATE_DISPLAY), 	SEGMENT(BOTTOM_MIDDLE_SEGMENT, LOWER_DIGIT_HOUR_DISPLAY)};
	step1->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 							AnimationEffects::AnimateInToRight};
	step1->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_MIDDLE_SEGMENT, LOWER_DIGIT_HOUR_DISPLAY), 		SEGMENT(BOTTOM_MIDDLE_SEGMENT, SECOND_INTERMEDIATE_DISPLAY)};
	step2->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 							AnimationEffects::AnimateInToRight};
	step2->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step3 = new Animator::animationStep;
	step3->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_MIDDLE_SEGMENT, SECOND_INTERMEDIATE_DISPLAY), 	SEGMENT(BOTTOM_MIDDLE_SEGMENT, HIGHER_DIGIT_MINUTE_DISPLAY)};
	step3->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 							AnimationEffects::AnimateInToRight};
	step3->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step4 = new Animator::animationStep;
	step4->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_MIDDLE_SEGMENT, HIGHER_DIGIT_MINUTE_DISPLAY), 	SEGMENT(BOTTOM_MIDDLE_SEGMENT, THIRD_INTERMEDIATE_DISPLAY)};
	step4->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 							AnimationEffects::AnimateInToRight};
	step4->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step5 = new Animator::animationStep;
	step5->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_MIDDLE_SEGMENT, THIRD_INTERMEDIATE_DISPLAY), 	SEGMENT(BOTTOM_MIDDLE_SEGMENT, LOWER_DIGIT_MINUTE_DISPLAY)};
	step5->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 							AnimationEffects::AnimateInToRight};
	step5->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step6 = new Animator::animationStep;
	step6->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_MIDDLE_SEGMENT, LOWER_DIGIT_MINUTE_DISPLAY), 	SEGMENT(BOTTOM_RIGHT_SEGMENT, LOWER_DIGIT_MINUTE_DISPLAY)};
	step6->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 							AnimationEffects::AnimateInToTop};
	step6->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step7 = new Animator::animationStep;
	step7->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_RIGHT_SEGMENT, LOWER_DIGIT_MINUTE_DISPLAY), 	SEGMENT(TOP_RIGHT_SEGMENT, LOWER_DIGIT_MINUTE_DISPLAY)};
	step7->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToTop, 							AnimationEffects::AnimateInToTop};
	step7->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step8 = new Animator::animationStep;
	step8->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_RIGHT_SEGMENT, LOWER_DIGIT_MINUTE_DISPLAY), 		SEGMENT(TOP_MIDDLE_SEGMENT, LOWER_DIGIT_MINUTE_DISPLAY)};
	step8->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToTop, 							AnimationEffects::AnimateInToLeft};
	step8->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step9 = new Animator::animationStep;
	step9->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_MIDDLE_SEGMENT, LOWER_DIGIT_MINUTE_DISPLAY), 		SEGMENT(TOP_MIDDLE_SEGMENT, THIRD_INTERMEDIATE_DISPLAY)};
	step9->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToLeft, 							AnimationEffects::AnimateInToLeft};
	step9->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step10 = new Animator::animationStep;
	step10->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_MIDDLE_SEGMENT, THIRD_INTERMEDIATE_DISPLAY), 		SEGMENT(TOP_MIDDLE_SEGMENT, HIGHER_DIGIT_MINUTE_DISPLAY)};
	step10->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToLeft, 							AnimationEffects::AnimateInToLeft};
	step10->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step11 = new Animator::animationStep;
	step11->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_MIDDLE_SEGMENT, HIGHER_DIGIT_MINUTE_DISPLAY), 		SEGMENT(TOP_MIDDLE_SEGMENT, SECOND_INTERMEDIATE_DISPLAY)};
	step11->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToLeft, 							AnimationEffects::AnimateInToLeft};
	step11->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step12 = new Animator::animationStep;
	step12->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_MIDDLE_SEGMENT, SECOND_INTERMEDIATE_DISPLAY), 		SEGMENT(TOP_MIDDLE_SEGMENT, LOWER_DIGIT_HOUR_DISPLAY)};
	step12->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToLeft, 							AnimationEffects::AnimateInToLeft};
	step12->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step13 = new Animator::animationStep;
	step13->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_MIDDLE_SEGMENT, LOWER_DIGIT_HOUR_DISPLAY), 		SEGMENT(TOP_MIDDLE_SEGMENT, FIRST_INTERMEDIATE_DISPLAY)};
	step13->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToLeft, 							AnimationEffects::AnimateInToLeft};
	step13->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step14 = new Animator::animationStep;
	step14->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_MIDDLE_SEGMENT, FIRST_INTERMEDIATE_DISPLAY), 		SEGMENT(TOP_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step14->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToLeft, 							AnimationEffects::AnimateInToBottom};
	step14->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step15 = new Animator::animationStep;
	step15->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(TOP_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), 		SEGMENT(BOTTOM_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY)};
	step15->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom, 							AnimationEffects::AnimateInToBottom};
	step15->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};
	Animator::animationStep* step16 = new Animator::animationStep;
	step16->arrayIndex 			= new int16_t[LENGTH]								{SEGMENT(BOTTOM_RIGHT_SEGMENT, HIGHER_DIGIT_HOUR_DISPLAY), 		NO_SEGMENTS};
	step16->animationEffects 	= new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom, 							NO_ANIMATION};
	step16->easingEffects 		= new EasingBase*[LENGTH] 							{NO_EASING, 													NO_EASING};

	LinkedList<Animator::animationStep*>* allSteps = new LinkedList<Animator::animationStep*>();
	allSteps->add(preStep);
	allSteps->add(step0);
	allSteps->add(step1);
	allSteps->add(step2);
	allSteps->add(step3);
	allSteps->add(step4);
	allSteps->add(step5);
	allSteps->add(step6);
	allSteps->add(step7);
	allSteps->add(step8);
	allSteps->add(step9);
	allSteps->add(step10);
	allSteps->add(step11);
	allSteps->add(step12);
	allSteps->add(step13);
	allSteps->add(step14);
	allSteps->add(step15);
	allSteps->add(step16);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / allSteps->size();
	animation->animations 			= allSteps;
	return animation;
}