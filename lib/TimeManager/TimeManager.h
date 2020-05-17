#ifndef __TIME_MANAGER_H_
#define __TIME_MANAGER_H_

#include <Arduino.h>
#include "time.h"

/**
 * @brief enable for wifi less operation or to demo all the animations
 */
#define TIME_MANAGER_DEMO_MODE	false

class TimeManager
{
public:
	typedef struct 
	{
		uint8_t hours;
		uint8_t minutes;
		uint8_t seconds;
	}TimeInfo;
private:
	uint64_t lastUpdate;
	TimeInfo currentTime;
	uint32_t updateInterv;
public:
	TimeManager(long gmtOffset_sec, int daylightOffset_sec, const char* server1, uint32_t updateIntervall);
	~TimeManager();

	/**
	 * @brief update the current time based on the internal clock, I am too lazy for finding out how timer interrupts work on the esp
	 */
	void update();

	/**
	 * @brief get the current time in a struct
	 */
	TimeInfo getCurrentTime();

	/**
	 * @brief get the current time as a string
	 */
	String getCurrentTimeString();
};

#endif