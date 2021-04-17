/**
 * \file Animations.h
 * \author Florian Laschober
 * \brief Simplified animations for 12h Displays without intermediate segments
 */

#ifndef __ANIMATIONS_H_
#define __ANIMATIONS_H_

#include "DisplayManager.h"

/**
 * \brief Animation to be used during some indefinite loading operation.
 *        Loops along the outside of the higher digit hour display in a "circle".
 *        Suppposed to be used as a endlessly looping animation and to be
 *        stopped by calling the stopLooping method as soon as loading is finished.
 *
 */
extern Animator::ComplexAmination* IndefiniteLoadingAnimation;

/**
 * \brief Animation which is used to display a progress with a defined end point. Similar to a progress bar.
 */
extern Animator::ComplexAmination* LoadingProgressAnimation;

#endif
