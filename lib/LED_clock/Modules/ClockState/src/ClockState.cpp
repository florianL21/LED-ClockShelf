#include "ClockState.h"

ClockState* ClockState::instance = nullptr;

ClockState::ClockState()
{
	MainState = CLOCK_MODE;
	clockBrightness = 128;
	alarmToggleCount = 0;
	nightModeBrightness = 0;
	numDots = NUM_SEPERATION_DOTS;

	lastUpdateMillis = millis();
	lastDotFlash = millis();
	currentAlarmSignalState = false;
	isinNightMode = false;
	timeM = TimeManager::getInstance();
	ShelfDisplays = DisplayManager::getInstance();
}

ClockState::~ClockState()
{
	instance = nullptr;
}

ClockState* ClockState::getInstance()
{
	if(instance == nullptr)
	{
		instance = new ClockState();
	}
	return instance;
}

void ClockState::switchMode(ClockStates newState)
{
    if(newState == ClockState::CLOCK_MODE)
    {
        alarmToggleCount = 0;
    }
    MainState = newState;
}

ClockState::ClockStates ClockState::getMode()
{
    return MainState;
}

void ClockState::handleStates()
{
	if(lastUpdateMillis + TIME_UPDATE_INTERVALL <= millis()) // update the display only in a certain intervall
	{
		lastUpdateMillis = millis();
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
				if(numDots > 0)
				{
					if(lastDotFlash + DOT_FLASH_INTERVALL <= millis())
					{
						lastDotFlash = millis();
						ShelfDisplays->flashSeperationDot(numDots);
					}
				}
			#endif
		break;
		case ClockState::TIMER_MODE:
			currentTime = timeM->getRemainingTimerTime();
			ShelfDisplays->displayTimer(currentTime.hours, currentTime.minutes, currentTime.seconds);
		break;
		case ClockState::TIMER_NOTIFICATION:
			if(currentAlarmSignalState == true)
			{
				ShelfDisplays->setGlobalBrightness(NOTIFICATION_BRIGHTNESS, false);
			}
			else
			{
				ShelfDisplays->setGlobalBrightness(0, false);
			}
			currentAlarmSignalState = !currentAlarmSignalState;
			alarmToggleCount++;
			#if TIMER_FLASH_TIME == true
				ShelfDisplays->displayTime(currentTime.hours, currentTime.minutes);
			#else
				ShelfDisplays->displayTime(0, 0);
			#endif
			if(alarmToggleCount >= TIMER_FLASH_COUNT)
			{
				ShelfDisplays->setGlobalBrightness(clockBrightness);
				ShelfDisplays->displayTime(currentTime.hours, currentTime.minutes);
				alarmToggleCount = 0;
				MainState = ClockState::CLOCK_MODE;
			}
		break;
		case ClockState::ALARM_NOTIFICATION:
			if(currentAlarmSignalState == true)
			{
				ShelfDisplays->setGlobalBrightness(NOTIFICATION_BRIGHTNESS, false);
			}
			else
			{
				ShelfDisplays->setGlobalBrightness(0, false);
			}
			currentAlarmSignalState = !currentAlarmSignalState;
			ShelfDisplays->displayTime(currentTime.hours, currentTime.minutes);
			if(!timeM->isAlarmActive())
			{
				ShelfDisplays->setGlobalBrightness(clockBrightness);
				MainState = ClockState::CLOCK_MODE;
			}
		break;
		default:
			break;
		}
	}
}
