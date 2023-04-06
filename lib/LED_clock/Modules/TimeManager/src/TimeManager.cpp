/**
 * \file TimeManager.cpp
 * \author Florian Laschober
 * \brief Implementation of the TimeManager class member functions
 */

#include "TimeManager.h"

TimeManager* TimeManager::TimeManagerSingelton = nullptr;

void IRAM_ATTR onTimer();

TimeManager::TimeManager()
{
	currentTime.hours = 0;
	currentTime.minutes = 0;
	currentTime.seconds = 0;
	offlineTimeCounter = 0;
	TimerDuration.hours = 0;
	TimerDuration.minutes = 0;
	TimerDuration.seconds = 0;
	TimerInitialDuration.hours = 0;
	TimerInitialDuration.minutes = 0;
	TimerInitialDuration.seconds = 0;
	TimerTickCallback = nullptr;
	TimerDoneCallback = nullptr;
	AlarmTriggeredCallback = nullptr;
	TimerModeActive = false;
	AlarmActiveDays = NONE;
	AlarmActive = false;
	AlarmTriggered = false;
	AlarmCleared = false;
	SynchronizeRequested = false;
}

TimeManager::~TimeManager()
{
	disableTimer();
	TimeManagerSingelton = nullptr;
}

TimeManager* TimeManager::getInstance()
{
	if(TimeManagerSingelton == nullptr)
	{
		TimeManagerSingelton = new TimeManager();
	}
	return TimeManagerSingelton;
}

bool TimeManager::init()
{
	#if TIME_MANAGER_DEMO_MODE == false
		configTzTime(TIMEZONE_INFO, NTP_SERVER);
	#endif
	// timer 0 divider 80 because 80Mhz and count up
	timer = timerBegin(0, 80, true);

	//Set the callback for the timer
	timerAttachInterrupt(timer, &onTimer, true);

	// Set alarm to call onTimer function every second 1 tick is 1us
	timerAlarmWrite(timer, 1000000, true);

	//synchronize the time for the first time then start the timer
	uint8_t retry = 0;
	bool fistSyncSuccess = synchronize();
	while(fistSyncSuccess != true && retry <= 20)
	{
		fistSyncSuccess = synchronize();
		retry++;
	}
	if(fistSyncSuccess == false)
	{
		return false;
	}
	timerAlarmEnable(timer);
	return true;
}

String TimeManager::getCurrentTimeString()
{
	char buf[6];
	TimeInfo currentTime = getCurrentTime();
	sprintf(buf, "%02d:%02d", currentTime.hours, currentTime.minutes);
	return String(buf);
}

TimeManager::TimeInfo TimeManager::getCurrentTime()
{
	return currentTime;
}

TimeManager::TimeInfo TimeManager::getRemainingTimerTime()
{
	return TimerDuration;
}

bool TimeManager::synchronize()
{
	struct tm timeinfo;
	if(!getLocalTime(&timeinfo))
	{
		Serial.println("[E]: TimeManager failed to get time from NTP server");
		return false;
	}
	currentTime.hours 	= timeinfo.tm_hour;
	currentTime.minutes = timeinfo.tm_min;
	currentTime.seconds = timeinfo.tm_sec;
	if(timeinfo.tm_wday == 0) // Sunday is not the first day in the week
	{
		currentWeekday 	= 6;
	}
	else
	{
		currentWeekday 	= timeinfo.tm_wday - 1;
	}
	return true;
}

void TimeManager::disableTimer()
{
	timerDetachInterrupt(timer);
	timerAlarmDisable(timer);
}

void TimeManager::advanceByOneSecondOffline()
{
	currentTime.seconds++;
	if(currentTime.seconds > 59)
	{
		currentTime.minutes++;
		currentTime.seconds = 0;
	}
	if(currentTime.minutes > 59)
	{
		currentTime.hours++;
		currentTime.minutes = 0;
	}
	if(currentTime.hours > 24)
	{
		currentTime.hours = 0;
	}
}

void TimeManager::TimerCountDOwnByOneSecond()
{
	TimerDuration.seconds--;
	if(TimerDuration.seconds > 59)
	{
		TimerDuration.minutes--;
		TimerDuration.seconds = 59;
	}
	if(TimerDuration.minutes > 59)
	{
		TimerDuration.hours--;
		TimerDuration.minutes = 59;
	}
	if(TimerDuration.hours > 24)
	{
		TimerDuration.hours = 24;
	}
}

void TimeManager::setTimerDuration(TimeInfo newTimerDuration)
{
	TimerInitialDuration = newTimerDuration;
	TimerDuration = newTimerDuration;
}

void TimeManager::startTimer()
{
	TimerModeActive = true;
}

