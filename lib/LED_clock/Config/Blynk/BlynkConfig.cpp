#include "BlynkConfig.h"

#if IS_BLYNK_ACTIVE == true

	/**
	 * @note if you use a different controller make sure to change the include here
	 */
	#include <BlynkSimpleEsp32.h>

	BlynkConfig* BlynkConfig::instance = nullptr;
	BlynkConfig* BlynkC = BlynkConfig::getInstance();
	ClockState* ClockS = ClockState::getInstance();
	TimeManager* TimeM = TimeManager::getInstance();

	BlynkConfig::BlynkConfig()
	{
		ShelfDisplays = DisplayManager::getInstance();
	}

	BlynkConfig::~BlynkConfig()
	{
		if(instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	BlynkConfig* BlynkConfig::getInstance()
	{
		if(instance == nullptr)
		{
			instance = new BlynkConfig();
		}
		return instance;
	}

	void BlynkConfig::stop()
	{
		vTaskDelete(BlynkLoop);
	}

	void BlynkLoopCode(void* pvParameters)
	{
		Serial.printf("Loop task running on core %d\n\r", xPortGetCoreID());
		BlynkConfig* blynkC = BlynkConfig::getInstance();
		for(;;)
		{
			#if IS_BLYNK_ACTIVE == true
				Blynk.run();
				if(blynkC->blynkUIUpdateRequired == true)
				{
					blynkC->blynkUIUpdateRequired = false;
					if(ClockS->MainState == ClockState::CLOCK_MODE)
					{
						Blynk.virtualWrite(BLYNK_CHANNEL_TIMER_START_BUTTON, 0);
					}
					else
					{
						// TimeManager::TimeInfo currentTimerValue = timeM->getCurrentTime();
						// int time = currentTimerValue.hours * 3600 + currentTimerValue.minutes * 60 + currentTimerValue.seconds;
						// Blynk.virtualWrite(BLYNK_CHANNEL_TIMER_START_BUTTON, time, 0);
					}
				}
			#endif
			delay(1); //needed to serve the wdg
		}
	}

	void BlynkConfig::setup()
	{
		Blynk.config(BLYNK_AUTH_TOKEN, BLYNK_SERVER, 80);
		Serial.println("Starting blynk on core 0...");
		//Setup the loop task on the second core
		xTaskCreatePinnedToCore(
		BlynkLoopCode,	// Task function.
		"BlynkLoop",	// name of task.
		10000,			// Stack size of task
		NULL,			// parameter of the task
		1,				// priority of the task
		&BlynkLoop,		// Task handle to keep track of created task
		0);				// pin task to core 0
	}

	void BlynkConfig::updateUI()
	{
		blynkUIUpdateRequired = true;
	}


	BLYNK_CONNECTED()
	{
		Blynk.syncVirtual(BLYNK_CHANNEL_BRIGHTNESS_SLIDER);
		#if BLYNK_SEPERATE_COLOR_CONTROL == true
			Blynk.syncVirtual(BLYNK_CHANNEL_LIGHT_GROUP_SELECTOR);
		#endif
		Blynk.syncVirtual(BLYNK_CHANNEL_CURRENT_COLOR_PICKER);
		Blynk.syncVirtual(BLYNK_CHANNEL_TIMER_TIME_INPUT);
		Blynk.syncVirtual(BLYNK_CHANNEL_HOUR_COLOR_SAVE);
		Blynk.syncVirtual(BLYNK_CHANNEL_MINUTE_COLOR_SAVE);
		Blynk.syncVirtual(BLYNK_CHANNEL_INTERNAL_COLOR_SAVE);
		Blynk.syncVirtual(BLYNK_CHANNEL_NIGHT_MODE_BRIGHTNESS);
		Blynk.syncVirtual(BLYNK_CHANNEL_NIGHT_MODE_TIME_INPUT);
		Blynk.virtualWrite(BLYNK_CHANNEL_TIMER_START_BUTTON, 0);
	}

	BLYNK_WRITE(BLYNK_CHANNEL_BRIGHTNESS_SLIDER)
	{
		ClockS->clockBrightness = param[0].asInt();
		BlynkC->ShelfDisplays->setGlobalBrightness(ClockS->clockBrightness);
	}

	#if BLYNK_SEPERATE_COLOR_CONTROL == true
		BLYNK_WRITE(BLYNK_CHANNEL_LIGHT_GROUP_SELECTOR)
		{
			switch (param.asInt())
			{
			case 1:
				BlynkC->ColorSelection = BlynkConfig::CHANGE_HOURS_COLOR;
				Blynk.virtualWrite(BLYNK_CHANNEL_CURRENT_COLOR_PICKER, BlynkC->HourColor.r, BlynkC->HourColor.g, BlynkC->HourColor.b);
				break;
			case 2:
				BlynkC->ColorSelection = BlynkConfig::CHANGE_MINUTES_COLOR;
				Blynk.virtualWrite(BLYNK_CHANNEL_CURRENT_COLOR_PICKER, BlynkC->MinuteColor.r, BlynkC->MinuteColor.g, BlynkC->MinuteColor.b);
				break;
			case 3:
				BlynkC->ColorSelection = BlynkConfig::CHANGE_INTERRIOR_COLOR;
				Blynk.virtualWrite(BLYNK_CHANNEL_CURRENT_COLOR_PICKER, BlynkC->InternalColor.r, BlynkC->InternalColor.g, BlynkC->InternalColor.b);
				break;
			}
		}
	#endif

	BLYNK_WRITE(BLYNK_CHANNEL_CURRENT_COLOR_PICKER)
	{
		CRGB currentColor;
		currentColor.r  = param[0].asInt();
		currentColor.g  = param[1].asInt();
		currentColor.b  = param[2].asInt();
		#if BLYNK_SEPERATE_COLOR_CONTROL == true
			switch (BlynkC->ColorSelection)
			{
			case BlynkConfig::CHANGE_HOURS_COLOR:
				BlynkC->ShelfDisplays->setHourSegmentColors(currentColor);
				Blynk.virtualWrite(BLYNK_CHANNEL_HOUR_COLOR_SAVE, currentColor.r, currentColor.g, currentColor.b);
				BlynkC->HourColor = currentColor;
				break;
			case BlynkConfig::CHANGE_MINUTES_COLOR:
				BlynkC->ShelfDisplays->setMinuteSegmentColors(currentColor);
				Blynk.virtualWrite(BLYNK_CHANNEL_MINUTE_COLOR_SAVE, currentColor.r, currentColor.g, currentColor.b);
				BlynkC->MinuteColor = currentColor;
				break;
			case BlynkConfig::CHANGE_INTERRIOR_COLOR:
				BlynkC->ShelfDisplays->setInternalLEDColor(currentColor);
				Blynk.virtualWrite(BLYNK_CHANNEL_INTERNAL_COLOR_SAVE, currentColor.r, currentColor.g, currentColor.b);
				BlynkC->InternalColor = currentColor;
				break;
			}
		#else
			BlynkC->ShelfDisplays->setAllSegmentColors(currentColor);
		#endif
	}

	BLYNK_WRITE(BLYNK_CHANNEL_HOUR_COLOR_SAVE)
	{
		CRGB SavedColor;
		SavedColor.r  = param[0].asInt();
		SavedColor.g  = param[1].asInt();
		SavedColor.b  = param[2].asInt();
		BlynkC->ShelfDisplays->setHourSegmentColors(SavedColor);
		BlynkC->HourColor = SavedColor;
	}

	BLYNK_WRITE(BLYNK_CHANNEL_MINUTE_COLOR_SAVE)
	{
		CRGB SavedColor;
		SavedColor.r  = param[0].asInt();
		SavedColor.g  = param[1].asInt();
		SavedColor.b  = param[2].asInt();
		BlynkC->ShelfDisplays->setMinuteSegmentColors(SavedColor);
		BlynkC->MinuteColor = SavedColor;
	}

	BLYNK_WRITE(BLYNK_CHANNEL_INTERNAL_COLOR_SAVE)
	{
		CRGB SavedColor;
		SavedColor.r  = param[0].asInt();
		SavedColor.g  = param[1].asInt();
		SavedColor.b  = param[2].asInt();
		BlynkC->ShelfDisplays->setInternalLEDColor(SavedColor);
		BlynkC->InternalColor = SavedColor;
	}

	BLYNK_WRITE(BLYNK_CHANNEL_TIMER_TIME_INPUT)
	{
		TimeManager::TimeInfo TimerDuration;
		TimeInputParam t(param);
		TimerDuration.hours = t.getStartHour();
		TimerDuration.minutes = t.getStartMinute();
		TimerDuration.seconds = t.getStartSecond();
		//Serial.printf("StartTime: %d:%d:%d\n\r", TimerDuration.hours, TimerDuration.minutes, TimerDuration.seconds);
		TimeM->setTimerDuration(TimerDuration);
	}

	BLYNK_WRITE(BLYNK_CHANNEL_TIMER_START_BUTTON)
	{
		if(param[0].asInt() == 1)
		{
			TimeM->startTimer();
			Serial.println("Timer Started");
			ClockS->MainState = ClockState::TIMER_MODE;
		}
		else
		{
			TimeM->stopTimer();
			Serial.println("Timer Stopped");
			Blynk.syncVirtual(BLYNK_CHANNEL_TIMER_TIME_INPUT);
			ClockS->alarmToggleCount = 0;
			BlynkC->ShelfDisplays->setGlobalBrightness(ClockS->clockBrightness);
			ClockS->MainState = ClockState::CLOCK_MODE;
		}
	}

	BLYNK_WRITE(BLYNK_CHANNEL_NIGHT_MODE_TIME_INPUT)
	{
		TimeInputParam t(param);
		ClockS->NightModeStartTime.hours = t.getStartHour();
		ClockS->NightModeStartTime.minutes = t.getStartMinute();
		ClockS->NightModeStartTime.seconds = t.getStartSecond();
		ClockS->NightModeStopTime.hours = t.getStopHour();
		ClockS->NightModeStopTime.minutes = t.getStopMinute();
		ClockS->NightModeStopTime.seconds = t.getStopSecond();
	}

	BLYNK_WRITE(BLYNK_CHANNEL_NIGHT_MODE_BRIGHTNESS)
	{
		ClockS->nightModeBrightness = param[0].asInt();
		if(TimeM->isInBetween(ClockS->NightModeStartTime, ClockS->NightModeStopTime))
		{
			BlynkC->ShelfDisplays->setGlobalBrightness(ClockS->nightModeBrightness);
		}
	}
#endif