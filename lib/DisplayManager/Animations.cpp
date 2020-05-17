#include "DisplayManager.h"

void DisplayManager::InitLoadingAnimation(uint16_t totalAnimationLength)
{
	Animator::animationStep* preStep = new Animator::animationStep;
	preStep->objects = new AnimatableObject*[2] {allSegments[19], nullptr};
	preStep->animationEffects = new uint8_t[2] {Segment::ANIMATE_IN_TO_RIGHT, 0};
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[2] {allSegments[19], allSegments[18]};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_TOP};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->objects = new AnimatableObject*[2] {allSegments[18], allSegments[14]};
	step1->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_TOP};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->objects = new AnimatableObject*[2] {allSegments[14], allSegments[15]};
	step2->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step3 = new Animator::animationStep;
	step3->objects = new AnimatableObject*[2] {allSegments[15], allSegments[16]};
	step3->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_BOTTOM};
	Animator::animationStep* step4 = new Animator::animationStep;
	step4->objects = new AnimatableObject*[2] {allSegments[16], allSegments[20]};
	step4->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_BOTTOM, Segment::ANIMATE_IN_TO_BOTTOM};
	Animator::animationStep* step5 = new Animator::animationStep;
	step5->objects = new AnimatableObject*[2] {allSegments[20], nullptr};
	step5->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_BOTTOM, 0};

	LinkedList<Animator::animationStep*>* allSteps = new LinkedList<Animator::animationStep*>();
	allSteps->add(preStep);
	allSteps->add(step0);
	allSteps->add(step1);
	allSteps->add(step2);
	allSteps->add(step3);
	allSteps->add(step4);
	allSteps->add(step5);

	LoadingAnimation.animationComplexity = 2;
	LoadingAnimation.LengthPerAnimation = totalAnimationLength / allSteps->size();
	LoadingAnimation.animations = allSteps;
}