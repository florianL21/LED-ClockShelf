#include "Animations.h"

Animator::ComplexAmination* InitLoadingAnimation(uint16_t totalAnimationLength);
Animator::ComplexAmination* LoadingAnimation = InitLoadingAnimation(LOADING_ANIMATION_DURATION);

Animator::ComplexAmination* InitLoadingAnimation(uint16_t totalAnimationLength)
{
	Animator::animationStep* preStep = new Animator::animationStep;
	preStep->arrayIndex = new int16_t[2] {0, -1};
	preStep->animationEffects = new AnimatableObject::AnimationFunction[2] {AnimationEffects::AnimateInToRight, nullptr};
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[2] {0, 1};
	step0->animationEffects = new AnimatableObject::AnimationFunction[2] {AnimationEffects::AnimateOutToRight, AnimationEffects::AnimateInToTop};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex = new int16_t[2] {1, 2};
	step1->animationEffects = new AnimatableObject::AnimationFunction[2] {AnimationEffects::AnimateOutToTop, AnimationEffects::AnimateInToTop};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->arrayIndex = new int16_t[2] {2, 3};
	step2->animationEffects = new AnimatableObject::AnimationFunction[2] {AnimationEffects::AnimateOutToTop, AnimationEffects::AnimateInToLeft};
	Animator::animationStep* step3 = new Animator::animationStep;
	step3->arrayIndex = new int16_t[2] {3, 4};
	step3->animationEffects = new AnimatableObject::AnimationFunction[2] {AnimationEffects::AnimateOutToLeft, AnimationEffects::AnimateInToBottom};
	Animator::animationStep* step4 = new Animator::animationStep;
	step4->arrayIndex = new int16_t[2] {4, 5};
	step4->animationEffects = new AnimatableObject::AnimationFunction[2] {AnimationEffects::AnimateOutToBottom, AnimationEffects::AnimateInToBottom};
	Animator::animationStep* step5 = new Animator::animationStep;
	step5->arrayIndex = new int16_t[2] {5, -1};
	step5->animationEffects = new AnimatableObject::AnimationFunction[2] {AnimationEffects::AnimateOutToBottom, nullptr};

	LinkedList<Animator::animationStep*>* allSteps = new LinkedList<Animator::animationStep*>();
	allSteps->add(preStep);
	allSteps->add(step0);
	allSteps->add(step1);
	allSteps->add(step2);
	allSteps->add(step3);
	allSteps->add(step4);
	allSteps->add(step5);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 2;
	animation->LengthPerAnimation = totalAnimationLength / allSteps->size();
	animation->animations = allSteps;
	return animation;
}