#include "SegmentTransitions.h"

/**
 * \brief Easings have to be setup before any of the initAnimate functions are called
 * 		  it's only possible to reuse an easing if the multiple anstances of
 * 		  it running at the same time have the exact same settings. This includes duration too.
 * \addtogroup AnimationEasings
 * \{
 */
BounceEase* bounceEaseOut 	= new BounceEase(EASE_OUT);
CubicEase* cubicEaseInOut 	= new CubicEase(EASE_IN_OUT);
CubicEase* cubicEaseIn 		= new CubicEase(EASE_IN);
CubicEase* cubicEaseOut 	= new CubicEase(EASE_OUT);
/** \} */

/**
 * \brief Function prototypes for all segment transition animation init functions
 * \addtogroup TransitionAnimationInitFunctions
 * \{
 */
Animator::ComplexAmination* InitAnimate0to1(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate1to2(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate2to3(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate2to0(uint16_t totalAnimationLength);
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
Animator::ComplexAmination* InitAnimate9to8(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate8to7(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate7to6(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate6to5(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate5to4(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate4to3(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate3to2(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate2to1(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate1to0(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate0to9(uint16_t totalAnimationLength);
Animator::ComplexAmination* InitAnimate0to5(uint16_t totalAnimationLength);
/** \} */

/**
 * \brief Global variables for all segment transition animations
 * \addtogroup TransitionAnimations
 * \{
 */
Animator::ComplexAmination* Animate0to1 	= InitAnimate0to1(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate1to2 	= InitAnimate1to2(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate2to3 	= InitAnimate2to3(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate3to4 	= InitAnimate3to4(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate2to0 	= InitAnimate2to0(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate4to5 	= InitAnimate4to5(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate5to6 	= InitAnimate5to6(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate5to0 	= InitAnimate5to0(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate6to7 	= InitAnimate6to7(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate7to8 	= InitAnimate7to8(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate8to9 	= InitAnimate8to9(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate9to0 	= InitAnimate9to0(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* AnimateOFFto1 	= InitAnimateOFFto1(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate1toOFF 	= InitAnimate1toOFF(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate9to8 	= InitAnimate9to8(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate8to7 	= InitAnimate8to7(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate7to6 	= InitAnimate7to6(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate6to5 	= InitAnimate6to5(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate5to4 	= InitAnimate5to4(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate4to3 	= InitAnimate4to3(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate3to2 	= InitAnimate3to2(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate2to1 	= InitAnimate2to1(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate1to0 	= InitAnimate1to0(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate0to9 	= InitAnimate0to9(DIGIT_ANIMATION_SPEED);
Animator::ComplexAmination* Animate0to5 	= InitAnimate0to5(DIGIT_ANIMATION_SPEED);
/** \} */

/**
 * \brief This transformation lookup table defines which animation to call for which transition.
 * 		  Every row decides from which digits we want to morph and than the column of the digit we want to morph to is selected.
 * 		  The resulting animation is then executed in case that transition is neccesary.
 *
 */
Animator::ComplexAmination* TransformationLookupTable[11][11] = {
		  //To:0              1              2              3              4              5              6              7              8              9             OFF
/*from 0	*/{nullptr      , Animate0to1  , nullptr      , nullptr      , nullptr      , Animate0to5  , nullptr      , nullptr      , nullptr      , Animate0to9  , nullptr      },
/*from 1	*/{Animate1to0  , nullptr      , Animate1to2  , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , Animate1toOFF},
/*from 2	*/{Animate2to0  , Animate2to1  , nullptr      , Animate2to3  , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      },
/*from 3	*/{nullptr      , nullptr      , Animate3to2  , nullptr      , Animate3to4  , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      },
/*from 4	*/{nullptr      , nullptr      , nullptr      , Animate4to3  , nullptr      , Animate4to5  , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      },
/*from 5	*/{Animate5to0  , nullptr      , nullptr      , nullptr      , Animate5to4  , nullptr      , Animate5to6  , nullptr      , nullptr      , nullptr      , nullptr      },
/*from 6	*/{nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , Animate6to5  , nullptr      , Animate6to7  , nullptr      , nullptr      , nullptr      },
/*from 7	*/{nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , Animate7to6  , nullptr      , Animate7to8  , nullptr      , nullptr      },
/*from 8	*/{nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , Animate8to7  , nullptr      , Animate8to9  , nullptr      },
/*from 9	*/{Animate9to0  , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , Animate9to8  , nullptr      , nullptr      },
/*from OFF	*/{nullptr      , AnimateOFFto1, nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      , nullptr      }
};

Animator::ComplexAmination* InitAnimate0to1(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	2
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH]								{TOP_LEFT_SEGMENT, 						BOTTOM_LEFT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH]	{AnimationEffects::AnimateOutToTop, 	AnimationEffects::AnimateOutToBottom};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseIn, 							cubicEaseIn};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex 		= new int16_t[LENGTH]								{TOP_MIDDLE_SEGMENT, 					BOTTOM_MIDDLE_SEGMENT};
	step1->animationEffects = new AnimatableObject::AnimationFunction[LENGTH]	{AnimationEffects::AnimateOutToRight, 	AnimationEffects::AnimateOutToRight};
	step1->easingEffects 	= new EasingBase*[LENGTH]							{cubicEaseOut, 							cubicEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);

	Animator::ComplexAmination* animation 	= new Animator::ComplexAmination();
	animation->animationComplexity 			= LENGTH;
	animation->LengthPerAnimation 			= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 					= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate1to2(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	2
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH]								{BOTTOM_RIGHT_SEGMENT, 					CENTER_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH]	{AnimationEffects::AnimateOutToTop, 	AnimationEffects::AnimateInToLeft};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseIn,							NO_EASING};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_LEFT_SEGMENT, 					NO_SEGMENTS};
	step1->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToBottom,	NO_ANIMATION};
	step1->easingEffects 	= new EasingBase*[LENGTH] 							{NO_EASING, 							NO_EASING};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_MIDDLE_SEGMENT, 				TOP_MIDDLE_SEGMENT};
	step2->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToRight, 	AnimationEffects::AnimateInToLeft};
	step2->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut, 						bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);
	AnimationStepSequence->add(step2);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate2to3(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	2
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_LEFT_SEGMENT, 					BOTTOM_RIGHT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom, 	AnimationEffects::AnimateInToTop};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut, 						bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate2to0(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	3
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{TOP_LEFT_SEGMENT, 						CENTER_SEGMENT, 						BOTTOM_RIGHT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToBottom, 	AnimationEffects::AnimateOutToRight, 	AnimationEffects::AnimateInToBottom};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut, 						cubicEaseInOut,							bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = LENGTH;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size()+1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate3to4(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	3
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex = new int16_t[LENGTH] 									{BOTTOM_MIDDLE_SEGMENT, 				TOP_LEFT_SEGMENT, 						TOP_MIDDLE_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 	AnimationEffects::AnimateInToBottom, 	AnimationEffects::AnimateOutToLeft};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut, 						bounceEaseOut,							bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = LENGTH;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate4to5(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	3
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{TOP_RIGHT_SEGMENT, 					TOP_MIDDLE_SEGMENT, 				BOTTOM_MIDDLE_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToTop, 	AnimationEffects::AnimateInToLeft, 	AnimationEffects::AnimateInToLeft};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut, 						bounceEaseOut,						bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity = LENGTH;
	animation->LengthPerAnimation = totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations = AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate5to6(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	1
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[1] 								{BOTTOM_LEFT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[1] 	{AnimationEffects::AnimateInToTop};
	step0->easingEffects 	= new EasingBase*[LENGTH] 						{bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate5to0(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	3
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{CENTER_SEGMENT, 						BOTTOM_LEFT_SEGMENT, 					TOP_RIGHT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 	AnimationEffects::AnimateInToBottom, 	AnimationEffects::AnimateInToTop};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut, 						bounceEaseOut,							bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate6to7(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	3
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{TOP_LEFT_SEGMENT, 						CENTER_SEGMENT, 						TOP_RIGHT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToTop, 	AnimationEffects::AnimateOutToLeft, 	AnimationEffects::AnimateInToBottom};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseIn, 							cubicEaseIn,							cubicEaseOut};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_LEFT_SEGMENT, 					NO_SEGMENTS, 							NO_SEGMENTS};
	step1->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom, 	NO_ANIMATION, 							NO_ANIMATION};
	step1->easingEffects 	= new EasingBase*[LENGTH] 							{NO_EASING, 							NO_EASING,								NO_EASING};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_MIDDLE_SEGMENT, 				NO_SEGMENTS, 							NO_SEGMENTS};
	step2->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 	NO_ANIMATION, 							NO_ANIMATION};
	step2->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseOut, 							NO_EASING,								NO_EASING};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);
	AnimationStepSequence->add(step2);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate7to8(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	2
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{TOP_LEFT_SEGMENT, 						BOTTOM_MIDDLE_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToBottom, 	AnimationEffects::AnimateInToLeft};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseIn, 							cubicEaseIn};

	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_LEFT_SEGMENT, 					CENTER_SEGMENT};
	step1->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToTop, 		AnimationEffects::AnimateInToRight};
	step1->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseOut, 							cubicEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate8to9(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	1
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_LEFT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate9to0(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	2
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{CENTER_SEGMENT, 						BOTTOM_LEFT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToLeft, 	AnimationEffects::AnimateInToBottom};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut, 						bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate1toOFF(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	2
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_RIGHT_SEGMENT, 					TOP_RIGHT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom, 	AnimationEffects::AnimateOutToTop};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseInOut, 						cubicEaseInOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimateOFFto1(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH	2
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{TOP_RIGHT_SEGMENT, 				BOTTOM_RIGHT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToTop, 	AnimationEffects::AnimateInToBottom};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseInOut, 					cubicEaseInOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate9to8(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 1
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_LEFT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToTop};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate8to7(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 3
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{TOP_LEFT_SEGMENT, 						CENTER_SEGMENT, 						BOTTOM_LEFT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToTop, 	AnimationEffects::AnimateOutToRight, 	AnimationEffects::AnimateOutToBottom};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseIn, 							cubicEaseIn, 							cubicEaseIn};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_MIDDLE_SEGMENT, 				NO_SEGMENTS, 							NO_SEGMENTS};
	step1->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 	NO_ANIMATION, 							NO_ANIMATION};
	step1->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseOut, 							cubicEaseOut, 							NO_EASING};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate7to6(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 3
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{TOP_RIGHT_SEGMENT, 					TOP_LEFT_SEGMENT, 						BOTTOM_MIDDLE_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToTop, 	AnimationEffects::AnimateInToBottom, 	AnimationEffects::AnimateInToLeft};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseIn, 							cubicEaseIn, 							cubicEaseIn};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex 		= new int16_t[LENGTH] 								{CENTER_SEGMENT, 						BOTTOM_LEFT_SEGMENT, 					NO_SEGMENTS};
	step1->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToRight, 	AnimationEffects::AnimateInToTop, 		NO_ANIMATION};
	step1->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseOut, 							cubicEaseOut, 							NO_EASING};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate6to5(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 1
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_LEFT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate5to4(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 3
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{TOP_MIDDLE_SEGMENT, 					TOP_RIGHT_SEGMENT, 						BOTTOM_MIDDLE_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 	AnimationEffects::AnimateInToBottom,	AnimationEffects::AnimateOutToRight};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut, 						bounceEaseOut, 							bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate4to3(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 3
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{TOP_LEFT_SEGMENT, 						TOP_MIDDLE_SEGMENT, 				BOTTOM_MIDDLE_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToTop, 	AnimationEffects::AnimateInToRight,	AnimationEffects::AnimateInToLeft};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut, 						bounceEaseOut, 						bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate3to2(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 2
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_RIGHT_SEGMENT, 					BOTTOM_LEFT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom, 	AnimationEffects::AnimateInToTop};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut, 						bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate2to1(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 2
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{TOP_MIDDLE_SEGMENT, 					CENTER_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToRight, 	AnimationEffects::AnimateOutToLeft};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseInOut, 						cubicEaseIn};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_LEFT_SEGMENT, 					NO_SEGMENTS};
	step1->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom, 	NO_ANIMATION};
	step1->easingEffects 	= new EasingBase*[LENGTH] 							{NO_EASING, 							NO_EASING};
	Animator::animationStep* step2 = new Animator::animationStep;
	step2->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_RIGHT_SEGMENT, 					BOTTOM_MIDDLE_SEGMENT};
	step2->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToTop, 		AnimationEffects::AnimateOutToRight};
	step2->easingEffects 	= new EasingBase*[LENGTH] 							{NO_EASING, 							NO_EASING};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);
	AnimationStepSequence->add(step2);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate1to0(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 2
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{TOP_MIDDLE_SEGMENT, 					BOTTOM_MIDDLE_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToLeft, 	AnimationEffects::AnimateInToLeft};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseIn, 							cubicEaseIn};
	Animator::animationStep* step1 = new Animator::animationStep;
	step1->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_LEFT_SEGMENT, 					TOP_LEFT_SEGMENT};
	step1->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateInToTop, 		AnimationEffects::AnimateInToBottom};
	step1->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut, 						bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);
	AnimationStepSequence->add(step1);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate0to9(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 2
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{BOTTOM_LEFT_SEGMENT, 					CENTER_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToTop, 	AnimationEffects::AnimateInToRight};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{bounceEaseOut, 						bounceEaseOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}

Animator::ComplexAmination* InitAnimate0to5(uint16_t totalAnimationLength)
{
	#undef LENGTH
	#define LENGTH 3
	Animator::animationStep* step0 = new Animator::animationStep;
	step0->arrayIndex 		= new int16_t[LENGTH] 								{TOP_RIGHT_SEGMENT, 					CENTER_SEGMENT, 					BOTTOM_LEFT_SEGMENT};
	step0->animationEffects = new AnimatableObject::AnimationFunction[LENGTH] 	{AnimationEffects::AnimateOutToBottom, 	AnimationEffects::AnimateInToLeft, 	AnimationEffects::AnimateOutToBottom};
	step0->easingEffects 	= new EasingBase*[LENGTH] 							{cubicEaseInOut, 						cubicEaseInOut, 					cubicEaseInOut};

	LinkedList<Animator::animationStep*>* AnimationStepSequence = new LinkedList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}