/**
 * \file ClockState.h
 * \author Florian Laschober
 * \brief Header for class definition of the #ClockState which is used to keep track of values between modules
 */

#ifndef _CLOCK_STATE_H_
#define _CLOCK_STATE_H_

#include "Configuration.h"
#include <Arduino.h>
#include "TimeManager.h"
#include "DisplayManager.h"

/**
 * \brief The clockState is responsible to hold all the data that needs to be communicated between components.
 *        It can be imagined as kind of like an "object oriented global variable"
 */
class ClockState
{
public:
    /**
     * \brief Avaliable clock modes each with a different behaviour
     */
	enum ClockStates {CLOCK_MODE, TIMER_MODE, TIMER_NOTIFICATION, ALARM_NOTIFICATION};
private:
	TimeManager* timeM;
	DisplayManager* ShelfDisplays;
	static ClockState* instance;
	unsigned long lastDotFlash;
    ClockStates MainState;
    uint16_t alarmToggleCount;
    unsigned long lastUpdateMillis;
    bool currentAlarmSignalState;
    bool isinNightMode;

	ClockState();
public:

    /**
     * \brief Base brightness of the clock. The actual brightness can still change if a light sensor is used
     */
	uint8_t clockBrightness;

    /**
     * \brief Brightness of the clock driing nighttime hours define by #ClockState::NightModeStartTime and
     *        #ClockState::NightModeStopTime
     */
    uint8_t nightModeBrightness;

    /**
     * \brief Any time after will be considered nighttime as long as it is still lower than #ClockState::NightModeStopTime
     */
	TimeManager::TimeInfo NightModeStartTime;

    /**
     * \brief Any time before will be considered nighttime as long as it is still higher than #ClockState::NightModeStartTime
     */
	TimeManager::TimeInfo NightModeStopTime;

    /**
     * \brief defines the number of dots.
     * \range 0 -> no dot; 1 -> one dot; 2 -> two dots; other-> one dot
     */
	uint8_t numDots;

    /**
     * \brief Get the instance of the Clock object or create it if it was not yet instantiated.
     *
     * \return ClockState* returns the address to the ClockState object
     */
    static ClockState* getInstance();

    /**
     * \brief Destroys the ClockState object and cause #ClockState::getInstance to create a new object the next time it is called
     */
	~ClockState();

    /**
     * \brief Switch the current mode of the clock
     */
    void switchMode(ClockStates newState);

    /**
     * \brief Returns the current mode of the clock
     */
    ClockStates getMode();

    /**
     * \brief Has to be called periodically to update the screen and process state transitions within the state machine.
     *
     */
	void handleStates();
};

#endif
