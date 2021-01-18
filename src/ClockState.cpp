#include "ClockState.h"

ClockState* ClockState::instance = nullptr;

ClockState::ClockState()
{
	MainState = CLOCK_MODE;
	clockBrightness = 128;
	alarmToggleCount = 0;
	nightModeBrightness = 0;

	lastMillis = millis();
	currentAlarmSignalState = false;
	isinNightMode = false;
	timeM = TimeManager::getInstance();
	ShelfDisplays = DisplayManager::getInstance();
}

ClockState::~ClockState()
{
	if(instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

ClockState* ClockState::getInstance()
{
	if(instance == nullptr)
	{
		instance = new ClockState();
	}
	return instance;
}

void ClockState::handleStates()
{
	if(lastMillis + TIME_UPDATE_INTERVALL <= millis()) // update the display only in a certain intervall
	{
		lastMillis = millis();
		TimeManager::TimeInfo currentTime;
		currentTime = timeM->getCurrentTime();
		switch (MainState)
		{
		case ClockState::CLOCK_MODE:
			if(timeM->isInBetween(NightModeStartTime, NightModeStopTime))
			{
				if(isinNightMode == false)
				{
					isinNightMode = true;
					ShelfDisplays->setGlobalBrightness(nightModeBrightness);
				}
			}
			else
			{
				if(isinNightMode == true)
				{
					isinNightMode = false;
					ShelfDisplays->setGlobalBrightness(clockBrightness);
				}
			}
			ShelfDisplays->displayTime(currentTime.hours, currentTime.minutes);
			#if DISPLAY_FOR_SEPERATION_DOT > -1
				if(flashMiddleDot == true)
				{
					ShelfDisplays->flashSeperationDot(); //this will always flash at half the update speed
				}
				flashMiddleDot = !flashMiddleDot;
			#endif
		break;
		case ClockState::TIMER_MODE:
			//timers only support up to one hour durations, but really only 19 minutes if the first segment can only display a one
			ShelfDisplays->displayTime(currentTime.minutes, currentTime.seconds);
		break;
		case ClockState::ALARM_MODE:
			if(currentAlarmSignalState == true)
			{
				ShelfDisplays->setGlobalBrightness(255, false);
			}
			else
			{
				ShelfDisplays->setGlobalBrightness(0, false);
			}
			currentAlarmSignalState = !currentAlarmSignalState;
			alarmToggleCount++;
			#if ALARM_FLASH_TIME == true
				ShelfDisplays->displayTime(currentTime.hours, currentTime.minutes);
			#else
				ShelfDisplays->displayTime(0, 0);
			#endif
			if(alarmToggleCount >= ALARM_FLASH_COUNT)
			{
				ShelfDisplays->setGlobalBrightness(clockBrightness);
				ShelfDisplays->displayTime(currentTime.hours, currentTime.minutes);
				alarmToggleCount = 0;
				MainState = ClockState::CLOCK_MODE;
			}
		break;
		default:
			break;
		}
	}
	ShelfDisplays->handle();
}