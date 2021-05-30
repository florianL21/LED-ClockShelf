/**
 * \file BlynkConfig.cpp
 * \author Florian Laschober
 * \brief Implementation of member function of #BlynkConfig and also all blynk hooks used to interact via the app
 */

#include "BlynkConfig.h"

/**
 * \note if you use a different controller make sure to change the include here
 */
#include <BlynkSimpleEsp32.h>

BlynkConfig* BlynkConfig::instance 	= nullptr;
BlynkConfig* BlynkC 				= nullptr;
ClockState* ClockS 					= nullptr;
TimeManager* TimeM 					= nullptr;

bool blynkReconfigure(ConfigManager* config);

/**
 * \brief Construct a new Blynk Config object. Also poulate all variables of the class with meaningful values
 *
 */
BlynkConfig::BlynkConfig()
{
	BlynkC 					= this;
	ClockS 					= ClockState::getInstance();
	TimeM 					= TimeManager::getInstance();
	ShelfDisplays 			= DisplayManager::getInstance();
	config 					= ConfigManager::getInstance();
	isClearAction 			= false;
	ColorSelection 			= CHANGE_HOURS_COLOR;
	blynkUIUpdateRequired 	= false;
	isTaskRunning 			= false;
	config->registerOnChangedCallback(ConfigManager::BLYNK_CONFIG_CHANGED, blynkReconfigure);
}

/**
 * \brief Destroy the Blynk Config object. Ensure proper deletion
 *
 */
BlynkConfig::~BlynkConfig()
{
	instance = nullptr;
}

/**
 * \brief Either instantiate a new BlynkConfig object by calling the private constructor and return it's address
 *        or it an instance of it already exists just return that.
 *
 * \return BlynkConfig* address of the new/already existing blynk config object
 */
BlynkConfig* BlynkConfig::getInstance()
{
	if(instance == nullptr)
	{
		instance = new BlynkConfig();
	}
	return instance;
}

/**
 * \brief Terminates the blynk task running on the second core
 *
 */
void BlynkConfig::stop()
{
	if(isTaskRunning == true)
	{
		vTaskDelete(BlynkLoop);
		isTaskRunning = false;
	}
}

/**
 * \brief Code for the second thread running on the second core of the ESP handling all the blynk code since
 *        all of it is coded in a blocking way and we don't want to influence the animation smoothness
 *
 */
void BlynkLoopCode(void* pvParameters)
{
	Serial.printf("Loop task running on core %d\n\r", xPortGetCoreID());
	BlynkConfig* blynkC = BlynkConfig::getInstance();
	for(;;)
	{
			Blynk.run();
			if(blynkC->blynkUIUpdateRequired == true)
			{
				blynkC->blynkUIUpdateRequired = false;
				if(ClockS->getMode() == ClockState::CLOCK_MODE)
				{
					Blynk.virtualWrite(BLYNK_CHANNEL_TIMER_START_BUTTON, 0);
				}
				else if(ClockS->getMode() == ClockState::ALARM_NOTIFICATION)
				{
					Blynk.setProperty(BLYNK_CHANNEL_ALARM_START_BUTTON, "onLabel", "Clear");
				}
				else
				{
					// TimeManager::TimeInfo currentTimerValue = timeM->getCurrentTime();
					// int time = currentTimerValue.hours * 3600 + currentTimerValue.minutes * 60 + currentTimerValue.seconds;
					// Blynk.virtualWrite(BLYNK_CHANNEL_TIMER_START_BUTTON, time, 0);
				}
			}
		delay(1); //needed to serve the wdg
	}
}


/**
 * \brief call Blynk.config and start the separate thread on the second core
 *
 */
void BlynkConfig::setup()
{
	if(config->getProperty<bool>(ConfigManager::BASE_CONFIG, BLYNK_ACTIVE_KEY) == true && isTaskRunning == false)
	{
		Blynk.config(config->getProperty<const char*>(ConfigManager::BASE_CONFIG, BLYNK_TOKEN_KEY),
					 config->getProperty<const char*>(ConfigManager::BASE_CONFIG, BLYNK_SERVER_KEY), 80);
		Serial.println("Starting blynk on core 0...");
		//Setup Blynk in another task because it is coded in a blocking way
		xTaskCreatePinnedToCore(
		BlynkLoopCode,	// Task function.
		"BlynkLoop",	// name of task.
		8192,			// Stack size of task
		NULL,			// parameter of the task
		1,				// priority of the task
		&BlynkLoop,		// Task handle to keep track of created task
		0);				// pin task to core 0
		isTaskRunning = true;
	}
}

void BlynkConfig::setEnabled(bool enabled)
{
	if(enabled == true)
	{
		setup();
	} else if(enabled == false)
	{
		stop();
	}
}

