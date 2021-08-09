/*
 * Easing Functions: Copyright (c) 2010 Andy Brown
 * http://www.andybrown.me.uk
 *
 * This work is licensed under a Creative Commons
 * Attribution_ShareAlike 3.0 Unported License.
 * http://creativecommons.org/licenses/by_sa/3.0/
 */

#include "EasingBase.h"

/*
 * Default constructor
 */

EasingBase::EasingBase()
{
	_change = 0;
	_type = EASE_IN;
}

EasingBase::EasingBase(easingType_t type_)
{
	_change = 0;
	_type = type_;
}

EasingBase::~EasingBase()
{

}

void EasingBase::setType(easingType_t type_)
{
	_type = type_;
}

NUMBER EasingBase::ease(NUMBER time_) const
{
	switch (_type)
	{
	case EASE_IN:
		return easeIn(time_);
		break;
	case EASE_OUT:
		return easeOut(time_);
		break;
	case EASE_IN_OUT:
		return easeInOut(time_);
		break;
	default:
		return 0;
		break;
	}
}


/*
 * Set the duration
 */

void EasingBase::setDuration(NUMBER duration_)
{
	_duration=duration_;
}


/*
 * Set the total change in position
 */

void EasingBase::setTotalChangeInPosition(NUMBER totalChangeInPosition_)
{
	_change=totalChangeInPosition_;
}
