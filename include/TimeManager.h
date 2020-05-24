#ifndef __TIME_MANAGER_H_
#define __TIME_MANAGER_H_

#include <Arduino.h>
#include "time.h"
#include "Configuration.h"
#if RUN_WITHOUT_WIFI == false
	#include "WiFi.h"
#endif

class TimeManager
{
	friend void IRAM_ATTR onTimer();
public:
	typedef struct 
	{
		uint8_t hours;
		uint8_t minutes;
		uint8_t seconds;
	}TimeInfo;
private:
	TimeInfo currentTime;
	hw_timer_t* timer;
	uint32_t offlineTimeCounter;
	static TimeManager* TimeManagerSingelton;

	TimeManager();
	void advanceByOneSecondOffline();
public:
	~TimeManager();

	static TimeManager* getInstance();

	/**
	 * @brief Synchronize the time with the NTP server
	 */
	bool synchronize();

	/**
	 * @brief get the current time in a struct
	 */
	TimeInfo getCurrentTime();

	/**
	 * @brief get the current time as a string
	 */
	String getCurrentTimeString();

	void disableTimer();
};

#endif