void TimeManager::stopTimer()
{
	TimerModeActive = false;
}

bool TimeManager::isInBetween(TimeInfo timeStart, TimeInfo timeStop)
{
	uint32_t startTime = timeStart.hours * 3600 + timeStart.minutes * 60 + timeStart.seconds;
	uint32_t endTime = timeStop.hours * 3600 + timeStop.minutes * 60 + timeStop.seconds;
	uint32_t nowTime = currentTime.hours * 3600 + currentTime.minutes * 60 + currentTime.seconds;

	if(startTime > endTime)
	{
		if(nowTime >= startTime || nowTime <= endTime)
		{
			return true;
		}
	}
	else
	{
		if(nowTime >= startTime && nowTime <= endTime)
		{
			return true;
		}
	}
	return false;
}

TimeManager::TimeInfo TimeManager::addSeconds(TimeInfo time, uint16_t secondsToAdd)
{
	uint32_t Time = time.hours * 3600 + time.minutes * 60 + time.seconds + secondsToAdd;
	TimeInfo newTime;
	newTime.hours = Time / 3600;
	newTime.minutes = (Time - newTime.hours * 3600) / 60;
	newTime.seconds = Time - newTime.hours * 3600 - newTime.minutes * 60;
	return newTime;
}

void TimeManager::setTimerTickCallback(TimerCallBack callback)
{
	TimerTickCallback = callback;
}

void TimeManager::setTimerDoneCallback(TimerCallBack callback)
{
	TimerDoneCallback = callback;
}

void TimeManager::setAlarmTime(TimeInfo alarmTime, Weekdays activeDays)
{
	AlarmTime = alarmTime;
	AlarmActiveDays = activeDays;
	AlarmTriggered = false;
}

void TimeManager::setAlarmMode(bool active)
{
	AlarmActive = active;
	AlarmTriggered = false;
}

void TimeManager::setAlarmCallback(TimerCallBack callback)
{
	AlarmTriggeredCallback = callback;
}

bool TimeManager::isAlarmActive()
{
	return AlarmTriggered == true && AlarmCleared == false;
}

void TimeManager::clearAlarm()
{
	AlarmCleared = true;
}

void TimeManager::handle()
{
	if(SynchronizeRequested == true)
	{
		if(synchronize() == true)
		{
			offlineTimeCounter = 0;
		}
		else
		{
			advanceByOneSecondOffline();
		}
		SynchronizeRequested = false;
	}
}

void IRAM_ATTR onTimer()
{
	TimeManager* timeM = TimeManager::getInstance();
	// Time code, use this for normal operation
	#if TIME_MANAGER_DEMO_MODE == false
		if(timeM->offlineTimeCounter++ >= TIME_SYNC_INTERVAL && WiFi.status() == WL_CONNECTED)
		{
			timeM->SynchronizeRequested = true;
		}
		else
		{
			timeM->advanceByOneSecondOffline();
		}
		//handle timer
		if(timeM->TimerModeActive == true)
		{
			timeM->TimerCountDOwnByOneSecond();
			if(timeM->TimerTickCallback != nullptr)
			{
				timeM->TimerTickCallback();
			}
			if(timeM->TimerDuration.hours == 0 && timeM->TimerDuration.minutes == 0 && timeM->TimerDuration.seconds == 0)
			{
				if(timeM->TimerDoneCallback != nullptr)
				{
					timeM->TimerDoneCallback();
				}
				timeM->TimerDuration = timeM->TimerInitialDuration;
				timeM->TimerModeActive = false;
			}
		}
		// handle the alarm
		if(((1 << timeM->currentWeekday) & timeM->AlarmActiveDays) != 0)
		{
			if(timeM->isInBetween(timeM->AlarmTime, timeM->addSeconds(timeM->AlarmTime, ALARM_NOTIFICATION_PERIOD)))
			{
				if(timeM->AlarmTriggered == false)
				{
					timeM->AlarmTriggered = true;
					timeM->AlarmCleared = false;
					if(timeM->AlarmTriggeredCallback != nullptr)
					{
						timeM->AlarmTriggeredCallback();
					}
				}
			}
			else if(timeM->AlarmTriggered == true)
			{
				timeM->AlarmTriggered = false;
				timeM->AlarmCleared = false;
			}
		}
	#else
		//DEMO CODE: Useful for testing animations
		timeM->currentTime.minutes++;
		if(timeM->currentTime.minutes > 59)
		{
			timeM->currentTime.hours++;
			timeM->currentTime.minutes = 0;
		}
		if(timeM->currentTime.hours > 24)
		{
			timeM->currentTime.hours = 0;
		}
	#endif
}