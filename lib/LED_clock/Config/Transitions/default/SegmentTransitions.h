/**
 * \file SegmentTransitions.h
 * \author Florian Laschober
 * \brief The default set of animations
 *        A good set of animation for a decent amount of scenarios. But not all cases are covered by it.
 */

#ifndef __SEGMENT_TRANSITIONS_H_
#define __SEGMENT_TRANSITIONS_H_

#include "SevenSegment.h"

/**
 * \brief Lookup table to know which animation to call for which transition
 *
 */
extern Animator::ComplexAmination* TransformationLookupTable[11][11];

/**
 * \brief All avaliable animations to morph between digits
 * \addtogroup DigitMorphAnimations
 * \{
 */
extern Animator::ComplexAmination* Animate0to1;
extern Animator::ComplexAmination* Animate1to2;
extern Animator::ComplexAmination* Animate2to3;
extern Animator::ComplexAmination* Animate3to4;
extern Animator::ComplexAmination* Animate2to0;
extern Animator::ComplexAmination* Animate4to5;
extern Animator::ComplexAmination* Animate5to6;
extern Animator::ComplexAmination* Animate5to0;
extern Animator::ComplexAmination* Animate6to7;
extern Animator::ComplexAmination* Animate7to8;
extern Animator::ComplexAmination* Animate8to9;
extern Animator::ComplexAmination* Animate9to0;
extern Animator::ComplexAmination* AnimateOFFto1;
extern Animator::ComplexAmination* Animate1toOFF;
extern Animator::ComplexAmination* Animate9to8;
extern Animator::ComplexAmination* Animate8to7;
extern Animator::ComplexAmination* Animate7to6;
extern Animator::ComplexAmination* Animate6to5;
extern Animator::ComplexAmination* Animate5to4;
extern Animator::ComplexAmination* Animate4to3;
extern Animator::ComplexAmination* Animate3to2;
extern Animator::ComplexAmination* Animate2to1;
extern Animator::ComplexAmination* Animate1to0;
extern Animator::ComplexAmination* Animate0to9;
extern Animator::ComplexAmination* Animate0to5;

/** \} */
#endif