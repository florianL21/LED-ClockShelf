#include "Animations.h"

Animator::ComplexAmination* InitLoadingAnimation(uint16_t totalAnimationLength);
Animator::ComplexAmination* LoadingAnimation = InitLoadingAnimation(LOADING_ANIMATION_DURATION);

Animator::ComplexAmination* InitLoadingAnimation(uint16_t totalAnimationLength)
{
	Animator::animationStep* preStep = new Animator::animationStep;
	preStep->arrayIndex = new int16_t[2] {0, -1};
	preStep->animationEffects = new uint8_t[2] {Segment::ANIMATE_IN_TO_RIGHT, 0};
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[2] {0, 1};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_RIGHT};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex = new int16_t[2] {1, 2};
	step1->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_RIGHT};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->arrayIndex = new int16_t[2] {2, 3};
	step2->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_RIGHT};
	Animator::animationStep* step3 = new Animator::animationStep;
	step3->arrayIndex = new int16_t[2] {3, 4};
	step3->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_RIGHT};
	Animator::animationStep* step4 = new Animator::animationStep;
	step4->arrayIndex = new int16_t[2] {4, 5};
	step4->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_RIGHT};
	Animator::animationStep* step5 = new Animator::animationStep;
	step5->arrayIndex = new int16_t[2] {5, 6};
	step5->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_TOP};
	Animator::animationStep* step6 = new Animator::animationStep;
	step6->arrayIndex = new int16_t[2] {6, 7};
	step6->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_TOP};
	Animator::animationStep* step7 = new Animator::animationStep;
	step7->arrayIndex = new int16_t[2] {7, 8};
	step7->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_TOP};
	Animator::animationStep* step8 = new Animator::animationStep;
	step8->arrayIndex = new int16_t[2] {8, 9};
	step8->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step9 = new Animator::animationStep;
	step9->arrayIndex = new int16_t[2] {9, 10};
	step9->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step10 = new Animator::animationStep;
	step10->arrayIndex = new int16_t[2] {10, 11};
	step10->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step11 = new Animator::animationStep;
	step11->arrayIndex = new int16_t[2] {11, 12};
	step11->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step12 = new Animator::animationStep;
	step12->arrayIndex = new int16_t[2] {12, 13};
	step12->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step13 = new Animator::animationStep;
	step13->arrayIndex = new int16_t[2] {13, 14};
	step13->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_BOTTOM};
	Animator::animationStep* step14 = new Animator::animationStep;
	step14->arrayIndex = new int16_t[2] {14, 15};
	step14->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_RIGHT};
	Animator::animationStep* step15 = new Animator::animationStep;
	step15->arrayIndex = new int16_t[2] {15, -1};
	step15->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, 0};

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

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 2;
	animation->LengthPerAnimation = totalAnimationLength / allSteps->size();
	animation->animations = allSteps;
	return animation;
}