bool blynkReconfigure(ConfigManager* config)
{
	Blynk.config(config->getProperty<const char*>(ConfigManager::BASE_CONFIG, BLYNK_TOKEN_KEY),
				 config->getProperty<const char*>(ConfigManager::BASE_CONFIG, BLYNK_SERVER_KEY), 80);
	BlynkC->setEnabled(config->getProperty<bool>(ConfigManager::BASE_CONFIG, BLYNK_ACTIVE_KEY));
	return SYSTEM_RESTART_REQUIRED;
}

/**
 * \brief Notify the Blynk thread that a UI update is needed.
 *        What exactly needs to be updated will be figured out in the thread loop itself.
 *
 */
void BlynkConfig::updateUI()
{
	blynkUIUpdateRequired = true;
}

/**
 * \brief Sync all channels as soon as blynk connects to the server
 *        Setup default UI states
 *
 */
BLYNK_CONNECTED()
{
	Blynk.syncVirtual(BLYNK_CHANNEL_BRIGHTNESS_SLIDER);
	Blynk.syncVirtual(BLYNK_CHANNEL_LIGHT_GROUP_SELECTOR);
	Blynk.syncVirtual(BLYNK_CHANNEL_CURRENT_COLOR_PICKER);
	Blynk.syncVirtual(BLYNK_CHANNEL_TIMER_TIME_INPUT);
	Blynk.syncVirtual(BLYNK_CHANNEL_HOUR_COLOR_SAVE);
	Blynk.syncVirtual(BLYNK_CHANNEL_MINUTE_COLOR_SAVE);
	Blynk.syncVirtual(BLYNK_CHANNEL_INTERNAL_COLOR_SAVE);
	Blynk.syncVirtual(BLYNK_CHANNEL_DOT_COLOR_SAVE);
	Blynk.syncVirtual(BLYNK_CHANNEL_NIGHT_MODE_BRIGHTNESS);
	Blynk.syncVirtual(BLYNK_CHANNEL_NIGHT_MODE_TIME_INPUT);
	Blynk.syncVirtual(BLYNK_CHANNEL_NUM_SEPERATION_DOTS);
	Blynk.syncVirtual(BLYNK_CHANNEL_ALARM_START_BUTTON);
	Blynk.syncVirtual(BLYNK_CHANNEL_ALARM_TIME_INPUT);
	Blynk.virtualWrite(BLYNK_CHANNEL_TIMER_START_BUTTON, 0);
}

/**
 * \brief Handle a brigness change by the user through the blynk app
 *
 */
BLYNK_WRITE(BLYNK_CHANNEL_BRIGHTNESS_SLIDER)
{
	ClockS->clockBrightness = param[0].asInt();
	BlynkC->ShelfDisplays->setGlobalBrightness(ClockS->clockBrightness);
}

/**
 * \brief Handle the change of the light group selector by the user through the blynk app
 *
 */
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
	case 4:
		BlynkC->ColorSelection = BlynkConfig::CHANGE_DOT_COLOR;
		Blynk.virtualWrite(BLYNK_CHANNEL_CURRENT_COLOR_PICKER, BlynkC->DotColor.r, BlynkC->DotColor.g, BlynkC->DotColor.b);
		break;
	}
}

/**
 * \brief Handle a color change for the currently selected light group by the user through the blynk app
 *
 */
BLYNK_WRITE(BLYNK_CHANNEL_CURRENT_COLOR_PICKER)
{
	CRGB currentColor;
	currentColor.r  = param[0].asInt();
	currentColor.g  = param[1].asInt();
	currentColor.b  = param[2].asInt();
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
	case BlynkConfig::CHANGE_DOT_COLOR:
		BlynkC->ShelfDisplays->setDotLEDColor(currentColor);
		Blynk.virtualWrite(BLYNK_CHANNEL_DOT_COLOR_SAVE, currentColor.r, currentColor.g, currentColor.b);
		BlynkC->DotColor = currentColor;
		break;
	}
}

/**
 * \brief Use an unused virtual channel to permanently store the color for the hours light group to be able
 *        to restore it's state after a reset.
 *
 */
BLYNK_WRITE(BLYNK_CHANNEL_HOUR_COLOR_SAVE)
{
	CRGB SavedColor;
	SavedColor.r  = param[0].asInt();
	SavedColor.g  = param[1].asInt();
	SavedColor.b  = param[2].asInt();
	BlynkC->ShelfDisplays->setHourSegmentColors(SavedColor);
	BlynkC->HourColor = SavedColor;
}

/**
 * \brief Use an unused virtual channel to permanently store the color for the minutes light group to be able
 *        to restore it's state after a reset.
 *
 */
