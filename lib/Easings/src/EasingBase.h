/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution_ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by_sa/3.0/
 */

#ifndef __CD7D63F1_57BA_4f1b_A832_758091A49A7A
#define __CD7D63F1_57BA_4f1b_A832_758091A49A7A

#include "EasingConstants.h"


// base class for easing functions

class EasingBase
{
protected:
	NUMBER _change;
	NUMBER _duration;
	easingType_t _type;

public:

	// default constructor
	EasingBase();

	EasingBase(easingType_t type_);

	//virtual destructor to make proper deletion possible
	virtual ~EasingBase();

	// single method to set the type for all easings
	void setType(easingType_t type_);

	// single method for all easings to execute
	NUMBER ease(NUMBER time_) const;

	// easing API methods
	virtual NUMBER easeIn(NUMBER time_) const=0;
	virtual NUMBER easeOut(NUMBER time_) const=0;
	virtual NUMBER easeInOut(NUMBER time_) const=0;

	// common properties
	void setDuration(NUMBER duration_);
	void setTotalChangeInPosition(NUMBER totalChangeInPosition_);
};


#endif
