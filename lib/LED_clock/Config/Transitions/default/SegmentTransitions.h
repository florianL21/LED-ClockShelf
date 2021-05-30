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

void SetupAllMorphAnimations(uint16_t animationLength);
void ChangeMorphAnimationSpeed(uint16_t newAnimationLength);
#endif