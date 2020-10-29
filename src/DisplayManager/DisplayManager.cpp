#include "DisplayManager.h"

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

void DisplayManager::InitSegments(uint16_t indexOfFirstLed, uint8_t ledsPerSegment, CRGB initialColor)
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
		animationManagers[diplayIndex[i]]->add(allSegments[i]);
		currentLEDIndex += ledsPerSegment;
	}
}


//TODO: Fix this, it currently crashes
void DisplayManager::displayText(String text)
{
	if(text.length() > 0)
	{
		uint8_t startDisplay;
		if(Displays[0]->canDisplay(text[0]))
		{
			startDisplay = 0;
		} else if(Displays[1]->canDisplay(text[0]))
		{
			startDisplay = 1;
		}
		else
		{
			startDisplay = 2;
		}

		uint8_t textPos = 0;

		do
		{
			if(Displays[startDisplay]->canDisplay(text[textPos]))
			{
				Displays[startDisplay]->DisplayChar(text[textPos]);
			}
			else
			{
				Displays[++startDisplay]->DisplayChar(text[textPos]);
			}
			textPos++;
			startDisplay++;
		}
		while (textPos < text.length() && startDisplay < NUM_DISPLAYS);
	}
}

void DisplayManager::displayTime(uint8_t hours, uint8_t minutes)
{
	uint8_t firstHourDigit = hours / 10;
	if(firstHourDigit == 0 && DISPLAY_SWITCH_OFF_AT_0 == true)
	{
		Displays[HIGHER_DIGIT_HOUR_DISPLAY]->off();
	}
	else
	{
		Displays[HIGHER_DIGIT_HOUR_DISPLAY]->DisplayNumber(firstHourDigit);
	}
	Displays[LOWER_DIGIT_HOUR_DISPLAY]->DisplayNumber(hours - firstHourDigit * 10); //get the last digit

	uint8_t firstMinuteDigit = minutes / 10;
	if(firstMinuteDigit == 0 && DISPLAY_SWITCH_OFF_AT_0 == true)
	{
		Displays[HIGHER_DIGIT_MINUTE_DISPLAY]->off();
	}
	else
	{
		Displays[HIGHER_DIGIT_MINUTE_DISPLAY]->DisplayNumber(firstMinuteDigit);
	}
	Displays[LOWER_DIGIT_MINUTE_DISPLAY]->DisplayNumber(minutes - firstMinuteDigit * 10); //get the last digit
	// Serial.printf("%d%d:%d%d\n\r", firstHourDigit, hours - firstHourDigit * 10, firstMinuteDigit, minutes - firstMinuteDigit * 10);
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

void DisplayManager::showProgress(uint32_t progress, uint32_t total)
{
	for (int i = 0; i < (progress / (total / (NUM_LEDS_PER_SEGMENT * NUM_SEGMENTS_PROGRESS))); i++)
	{
		leds[i] = CRGB::Orange;
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

void DisplayManager::flashSeperationDot()
{
	#if DISPLAY_FOR_SEPERATION_DOT > -1
		Displays[DISPLAY_FOR_SEPERATION_DOT]->FlashMiddleDot();
	#endif
}