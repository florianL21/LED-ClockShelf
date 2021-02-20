#ifndef _CLOCK_STATE_H_
#define _CLOCK_STATE_H_

#include "Configuration.h"
#include <Arduino.h>
#include "TimeManager.h"
#include "DisplayManager.h"

class ClockState
{
public:
	enum ClockStates {CLOCK_MODE, TIMER_MODE, ALARM_MODE};
	ClockStates MainState;
	uint8_t clockBrightness;
	uint16_t alarmToggleCount;
	TimeManager::TimeInfo NightModeStartTime;
	TimeManager::TimeInfo NightModeStopTime;
	uint8_t nightModeBrightness;

	unsigned long lastMillis;
	bool currentAlarmSignalState;
	bool isinNightMode;
	uint8_t numDots;

	~ClockState();
	static ClockState* getInstance();
	void handleStates();
private:
	TimeManager* timeM;
	DisplayManager* ShelfDisplays;
	static ClockState* instance;
	unsigned long lastDotFlash;

	ClockState();
};

#endif