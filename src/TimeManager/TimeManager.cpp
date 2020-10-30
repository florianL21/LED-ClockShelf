#include "TimeManager.h"

TimeManager* TimeManager::TimeManagerSingelton = nullptr;

void IRAM_ATTR onTimer();

TimeManager::TimeManager()
{
	#if TIME_MANAGER_DEMO_MODE == false
		configTzTime(TIMEZONE_INFO, NTP_SERVER);
	#endif
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
	TimerModeActive = false;

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
		Serial.printf("[E]: TimeManager failed to synchronize for the first time with the NTP server. Retrying in %d seconds", TIME_SYNC_INTERVALL);
	}
	timerAlarmEnable(timer);
}

TimeManager::~TimeManager()
{
	disableTimer();
}

TimeManager* TimeManager::getInstance()
{
	if(TimeManagerSingelton == nullptr)
	{
		TimeManagerSingelton = new TimeManager();
	}
	return TimeManagerSingelton;
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
	if(TimerModeActive == false)
	{
		TimeInfo returnTime = currentTime;
		#if DISPLAY_0_AT_MIDNIGHT == true
		if(currentTime.hours == 24)
		{
			returnTime.hours = 0;
		}
		#endif
		#if USE_24_HOUR_FORMAT == false
			if(currentTime.hours >= 13)
			{
				returnTime.hours -= 12;
			}
		#endif
		return returnTime;
	}
	else
	{
		return TimerDuration;
	}
}

TimeManager::TimeInfo TimeManager::getRealCurrentTime()
{
	return currentTime;
}

bool TimeManager::synchronize()
{
	struct tm timeinfo;
	if(!getLocalTime(&timeinfo))
	{
		Serial.println("[E]: TimeManager failed to get time from NTP server");
		return false;
	}
	currentTime.hours = timeinfo.tm_hour;
	currentTime.minutes = timeinfo.tm_min;
	currentTime.seconds = timeinfo.tm_sec;
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

bool TimeManager::isInBetween(TimeInfo time1, TimeInfo time2)
{
	uint32_t startTime = time1.hours * 3600 + time1.minutes * 60 + time1.seconds;
	uint32_t endTime = time2.hours * 3600 + time2.minutes * 60 + time2.seconds;
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

void TimeManager::setTimerTickCallback(TimerCallBack callback)
{
	TimerTickCallback = callback;
}

void TimeManager::setTimerDoneCallback(TimerCallBack callback)
{
	TimerDoneCallback = callback;
}

void IRAM_ATTR onTimer()
{
	TimeManager* timeM = TimeManager::getInstance();
	// Time code, use this for normal operation
	#if TIME_MANAGER_DEMO_MODE == false
		if(timeM->offlineTimeCounter++ >= TIME_SYNC_INTERVALL && WiFi.status() == WL_CONNECTED)
		{
			if(timeM->synchronize() == true)
			{
				timeM->offlineTimeCounter = 0;
			}
			else
			{
				timeM->advanceByOneSecondOffline();
			}
			
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