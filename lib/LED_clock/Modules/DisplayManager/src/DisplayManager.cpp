/**
 * \file DisplayManager.cpp
 * \author Florian Laschober
 * \brief Implementation of the DisplayManager class member functions
 */


#include "DisplayManager.h"

DisplayManager* DisplayManager::instance = nullptr;
LinkedList<DisplayManager::SegmentInstanceError>* DisplayManager::SegmentIndexErrorList = nullptr;

DisplayManager::DisplayManager()
{
	FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical

	#if APPEND_DOWN_LIGHTERS == false
		FastLED.addLeds<WS2812B, DOWNLIGHT_LED_DATA_PIN, GRB>(DownlightLeds, ADDITIONAL_LEDS);
	#endif

	for (uint16_t i = 0; i < NUM_LEDS; i++)
	{
		leds[i] = CRGB::Black;
	}

	#if APPEND_DOWN_LIGHTERS == false
		for (uint16_t i = 0; i < ADDITIONAL_LEDS; i++)
		{
			DownlightLeds[i] = CRGB::Black;
		}
	#endif

	for (uint8_t i = 0; i < NUM_DISPLAYS; i++)
	{
		animationManagers[i] = new Animator();
		Displays[i] = nullptr;
	}

	LEDBrightnessCurrent = 128;
	LEDBrightnessSmoothingStartPoint = 128;
	setGlobalBrightness(128, false);

	#if ENABLE_LIGHT_SENSOR == true
		lastSensorMeasurement = 0;
		takeBrightnessMeasurement();
	#endif
}

