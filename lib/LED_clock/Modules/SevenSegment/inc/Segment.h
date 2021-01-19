#ifndef __SEGMENT_H_
#define __SEGMENT_H_

#include <Arduino.h>
#include "AnimatableObject.h"
#define FASTLED_INTERNAL
#include "FastLED.h"


class AnimationEffects;
class Segment: public AnimatableObject
{
public:
	//for directional animations it is iportant that right animations are always first and their left counterpart is always one ID higer
	enum animation
	{
		ANIMATE_OUT_TO_RIGHT = 0,
		ANIMATE_OUT_TO_BOTTOM = 0,
		ANIMATE_OUT_TO_LEFT = 1,
		ANIMATE_OUT_TO_TOP = 1,
		ANIMATE_IN_TO_RIGHT = 2,
		ANIMATE_IN_TO_BOTTOM = 2,
		ANIMATE_IN_TO_LEFT = 3,
		ANIMATE_IN_TO_TOP = 3,
		AMINATE_SINGLE_LED_TO_RIGHT = 4,
		AMINATE_SINGLE_LED_TO_BOTTOM = 4,
		AMINATE_SINGLE_LED_TO_LEFT = 5,
		AMINATE_SINGLE_LED_TO_TOP = 5,
		__LAST_DIRECTIONAL_EFFECT = 6, //Internal value used to determine if an animation has a direction
		ANIMATE_MIDDLE_DOT_FLASH = 6
	};
	enum direction {LEFT_TO_RIGHT = false, RIGHT_TO_LEFT = true, TOP_TO_BOTTTOM = false, BOTTOM_TO_TOP = true};

private:
    friend class AnimationEffects;

	uint8_t length;
	bool invertDirection;
	CRGB color;
	CRGB AnimationColor;
	CRGB* leds;
	bool isOn;
	
	void writeToLEDs(CRGB colorToSet);
	void onAnimationStart();
	void setAnimationEffect(uint8_t newEffect);

public:
	Segment(CRGB LEDBuffer[], uint16_t indexOfFirstLEDInSegment, uint8_t segmentLength, direction Direction, CRGB segmentColor = CRGB::Black);
	~Segment();
	void tick();

	/**
	 * @brief sets the color of the segment without displaying the change
	 */
	void setColor(CRGB SegmentColor);

	/**
	 * @brief sets the color of the segment and updates it automatically in case the segment is turned on
	 */
	void updateColor(CRGB SegmentColor);

	/**
	 * @brief Sets the color of the segment and immidiatley writes is out to the leds
	 */ 
	void displayColor(CRGB SegmentColor);
	void display();
	/**
	 * @brief Turns off the leds of this segment but doesn't change the stored color of the segment
	 */ 
	void off();
	void updateAnimationColor(CRGB newColor);
	
};


#endif
