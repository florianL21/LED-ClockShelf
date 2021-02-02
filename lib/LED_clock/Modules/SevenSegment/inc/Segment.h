#ifndef __SEGMENT_H_
#define __SEGMENT_H_

#include <Arduino.h>
#include "AnimatableObject.h"
#define FASTLED_INTERNAL
#include "FastLED.h"
#include "misc.h"


class AnimationEffects;
class Segment: public AnimatableObject
{
public:
	enum direction {LEFT_TO_RIGHT = false, RIGHT_TO_LEFT = true, TOP_TO_BOTTTOM = false, BOTTOM_TO_TOP = true};

private:
    friend class AnimationEffects;

	uint8_t length;
	bool invertDirection;
	CRGB color;
	CRGB AnimationColor;
	CRGB* leds;

	void writeToLEDs(CRGB colorToSet);

	bool isOn();

public:
	Segment(CRGB LEDBuffer[], uint16_t indexOfFirstLEDInSegment, uint8_t segmentLength, direction Direction, CRGB segmentColor = CRGB::Black);
	~Segment();
	void tick(int32_t currentState);

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
