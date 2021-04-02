/**
 * \file TimeManager.h
 * \author Florian Laschober
 * \brief Class deinition for the Time manager
 */

#ifndef __TIME_MANAGER_H_
#define __TIME_MANAGER_H_

#include <Arduino.h>
#include "time.h"
#include "Configuration.h"
#if RUN_WITHOUT_WIFI == false
	#include "WiFi.h"
#endif

/**
 * \brief The TimeManager is responsible for synchronizing the time to the NTP servers and keeping track of it
 * 		  offline if the WIFI connection was lost. Also manages alarms and timers
 */
class TimeManager
{
	friend void IRAM_ATTR onTimer();
public:
	/**
	 * \brief Saves a time in hours, minutes and seconds
	 */
	typedef struct
	{
		uint8_t hours;
		uint8_t minutes;
		uint8_t seconds;
	}TimeInfo;

	/**
	 * \brief Definition of weekdays ids
	 */
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

	/**
	 * \brief Timer callback function type which is called if a timer ticks or is elapsed or an alrm is triggered
	 */
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
	/**
	 * \brief Destroy the Time Manager object
	 */
	~TimeManager();

	/**
	 * \brief Get the singelton instance ot the Time Manager
	 */
	static TimeManager* getInstance();

	/**
	 * \brief Initialize the time manager and synchronize to ntp for the first time
	 * \pre prerequisite is that WIFI is already up and running
	 * \returns true if init was successful
	 */
	bool init();

	/**
	 * \brief Disable the timer and deactivate the interrupt
	 */
	void disableTimer();

	/**
	 * \brief Synchronize the time with the NTP server
	 */
	bool synchronize();

	/**
	 * \brief get the current time in a struct for displaying it on the clock
	 */
	TimeInfo getCurrentTime();

	/**
	 * \brief get the remaining time of the active timer
	 */
	TimeInfo getRemainingTimerTime();

	/**
	 * \brief get the current time as a string
	 */
	String getCurrentTimeString();

	/**
	 * \brief Set the duration for the Timer
	 */
	void setTimerDuration(TimeInfo newTimerDuration);

	/**
	 * \brief Start the timer
	 */
	void startTimer();

	/**
	 * \brief Stop the timer
	 */
	void stopTimer();

	/**
	 * \brief Check if the current time is in a given time period
	 *
	 * \param timeStart Start of the time period
	 * \param timeStop End of the time period
	 * \return true is returned if the current time is in between the two specified times
	 * \return false is returned if the current time is not in between the two specified times
	 */
	bool isInBetween(TimeInfo timeStart, TimeInfo timeStop);

	/**
	 * \brief Adds the specified amount of seconds to a given time
	 *
	 * \param time Base time element
	 * \param secondsToAdd Seconds that should be added to the base time
	 * \return TimeInfo Time struct with the new time where the seconds were already added
	 */
	TimeInfo addSeconds(TimeInfo time, uint16_t secondsToAdd);

	/**
	 * \brief Set the Timer Tick Callback function
	 *
	 * \param callback Function which shall be called every time a timer ticks (once every second)
	 */
	void setTimerTickCallback(TimerCallBack callback);

	/**
	 * \brief Set the Timer Done Callback function
	 *
	 * \param callback Function which shall be called once a timer has fired
	 */
	void setTimerDoneCallback(TimerCallBack callback);

	/**
	 * \brief Set the time at which an alarm shall be triggered
	 *
	 * \param alarmTime Time of the alarm
	 * \param activeDays Weekdays on which the alarm shall be triggered
	 */
	void setAlarmTime(TimeInfo alarmTime, Weekdays activeDays);

	/**
	 * \brief Set if the alarm is active or not
	 *
	 * \param active set to true if the alarm is supposed to be active, set to false to deactivate
	 */
	void setAlarmMode(bool active);

	/**
	 * \brief Set the Alarm Callback function which is called once an alarm fired
	 *
	 * \param callback Function to call if the alarm was triggered
	 */
	void setAlarmCallback(TimerCallBack callback);

	/**
	 * \brief check if the alarm is active
	 *
	 * \return true if the alarm is active
	 * \return false if the alarm is deactivated
	 */
	bool isAlarmActive();

	/**
	 * \brief Clear a currently triggered alarm without disabling it
	 */
	void clearAlarm();

};

#endif
