#include "SegmentTransitions.h"

Animator::ComplexAmination* TransformationLookupTable[10][10] = {
//To:0  1  2  3  4  5  6  7  8  9
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//from 0
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//from 1
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//from 2
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//from 3
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//from 4
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//from 5
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//from 6
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//from 7
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//from 8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0} //from 9
};

Animator::ComplexAmination* InitAnimate0to1(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate1to2(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate2to3(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate2to0(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate2to1(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate3to4(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate4to5(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate5to6(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate5to0(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate6to7(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate7to8(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate8to9(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate9to0(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimateOFFto1(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate1toOFF(uint16_t totalAnimationLength);
Animator::ComplexAmination* Animate0to1 = InitAnimate0to1(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate1to2 = InitAnimate1to2(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate2to3 = InitAnimate2to3(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate3to4 = InitAnimate2to0(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate2to0 = InitAnimate2to1(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate2to1 = InitAnimate3to4(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate4to5 = InitAnimate4to5(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate5to6 = InitAnimate5to6(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate5to0 = InitAnimate5to0(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate6to7 = InitAnimate6to7(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate7to8 = InitAnimate7to8(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate8to9 = InitAnimate8to9(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate9to0 = InitAnimate9to0(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* AnimateOFFto1 = InitAnimateOFFto1(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate1toOFF = InitAnimate1toOFF(DIGIT_ANIMATION_SPEED);

Animator::ComplexAmination* InitAnimate0to1(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[2] {0, 4};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_OUT_TO_BOTTOM};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex = new int16_t[2] {1, 5};
	step1->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_OUT_TO_RIGHT};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 2;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate1to2(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[3] {1, 6, 3};
	step0->animationEffects = new uint8_t[3] {Segment::ANIMATE_IN_TO_LEFT, Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex = new int16_t[3] {4, -1, -1};
	step1->animationEffects = new uint8_t[3] {Segment::ANIMATE_IN_TO_BOTTOM, 0, 0};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->arrayIndex = new int16_t[3] {5, -1, -1};
	step2->animationEffects = new uint8_t[3] {Segment::ANIMATE_IN_TO_RIGHT, 0, 0};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);
	AnimationStepSequence->add(step2);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 3;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}


Animator::ComplexAmination* InitAnimate2to3(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[2] {4, 6};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_BOTTOM, Segment::ANIMATE_IN_TO_TOP};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 2;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate2to0(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[3] {0, 3, 6};
	step0->animationEffects = new uint8_t[3] {Segment::ANIMATE_IN_TO_BOTTOM, Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_BOTTOM};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 3;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate2to1(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[4] {1, 3, 4, 6};
	step0->animationEffects = new uint8_t[4] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_OUT_TO_BOTTOM, Segment::ANIMATE_IN_TO_TOP};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex = new int16_t[4] {5, -1, -1, -1};
	step1->animationEffects = new uint8_t[4] {Segment::ANIMATE_OUT_TO_RIGHT, 0, 0, 0};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 4;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate3to4(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[3] {5, 0, 1};
	step0->animationEffects = new uint8_t[3] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_BOTTOM, Segment::ANIMATE_OUT_TO_LEFT};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 3;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate4to5(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[3] {2, 1, 5};
	step0->animationEffects = new uint8_t[3] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_IN_TO_LEFT, Segment::ANIMATE_IN_TO_LEFT};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 3;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate5to6(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[1] {4};
	step0->animationEffects = new uint8_t[1] {Segment::ANIMATE_IN_TO_TOP};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 1;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate5to0(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[3] {3, 4, 2};
	step0->animationEffects = new uint8_t[3] {Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_TOP, Segment::ANIMATE_IN_TO_TOP};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 3;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate6to7(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[4] {0, 3, 2, 4};
	step0->animationEffects = new uint8_t[4] {Segment::ANIMATE_OUT_TO_TOP, Segment::ANIMATE_OUT_TO_RIGHT, Segment::ANIMATE_IN_TO_TOP, Segment::ANIMATE_OUT_TO_BOTTOM};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex = new int16_t[4] {5, -1, -1, -1};
	step1->animationEffects = new uint8_t[4] {Segment::ANIMATE_OUT_TO_RIGHT, 0, 0, 0};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 4;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate7to8(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[2] {0, 5};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_IN_TO_BOTTOM, Segment::ANIMATE_IN_TO_LEFT};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex = new int16_t[2] {4, 3};
	step1->animationEffects = new uint8_t[2] {Segment::ANIMATE_IN_TO_TOP, Segment::ANIMATE_IN_TO_RIGHT};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 2;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate8to9(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[1] {4};
	step0->animationEffects = new uint8_t[1] {Segment::ANIMATE_OUT_TO_BOTTOM};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 1;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate9to0(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[2] {3, 4};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_LEFT, Segment::ANIMATE_IN_TO_BOTTOM};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 2;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate1toOFF(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[2] {6, 2};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_OUT_TO_BOTTOM, Segment::ANIMATE_OUT_TO_TOP};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 2;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimateOFFto1(uint16_t totalAnimationLength)
{
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[2] {2, 6};
	step0->animationEffects = new uint8_t[2] {Segment::ANIMATE_IN_TO_TOP, Segment::ANIMATE_IN_TO_BOTTOM};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = 2;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}