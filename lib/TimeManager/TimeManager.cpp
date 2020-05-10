#include "TimeManager.h"

TimeManager::TimeManager(long gmtOffset_sec, int daylightOffset_sec, const char* server1, uint32_t updateIntervall)
{
	configTime(gmtOffset_sec, daylightOffset_sec, server1);
	lastUpdate = millis();
	updateInterv = updateIntervall;
	currentTime.hours = 0;
	currentTime.minutes = 0;
	currentTime.seconds = 0;
}

TimeManager::~TimeManager()
{
}

String TimeManager::getCurrentTimeString()
{
	char buf[6];
	TimeInfo currentTime = getCurrentTime();
	sprintf(buf, "%02d:%02d", currentTime.hours, currentTime.seconds);
	return String(buf);
}

TimeManager::TimeInfo TimeManager::getCurrentTime()
{
	return currentTime;
}

//TODO: Fix this hack
void TimeManager::update()
{
	if(lastUpdate + updateInterv < millis())
	{
		lastUpdate = millis();
		// Time code, use this for normal operation
		struct tm timeinfo;
		if(!getLocalTime(&timeinfo))
		{
			Serial.println("Failed to obtain time");
			currentTime.hours = 0;
			currentTime.minutes = 0;
			currentTime.seconds = 0;
			return;
		}
		currentTime.hours = timeinfo.tm_hour;
		currentTime.minutes = timeinfo.tm_min;
		currentTime.seconds = timeinfo.tm_sec;

		//DEMO CODE: Useful for testing animations
		//Tipp: if you have a bad internet connection disable Blynk functionallity as this will mess with the timing on fast updating digits
		/*
		currentTime.minutes++;
		if(currentTime.minutes > 59)
		{
			currentTime.hours++;
			currentTime.minutes = 0;
		}
		if(currentTime.hours > 24)
		{
			currentTime.hours = 0;
		}
		*/
	}
}