BLYNK_WRITE(BLYNK_CHANNEL_MINUTE_COLOR_SAVE)
{
	CRGB SavedColor;
	SavedColor.r  = param[0].asInt();
	SavedColor.g  = param[1].asInt();
	SavedColor.b  = param[2].asInt();
	BlynkC->ShelfDisplays->setMinuteSegmentColors(SavedColor);
	BlynkC->MinuteColor = SavedColor;
}

/**
 * \brief Use an unused virtual channel to permanently store the color for the internal light group to be able
 *        to restore it's state after a reset.
 *
 */
BLYNK_WRITE(BLYNK_CHANNEL_INTERNAL_COLOR_SAVE)
{
	CRGB SavedColor;
	SavedColor.r  = param[0].asInt();
	SavedColor.g  = param[1].asInt();
	SavedColor.b  = param[2].asInt();
	BlynkC->ShelfDisplays->setInternalLEDColor(SavedColor);
	BlynkC->InternalColor = SavedColor;
}

/**
 * \brief Use an unused virtual channel to permanently store the color for the dot light group to be able
 *        to restore it's state after a reset.
 *
 */
BLYNK_WRITE(BLYNK_CHANNEL_DOT_COLOR_SAVE)
{
	CRGB SavedColor;
	SavedColor.r  = param[0].asInt();
	SavedColor.g  = param[1].asInt();
	SavedColor.b  = param[2].asInt();
	BlynkC->ShelfDisplays->setDotLEDColor(SavedColor);
	BlynkC->DotColor = SavedColor;
}

/**
 * \brief Handle a timer duration change by the user through the blynk app
 *
 */
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

/**
 * \brief Handle the start of the timer by the user through the blynk app
 *
 */
BLYNK_WRITE(BLYNK_CHANNEL_TIMER_START_BUTTON)
{
	if(param[0].asInt() == 1)
	{
		TimeM->startTimer();
		Serial.println("Timer Started");
		ClockS->switchMode(ClockState::TIMER_MODE);
	}
	else
	{
		TimeM->stopTimer();
		Serial.println("Timer Stopped");
		Blynk.syncVirtual(BLYNK_CHANNEL_TIMER_TIME_INPUT);
		BlynkC->ShelfDisplays->setGlobalBrightness(ClockS->clockBrightness);
		ClockS->switchMode(ClockState::CLOCK_MODE);
	}
}

/**
 * \brief Handle the nightime window setting change by the user through the blynk app
 *
 */
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

/**
 * \brief Handle the nighttime brightness setting change by the user through the blynk app
 *
 */
BLYNK_WRITE(BLYNK_CHANNEL_NIGHT_MODE_BRIGHTNESS)
{
	ClockS->nightModeBrightness = param[0].asInt();
	if(TimeM->isInBetween(ClockS->NightModeStartTime, ClockS->NightModeStopTime))
	{
		BlynkC->ShelfDisplays->setGlobalBrightness(ClockS->nightModeBrightness);
	}
}

/**
 * \brief Handle the change of the dots display setting by the user through the blynk app
 *
 */
BLYNK_WRITE(BLYNK_CHANNEL_NUM_SEPERATION_DOTS)
{
	ClockS->numDots = param[0].asInt() - 1;
}

/**
 * \brief Handle an alarm time change by the user through the blynk app
 *
 */
BLYNK_WRITE(BLYNK_CHANNEL_ALARM_TIME_INPUT)
{
	TimeInputParam t(param);
	TimeManager::TimeInfo AlarmTime
	{
		.hours 		= (uint8_t)t.getStartHour(),
		.minutes 	= (uint8_t)t.getStartMinute(),
		.seconds 	= (uint8_t)t.getStartSecond()
	};
	uint8_t activeDays = 0x00;
	for (uint8_t i = 0; i < 7; i++)
	{
		if (t.isWeekdaySelected(i + 1)) // 1 to 7 for every weekday in blynk config
		{
			activeDays |= (1 << i);
		}
	}
	TimeM->setAlarmTime(AlarmTime, (TimeManager::Weekdays)activeDays);
}

/**
 * \brief Handle the activation/deactivation/clearing of the alarm function by the user through the blynk app
 *
 */
BLYNK_WRITE(BLYNK_CHANNEL_ALARM_START_BUTTON)
{
	if(ClockS->getMode() == ClockState::ALARM_NOTIFICATION)
	{
		Blynk.setProperty(BLYNK_CHANNEL_ALARM_START_BUTTON, "onLabel", "Deactivate");
		TimeM->clearAlarm();
		Blynk.virtualWrite(BLYNK_CHANNEL_ALARM_START_BUTTON, 1);
		BlynkC->isClearAction = true;
	}
	else if(BlynkC->isClearAction == true)
	{
		BlynkC->isClearAction = false;
	}
	else
	{
		TimeM->setAlarmMode(param[0].asInt() == 1);
	}
}