DisplayManager::~DisplayManager()
{
	if(instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

DisplayManager* DisplayManager::getInstance()
{
	if(instance == nullptr)
	{
		instance = new DisplayManager();
	}
	return instance;
}

void DisplayManager::setAllSegmentColors(CRGB color)
{
	for (uint16_t i = 0; i < NUM_SEGMENTS; i++)
	{
		allSegments[i]->updateColor(color);
	}
}

#if ENABLE_LIGHT_SENSOR == true

void DisplayManager::takeBrightnessMeasurement()
{
	if(lastSensorMeasurement + LIGHT_SENSOR_READ_DELAY < millis())
	{
		uint8_t lightSensorBrightnessNew = 0;
		lastSensorMeasurement = millis();
		lightSensorMeasurements.add(analogRead(LIGHT_SENSOR_PIN));
		if(lightSensorMeasurements.size() >= LIGHT_SENSOR_AVERAGE)
		{
			lightSensorMeasurements.shift();
		}
		if(lightSensorMeasurements.size() < LIGHT_SENSOR_MEDIAN_WIDTH)
		{
			//Calculate a normal average as long as the median width is not reached yet
			uint64_t BrightnessListSum = 0;
			for (uint16_t i = 0; i < lightSensorMeasurements.size(); i++)
			{
				BrightnessListSum += lightSensorMeasurements.get(i);
			}
			lightSensorBrightnessNew = map(BrightnessListSum / lightSensorMeasurements.size(), 0, 4095, 0, 255);
		}
		else
		{
			LinkedList<uint16_t> sortedMeasurements;
			//copy all the values to a new temporary list in order to sort them
			for (uint16_t i = 0; i < lightSensorMeasurements.size(); i++)
			{
				sortedMeasurements.add(lightSensorMeasurements.get(i));
			}
			sortedMeasurements.sort(SortFunction_SmallerThan);
			//calculate the average of the median window
			uint64_t BrightnessListSum = 0;
			uint16_t medianOffset = floor((sortedMeasurements.size() - LIGHT_SENSOR_MEDIAN_WIDTH) / 2);
			for (uint16_t i = 0; i < LIGHT_SENSOR_MEDIAN_WIDTH; i++)
			{
				BrightnessListSum += sortedMeasurements.get(i + medianOffset);
			}
			lightSensorBrightnessNew = map(BrightnessListSum / LIGHT_SENSOR_MEDIAN_WIDTH, LIGHT_SENSOR_MIN, LIGHT_SENSOR_MAX, LIGHT_SENSOR_SENSITIVITY, 0);
		}
		if(lightSensorBrightnessNew != lightSensorBrightness)
		{
			lightSensorBrightness = lightSensorBrightnessNew;
			setGlobalBrightness(currentLEDBrightness);
		}
		// Serial.printf("Sensor brightness: %d\n\r", lightSensorBrightness);
	}
}
#endif

void DisplayManager::setHourSegmentColors(CRGB color)
{
	Displays[LOWER_DIGIT_HOUR_DISPLAY]->updateColor(color);
	Displays[HIGHER_DIGIT_HOUR_DISPLAY]->updateColor(color);
}

void DisplayManager::setMinuteSegmentColors(CRGB color)
{
	Displays[LOWER_DIGIT_MINUTE_DISPLAY]->updateColor(color);
	Displays[HIGHER_DIGIT_MINUTE_DISPLAY]->updateColor(color);
}

void DisplayManager::InitSegments(uint16_t indexOfFirstLed, uint8_t ledsPerSegment, CRGB initialColor, uint8_t initBrightness)
{
	for (uint8_t i = 0; i < NUM_DISPLAYS; i++)
	{
		if(Displays[i] != nullptr)
		{
			free(Displays[i]);
			Displays[i] = nullptr;
		}
	}
	uint16_t currentLEDIndex = indexOfFirstLed;
	for (uint16_t i = 0; i < NUM_SEGMENTS; i++)
	{
		allSegments[i] = new Segment(leds, currentLEDIndex, ledsPerSegment, SegmentDirections[i], initialColor);
		if(Displays[diplayIndex[i]] == nullptr)
		{
			Displays[diplayIndex[i]] = new SevenSegment(SegmentDisplayModes[diplayIndex[i]], animationManagers[diplayIndex[i]]);
		}
		Displays[diplayIndex[i]]->add(allSegments[i], SegmentPositions[i]);
		animationManager.add(allSegments[i]);
		currentLEDIndex += ledsPerSegment;
	}
	//set the initial brightness to avoid jumps
	LEDBrightnessCurrent = initBrightness;
	LEDBrightnessSmoothingStartPoint = initBrightness;
	setGlobalBrightness(initBrightness, false);
	//All animations should be initialized by now. So now print the backlog of errors to not forget about it
	printAnimationInitErrors();
}

void DisplayManager::displayRaw(uint8_t Hour, uint8_t Minute)
{
	uint8_t firstHourDigit = Hour / 10;
	if(firstHourDigit == 0 && DISPLAY_SWITCH_OFF_AT_0 == true)
	{
		Displays[HIGHER_DIGIT_HOUR_DISPLAY]->off();
	}
	else
	{
		Displays[HIGHER_DIGIT_HOUR_DISPLAY]->DisplayNumber(firstHourDigit);
	}
	Displays[LOWER_DIGIT_HOUR_DISPLAY]->DisplayNumber(Hour - firstHourDigit * 10); //get the last digit

	uint8_t firstMinuteDigit = Minute / 10;
	if(firstMinuteDigit == 0 && DISPLAY_SWITCH_OFF_AT_0 == true)
	{
		Displays[HIGHER_DIGIT_MINUTE_DISPLAY]->off();
	}
	else
	{
		Displays[HIGHER_DIGIT_MINUTE_DISPLAY]->DisplayNumber(firstMinuteDigit);
	}
	Displays[LOWER_DIGIT_MINUTE_DISPLAY]->DisplayNumber(Minute - firstMinuteDigit * 10); //get the last digit
}

void DisplayManager::displayTime(uint8_t hours, uint8_t minutes)
{
	#if DISPLAY_0_AT_MIDNIGHT == true
	if(hours == 24)
	{
		hours = 0;
	}
	#endif
	#if USE_24_HOUR_FORMAT == false
		if(hours >= 13)
		{
			hours -= 12;
		}
	#endif
	displayRaw(hours, minutes);
}

void DisplayManager::displayTimer(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	if(hours != 0)
	{
		displayRaw(hours, minutes);
	}
	else
	{
		if(SegmentDisplayModes[HIGHER_DIGIT_HOUR_DISPLAY] == SevenSegment::ONLY_ONE)
		{
			if(minutes < 20)
			{
				displayRaw(minutes, seconds);
			}
			else
			{
				displayRaw(hours, minutes);
			}
		}
		else
		{
			displayRaw(minutes, seconds);
		}
	}
}

void DisplayManager::handle()
{
	animationManager.handle();
	for (uint8_t i = 0; i < NUM_DISPLAYS; i++)
	{
		animationManagers[i]->handle();
	}

	#if ENABLE_LIGHT_SENSOR == true
		takeBrightnessMeasurement();
	#endif
	uint64_t currentMillis = millis();
	if(LEDBrightnessCurrent != LEDBrightnessSetPoint && lastBrightnessChange + BRIGHTNESS_INTERPOLATION >= currentMillis)
	{
		double progress = easeInOutCubic(map_float(currentMillis - lastBrightnessChange, 0.0, BRIGHTNESS_INTERPOLATION, 0.0, 1.0));
		uint8_t smoothedBrightness = map_float(progress, 0, 1, LEDBrightnessSmoothingStartPoint, LEDBrightnessSetPoint);
		LEDBrightnessCurrent = smoothedBrightness;
		FastLED.setBrightness(LEDBrightnessCurrent);
	}
}

void DisplayManager::setInternalLEDColor(CRGB color)
{
	for (uint16_t i = 0; i < ADDITIONAL_LEDS; i++)
	{
		#if APPEND_DOWN_LIGHTERS == true
			leds[NUM_LEDS - ADDITIONAL_LEDS + i] = color;
		#else
			DownlightLeds[i] = color;
		#endif
	}
}

void DisplayManager::setDotLEDColor(CRGB color)
{
	#if DISPLAY_FOR_SEPERATION_DOT > -1
		Displays[DISPLAY_FOR_SEPERATION_DOT]->setColor(color);
	#endif
}

void DisplayManager::AnimationManagersTemporaryOverride(Animator* OverrideanimationManager)
{
	for (uint16_t i = 0; i < NUM_DISPLAYS; i++)
	{
		animationManagerTempBuffer[i] = Displays[i]->AnimationHandler;
		Displays[i]->AnimationHandler = OverrideanimationManager;
	}
}

void DisplayManager::restoreAnimationManagers()
{
	for (uint16_t i = 0; i < NUM_DISPLAYS; i++)
	{
		Displays[i]->AnimationHandler = animationManagerTempBuffer[i];
	}
}

void DisplayManager::showLoadingAnimation()
{
	// AnimationManagersTemporaryOverride(&animationManager);
	animationManager.PlayComplexAnimation(LoadingAnimation, (AnimatableObject**)allSegments, true);
}

void DisplayManager::stopLoadingAnimation()
{
	animationManager.ComplexAnimationStopLooping();
}

void DisplayManager::waitForLoadingAnimationFinish()
{
	animationManager.WaitForComplexAnimationCompletion();
	// restoreAnimationManagers();
}

void DisplayManager::turnAllSegmentsOff()
{
	for (uint16_t i = 0; i < NUM_SEGMENTS; i++)
	{
		allSegments[i]->off();
	}
}

void DisplayManager::turnAllLEDsOff()
{
	for (uint16_t i = 0; i < NUM_SEGMENTS; i++)
	{
		animationManager.stopAnimation(allSegments[i]);
	}
	turnAllSegmentsOff();
	setInternalLEDColor(CRGB::Black);
}

void DisplayManager::showProgress(uint32_t progress, uint32_t total)
{
	for (int i = 0; i < map(progress, 0, total, 0, NUM_LEDS_PER_SEGMENT * NUM_SEGMENTS_PROGRESS); i++)
	{
		leds[i] = OTA_UPDATE_COLOR;
	}
	animationManager.handle();
}

void DisplayManager::delay(uint32_t timeInMs)
{
	animationManager.delay(timeInMs);
}

void DisplayManager::setGlobalBrightness(uint8_t brightness, bool enableSmoothTransition)
{
	currentLEDBrightness = brightness;

	#if ENABLE_LIGHT_SENSOR == true
		LEDBrightnessSetPoint = constrain(brightness - lightSensorBrightness, 0, 255);
	#else
		LEDBrightnessSetPoint = brightness;
	#endif
	if(enableSmoothTransition)
	{
		LEDBrightnessSmoothingStartPoint = LEDBrightnessCurrent;
		lastBrightnessChange = millis();
	}
	else
	{
		LEDBrightnessSmoothingStartPoint = LEDBrightnessCurrent = LEDBrightnessSetPoint;
		FastLED.setBrightness(LEDBrightnessCurrent);
	}
}

void DisplayManager::flashSeperationDot(uint8_t numDots)
{
	#if DISPLAY_FOR_SEPERATION_DOT > -1
		Displays[DISPLAY_FOR_SEPERATION_DOT]->FlashMiddleDot(numDots);
	#endif
}

void DisplayManager::test()
{
	static uint8_t count = 0;
	static int8_t direction = 1;

	count += direction;
	if(count >= 9 || count == 0)
	{
		direction *= -1;
	}
	Displays[0]->DisplayNumber(count);

}

int16_t DisplayManager::getGlobalSegmentIndex(SegmentPositions_t segmentPosition, DisplayIDs Display)
{
	for (uint16_t i = 0; i < NUM_SEGMENTS; i++)
	{
		if(diplayIndex[i] == Display && SegmentPositions[i] == (1 << segmentPosition))
		{
			return i;
		}
	}
	if(!Serial.availableForWrite()) // during startup Serial is not availiable yet so put the errors to a list
	{
		if(SegmentIndexErrorList == nullptr)
		{
			SegmentIndexErrorList = new LinkedList<SegmentInstanceError>();
		}
		SegmentInstanceError newError = {.segmentPosition = segmentPosition, .Display = Display};
		SegmentIndexErrorList->add(newError);
	}
	else // once Serial was initialized print errors right away to not forget about them
	{
		Serial.printf("[W] Segment not valid; Position: %d; Display: %d\n\r", segmentPosition, Display);
	}
	return NO_SEGMENTS;
}

void DisplayManager::printAnimationInitErrors()
{
	if(SegmentIndexErrorList != nullptr)
	{
		while(SegmentIndexErrorList->size() > 0)
		{
			SegmentInstanceError currentError =	SegmentIndexErrorList->pop();
			Serial.printf("[W] Segment not valid; Position: %d; Display: %d\n\r", currentError.segmentPosition, currentError.Display);
		}
	}
}
