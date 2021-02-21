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

	enum Weekdays
	{
		NONE 		= 0x00,
		MONDAY 		= 0x01,
		TUESDAY 	= 0x02,
		WEDNESDAY 	= 0x04,
		THURSDAY 	= 0x08,
		FRIDAY 		= 0x10,
		SATURDAY 	= 0x20,
		SUNDAY 		= 0x40
	};

	typedef void (*TimerCallBack)(void);
private:
	TimeInfo currentTime;
	hw_timer_t* timer;
	uint32_t offlineTimeCounter;
	static TimeManager* TimeManagerSingelton;
	TimeInfo TimerInitialDuration;
	TimeInfo TimerDuration;
	TimeInfo AlarmTime;
	Weekdays AlarmActiveDays;
	TimerCallBack TimerTickCallback;
	TimerCallBack TimerDoneCallback;
	TimerCallBack AlarmTriggeredCallback;
	uint8_t currentWeekday;
	bool TimerModeActive;
	bool AlarmActive;
	bool AlarmTriggered;
	bool AlarmCleared;

	TimeManager();
	void advanceByOneSecondOffline();
	void TimerCountDOwnByOneSecond();
public:
	~TimeManager();

	/**
	 * @brief Get the singelton instance ot the Time Manager
	 */
	static TimeManager* getInstance();

	/**
	 * @brief Initialize the time manager and synchronize to ntp for the first time
	 * @pre prerequisite is that WIFI is already up and running
	 * @returns true if init was successful
	 */
	bool init();

	/**
	 * @brief Disable the timer and deactivate the interrupt
	 */
	void disableTimer();

	/**
	 * @brief Synchronize the time with the NTP server
	 */
	bool synchronize();

	/**
	 * @brief get the current time in a struct for displaying it on the clock
	 */
	TimeInfo getCurrentTime();

	/**
	 * @brief get the remaining time of the active timer
	 */
	TimeInfo getRemainingTimerTime();

	/**
	 * @brief get the current time as a string
	 */
	String getCurrentTimeString();

	/**
	 * @brief Set the duration for the Timer
	 */
	void setTimerDuration(TimeInfo newTimerDuration);

	/**
	 * @brief Start the timer
	 */
	void startTimer();

	/**
	 * @brief Stop the timer
	 */
	void stopTimer();

	bool isInBetween(TimeInfo time1, TimeInfo time2);

	TimeInfo addSeconds(TimeInfo time, uint16_t secondsToAdd);

	void setTimerTickCallback(TimerCallBack callback);

	void setTimerDoneCallback(TimerCallBack callback);

	void setAlarmTime(TimeInfo alarmTime, Weekdays activeDays);

	void setAlarmMode(bool active);

	void setAlarmCallback(TimerCallBack callback);

	bool isAlarmActive();

	void clearAlarm();

};

#endif