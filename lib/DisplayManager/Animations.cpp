#include "DisplayManager.h"

void DisplayManager::InitLoadingAnimation(uint16_t totalAnimationLength)
{
	Animator::animationStep* preStep = new Animator::animationStep;
	preStep->objects = new AnimatableObject*[2] {allSegments[0], nullptr};
	preStep->animationEffects = new uint8_t[2] {Segment::ANIMATE_IN_TO_RIGHT, 0};
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[2] {allSegments[0], allSegments[1]};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_RIGHT};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->objects = new AnimatableObject*[2] {allSegments[1], allSegments[2]};
	step1->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_RIGHT};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->objects = new AnimatableObject*[2] {allSegments[2], allSegments[3]};
	step2->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_RIGHT};
	Animator::animationStep* step3 = new Animator::animationStep;
	step3->objects = new AnimatableObject*[2] {allSegments[3], allSegments[4]};
	step3->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_RIGHT};
	Animator::animationStep* step4 = new Animator::animationStep;
	step4->objects = new AnimatableObject*[2] {allSegments[4], allSegments[5]};
	step4->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_RIGHT};
	Animator::animationStep* step5 = new Animator::animationStep;
	step5->objects = new AnimatableObject*[2] {allSegments[5], allSegments[6]};
	step5->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_TOP};
	Animator::animationStep* step6 = new Animator::animationStep;
	step6->objects = new AnimatableObject*[2] {allSegments[6], allSegments[7]};
	step6->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_TOP};
	Animator::animationStep* step7 = new Animator::animationStep;
	step7->objects = new AnimatableObject*[2] {allSegments[7], allSegments[8]};
	step7->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_TOP};
	Animator::animationStep* step8 = new Animator::animationStep;
	step8->objects = new AnimatableObject*[2] {allSegments[8], allSegments[9]};
	step8->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step9 = new Animator::animationStep;
	step9->objects = new AnimatableObject*[2] {allSegments[9], allSegments[10]};
	step9->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step10 = new Animator::animationStep;
	step10->objects = new AnimatableObject*[2] {allSegments[10], allSegments[11]};
	step10->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step11 = new Animator::animationStep;
	step11->objects = new AnimatableObject*[2] {allSegments[11], allSegments[12]};
	step11->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step12 = new Animator::animationStep;
	step12->objects = new AnimatableObject*[2] {allSegments[12], allSegments[13]};
	step12->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step13 = new Animator::animationStep;
	step13->objects = new AnimatableObject*[2] {allSegments[13], allSegments[14]};
	step13->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_BOTTOM};
	Animator::animationStep* step14 = new Animator::animationStep;
	step14->objects = new AnimatableObject*[2] {allSegments[14], allSegments[15]};
	step14->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_RIGHT};
	Animator::animationStep* step15 = new Animator::animationStep;
	step15->objects = new AnimatableObject*[2] {allSegments[15], nullptr};
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

	LoadingAnimation.animationComplexity = 2;
	LoadingAnimation.LengthPerAnimation = totalAnimationLength / allSteps->size();
	LoadingAnimation.animations = allSteps;
}