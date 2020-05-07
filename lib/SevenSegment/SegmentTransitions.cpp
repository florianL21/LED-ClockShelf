#include "SevenSegment.h"


void SevenSegment::InitAnimate0to1(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[2] {Segments[0], Segments[4]};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_OUT_TO_BOTTOM};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->objects = new AnimatableObject*[2] {Segments[1], Segments[5]};
	step1->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_OUT_TO_RIGHT};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);

	Animate0to1.animationComplexity = 2;
	Animate0to1.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate0to1.animations = AnimationStepSequence;
}

void SevenSegment::InitAnimate1to2(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[3] {Segments[1], Segments[6], Segments[3]};
	step0->animationEffects = new uint8_t[3] {Segment::ANIMATE_IN_TO_LEFT, Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->objects = new AnimatableObject*[3] {Segments[4], nullptr, nullptr};
	step1->animationEffects = new uint8_t[3] {Segment::ANIMATE_IN_TO_BOTTOM, 0, 0};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->objects = new AnimatableObject*[3] {Segments[5], nullptr, nullptr};
	step2->animationEffects = new uint8_t[3] {Segment::ANIMATE_IN_TO_RIGHT, 0, 0};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);
	AnimationStepSequence->add(step2);

	Animate1to2.animationComplexity = 3;
	Animate1to2.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate1to2.animations = AnimationStepSequence;
}


void SevenSegment::InitAnimate2to3(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[2] {Segments[4], Segments[6]};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_BOTTOM, Segment::ANIMATE_IN_TO_TOP};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animate2to3.animationComplexity = 2;
	Animate2to3.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate2to3.animations = AnimationStepSequence;
}

void SevenSegment::InitAnimate2to0(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[3] {Segments[0], Segments[3], Segments[6]};
	step0->animationEffects = new uint8_t[3] {Segment::ANIMATE_IN_TO_BOTTOM, Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_BOTTOM};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animate2to0.animationComplexity = 3;
	Animate2to0.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate2to0.animations = AnimationStepSequence;
}

void SevenSegment::InitAnimate2to1(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[4] {Segments[1], Segments[3], Segments[4], Segments[6]};
	step0->animationEffects = new uint8_t[4] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_OUT_TO_BOTTOM, Segment::ANIMATE_IN_TO_TOP};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->objects = new AnimatableObject*[4] {Segments[5], nullptr, nullptr, nullptr};
	step1->animationEffects = new uint8_t[4] {Segment::ANIMATE_OUT_TO_RIGHT, 0, 0, 0};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);

	Animate2to1.animationComplexity = 4;
	Animate2to1.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate2to1.animations = AnimationStepSequence;
}

void SevenSegment::InitAnimate3to4(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[3] {Segments[5], Segments[0], Segments[1]};
	step0->animationEffects = new uint8_t[3] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_BOTTOM, Segment::ANIMATE_OUT_TO_LEFT};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animate3to4.animationComplexity = 3;
	Animate3to4.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate3to4.animations = AnimationStepSequence;
}

void SevenSegment::InitAnimate4to5(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[3] {Segments[2], Segments[1], Segments[5]};
	step0->animationEffects = new uint8_t[3] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_LEFT, Segment::ANIMATE_IN_TO_LEFT};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animate4to5.animationComplexity = 3;
	Animate4to5.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate4to5.animations = AnimationStepSequence;
}

void SevenSegment::InitAnimate5to6(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[1] {Segments[4]};
	step0->animationEffects = new uint8_t[1] {Segment::ANIMATE_IN_TO_TOP};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animate5to6.animationComplexity = 1;
	Animate5to6.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate5to6.animations = AnimationStepSequence;
}

void SevenSegment::InitAnimate5to0(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[3] {Segments[3], Segments[4], Segments[2]};
	step0->animationEffects = new uint8_t[3] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_TOP, Segment::ANIMATE_IN_TO_TOP};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animate5to0.animationComplexity = 3;
	Animate5to0.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate5to0.animations = AnimationStepSequence;
}

void SevenSegment::InitAnimate6to7(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[4] {Segments[0], Segments[3], Segments[2], Segments[4]};
	step0->animationEffects = new uint8_t[4] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_TOP, Segment::ANIMATE_OUT_TO_BOTTOM};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->objects = new AnimatableObject*[4] {Segments[5], nullptr, nullptr, nullptr};
	step1->animationEffects = new uint8_t[4] {Segment::ANIMATE_OUT_TO_RIGHT, 0, 0, 0};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);

	Animate6to7.animationComplexity = 4;
	Animate6to7.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate6to7.animations = AnimationStepSequence;
}

void SevenSegment::InitAnimate7to8(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[2] {Segments[0], Segments[5]};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_IN_TO_BOTTOM, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->objects = new AnimatableObject*[2] {Segments[4], Segments[3]};
	step1->animationEffects = new uint8_t[2] {Segment::ANIMATE_IN_TO_TOP, Segment::ANIMATE_IN_TO_RIGHT};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);

	Animate7to8.animationComplexity = 2;
	Animate7to8.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate7to8.animations = AnimationStepSequence;
}

void SevenSegment::InitAnimate8to9(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[1] {Segments[4]};
	step0->animationEffects = new uint8_t[1] {Segment::ANIMATE_OUT_TO_BOTTOM};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animate8to9.animationComplexity = 1;
	Animate8to9.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate8to9.animations = AnimationStepSequence;
}

void SevenSegment::InitAnimate9to0(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[2] {Segments[3], Segments[4]};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_BOTTOM};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animate9to0.animationComplexity = 2;
	Animate9to0.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate9to0.animations = AnimationStepSequence;
}

void SevenSegment::InitAnimate1toOFF(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[2] {Segments[6], Segments[2]};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_BOTTOM, Segment::ANIMATE_OUT_TO_TOP};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animate1toOFF.animationComplexity = 2;
	Animate1toOFF.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	Animate1toOFF.animations = AnimationStepSequence;
}

void SevenSegment::InitAnimateOFFto1(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->objects = new AnimatableObject*[2] {Segments[2], Segments[6]};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_IN_TO_TOP, Segment::ANIMATE_IN_TO_BOTTOM};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	AnimateOFFto1.animationComplexity = 2;
	AnimateOFFto1.LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	AnimateOFFto1.animations = AnimationStepSequence;
}