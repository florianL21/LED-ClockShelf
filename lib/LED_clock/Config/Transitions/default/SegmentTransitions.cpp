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

typedef Animator::ComplexAmination* (*AnimationInitFunction)(uint16_t totalAnimationLength);

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
 * \brief This transformation lookup table defines which animation to call for which transition.
 * 		  Every row decides from which digits we want to morph and than the column of the digit we want to morph to is selected.
 * 		  The resulting animation is then executed in case that transition is neccesary.
 *
 */
Animator::ComplexAmination* TransformationLookupTable[11][11] = {
		  //To:0			1				2				3				4				5				6				7				8				9				OFF
/*from 0	*/{nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		},
/*from 1	*/{nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		},
/*from 2	*/{nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		},
/*from 3	*/{nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		},
/*from 4	*/{nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		},
/*from 5	*/{nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		},
/*from 6	*/{nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		},
/*from 7	*/{nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		},
/*from 8	*/{nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		},
/*from 9	*/{nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		},
/*from OFF	*/{nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		, nullptr		}
};

AnimationInitFunction TransformationInitLookupTable[11][11] = {
		  //To:0              	1              		2              		3              		4              		5              		6              		7              		8              		9             OFF
/*from 0	*/{nullptr			, InitAnimate0to1	, nullptr			, nullptr			, nullptr			, InitAnimate0to5	, nullptr			, nullptr			, nullptr			, InitAnimate0to9	, nullptr			},
/*from 1	*/{InitAnimate1to0	, nullptr			, InitAnimate1to2	, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, InitAnimate1toOFF	},
/*from 2	*/{InitAnimate2to0	, InitAnimate2to1	, nullptr			, InitAnimate2to3	, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			},
/*from 3	*/{nullptr			, nullptr			, InitAnimate3to2	, nullptr			, InitAnimate3to4	, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			},
/*from 4	*/{nullptr			, nullptr			, nullptr			, InitAnimate4to3	, nullptr			, InitAnimate4to5	, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			},
/*from 5	*/{InitAnimate5to0	, nullptr			, nullptr			, nullptr			, InitAnimate5to4	, nullptr			, InitAnimate5to6	, nullptr			, nullptr			, nullptr			, nullptr			},
/*from 6	*/{nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, InitAnimate6to5	, nullptr			, InitAnimate6to7	, nullptr			, nullptr			, nullptr			},
/*from 7	*/{nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, InitAnimate7to6	, nullptr			, InitAnimate7to8	, nullptr			, nullptr			},
/*from 8	*/{nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, InitAnimate8to7	, nullptr			, InitAnimate8to9	, nullptr			},
/*from 9	*/{InitAnimate9to0	, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, InitAnimate9to8	, nullptr			, nullptr			},
/*from OFF	*/{nullptr			, InitAnimateOFFto1	, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			, nullptr			}
};


void cleanupMorphAnimation(Animator::ComplexAmination* animation)
{
	int animationChainLength = animation->animations->size();
	for (int i = 0; i < animationChainLength; i++)
	{
		Animator::animationStep* currentStep = animation->animations->get(i);
		delete currentStep->animationEffects;
		delete currentStep->arrayIndex;
		delete currentStep->easingEffects;
		delete currentStep;
	}
	animation->animations->clear();
	delete animation->animations; //TODO: check if problematic
	delete animation;
}

void SetupAllMorphAnimations(uint16_t animationLength)
{
	for (uint8_t i = 0; i < 11; i++)
	{
		for (uint8_t j = 0; j < 11; j++)
		{
			if(TransformationInitLookupTable[i][j] != nullptr)
			{
				if(TransformationLookupTable[i][j] != nullptr)
				{
					cleanupMorphAnimation(TransformationLookupTable[i][j]);
				}
				TransformationLookupTable[i][j] = TransformationInitLookupTable[i][j](animationLength);
			}
		}
	}
}

void ChangeMorphAnimationSpeed(uint16_t newAnimationLength)
{
	for (uint8_t i = 0; i < 11; i++)
	{
		for (uint8_t j = 0; j < 11; j++)
		{
			if(TransformationLookupTable[i][j] != nullptr)
			{
				TransformationLookupTable[i][j]->LengthPerAnimation = newAnimationLength / (TransformationLookupTable[i][j]->animations->size() + 1);
			}
		}
	}
}

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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
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

	DynamicList<Animator::animationStep*>* AnimationStepSequence = new DynamicList<Animator::animationStep*>();
	AnimationStepSequence->add(step0);

	Animator::ComplexAmination* animation = new Animator::ComplexAmination();
	animation->animationComplexity 	= LENGTH;
	animation->LengthPerAnimation 	= totalAnimationLength / (AnimationStepSequence->size() + 1); //+1 because I have to account for the last animation also taking time.
	animation->animations 			= AnimationStepSequence;
	return animation;
}