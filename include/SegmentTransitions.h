#ifndef __SEGMENT_TRANSITIONS_H_
#define __SEGMENT_TRANSITIONS_H_

#include "SevenSegment.h"

#define SEGMENT_OFF		10

extern Animator::ComplexAmination* TransformationLookupTable[11][11];
extern Animator::ComplexAmination* Animate0to1;
extern Animator::ComplexAmination* Animate1to2;
extern Animator::ComplexAmination* Animate2to3;
extern Animator::ComplexAmination* Animate3to4;
extern Animator::ComplexAmination* Animate2to0;
extern Animator::ComplexAmination* Animate2to1;
extern Animator::ComplexAmination* Animate4to5;
extern Animator::ComplexAmination* Animate5to6;
extern Animator::ComplexAmination* Animate5to0;
extern Animator::ComplexAmination* Animate6to7;
extern Animator::ComplexAmination* Animate7to8;
extern Animator::ComplexAmination* Animate8to9;
extern Animator::ComplexAmination* Animate9to0;
extern Animator::ComplexAmination* AnimateOFFto1;
extern Animator::ComplexAmination* Animate1toOFF;

#endif