#include "Animations.h"

Animator::ComplexAmination* InitLoadingAnimation(uint16_t totalAnimationLength);
Animator::ComplexAmination* LoadingAnimation = InitLoadingAnimation(LOADING_ANIMATION_DURATION);

Animator::ComplexAmination* InitLoadingAnimation(uint16_t totalAnimationLength)
{
	#undef ANIMATION_COMPLEXITY
	#define ANIMATION_COMPLEXITY 2
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[ANIMATION_COMPLEXITY] {19, -1};
	step0->animationEffects = new uint8_t[ANIMATION_COMPLEXITY] {Segment::ANIMATE_IN_TO_RIGHT, 0};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex = new int16_t[ANIMATION_COMPLEXITY] {19, 18};
	step1->animationEffects = new uint8_t[ANIMATION_COMPLEXITY] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_TOP};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->arrayIndex = new int16_t[ANIMATION_COMPLEXITY] {18, 14};
	step2->animationEffects = new uint8_t[ANIMATION_COMPLEXITY] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_TOP};
	Animator::animationStep* step3 = new Animator::animationStep;
	step3->arrayIndex = new int16_t[ANIMATION_COMPLEXITY] {14, 15};
	step3->animationEffects = new uint8_t[ANIMATION_COMPLEXITY] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step4 = new Animator::animationStep;
	step4->arrayIndex = new int16_t[ANIMATION_COMPLEXITY] {15, 16};
	step4->animationEffects = new uint8_t[ANIMATION_COMPLEXITY] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_BOTTOM};
	Animator::animationStep* step5 = new Animator::animationStep;
	step5->arrayIndex = new int16_t[ANIMATION_COMPLEXITY] {16, 20};
	step5->animationEffects = new uint8_t[ANIMATION_COMPLEXITY] {Segment::ANIMATE_OUT_TO_BOTTOM, Segment::ANIMATE_IN_TO_BOTTOM};
	Animator::animationStep* step6 = new Animator::animationStep;
	step6->arrayIndex = new int16_t[ANIMATION_COMPLEXITY] {20, -1};
	step6->animationEffects = new uint8_t[ANIMATION_COMPLEXITY] {Segment::ANIMATE_OUT_TO_BOTTOM, 0};

	LinkedList<Animator::animationStep*>* allSteps = new LinkedList<Animator::animationStep*>();
	allSteps->add(step0);
	allSteps->add(step1);
	allSteps->add(step2);
	allSteps->add(step3);
	allSteps->add(step4);
	allSteps->add(step5);
	allSteps->add(step6);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = ANIMATION_COMPLEXITY;
	animation->LengthPerAnimation = totalAnimationLength / allSteps->size();
	animation->animations = allSteps;
	return animation;
}