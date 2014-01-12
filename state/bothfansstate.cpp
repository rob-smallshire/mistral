/*
 * both_fans_state.cpp
 *
 *  Created on: 21 Sep 2012
 *      Author: rjs
 */

#include <Arduino.h>

#include <state/bothfansstate.hpp>

#include <controller.hpp>

const int APERTURE_OPEN = 0;
const int APERTURE_CLOSED = 255;

const int DEFAULT_IRIS_APERTURE = APERTURE_OPEN;

const float DEFAULT_FAN_RPM = 1000;

const float ONE_MINUTE = 60.0; // seconds
const float TRANSITION_DELAY = ONE_MINUTE;

const float DEFAULT_SETPOINT_CELSIUS = 20.0;

const float T_CABINET_MIN = 10.0; // C
const float T_CABINET_MAX = 40.0; // C

BothFansState::BothFansState(Controller* ctxt) :
    State(ctxt),
	pid_(DEFAULT_SETPOINT_CELSIUS,
		 DEFAULT_FAN_RPM,
		 -60.0, -2.0, -200,
		 context().minimumFanSpeed(),
		 context().maximumFanSpeed())
{
}

BothFansState::~BothFansState() {
}

bool BothFansState::isUntenableHigher() const
{
	return false;
}

bool BothFansState::isUntenableLower() const
{
	return (pid_.output() == pid_.outputMinimum()) && (pid_.clampedDuration() > TRANSITION_DELAY);
}

void BothFansState::enter(State* previous_state)
{
    pid_.setOutput(context().totalActualFanSpeed() / 2.0f);
    context().runFan(VENT_A);
    context().runFan(VENT_B);
	context().targetFanSpeed(VENT_A, pid_.output());
	context().targetFanSpeed(VENT_B, pid_.output());
	context().targetAperture(VENT_A, context().openedAperture());
	context().targetAperture(VENT_B, context().openedAperture());
}

void BothFansState::exit(State* next_state)
{
}

void BothFansState::update(float setpoint_temperature, float cabinet_temperature)
{
	pid_.setSetpoint(setpoint_temperature);
	float rpm = pid_.update(cabinet_temperature);
	context().targetFanSpeed(VENT_A, rpm);
	context().targetFanSpeed(VENT_B, rpm);
	Serial.print(name());
	Serial.print(" : Setting both fans to ");
	Serial.println(rpm);
}

