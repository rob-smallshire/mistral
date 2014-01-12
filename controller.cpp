/*
 * Controller.cpp
 *
 *  Created on: 23 Sep 2012
 *      Author: rjs
 */

#include <Arduino.h>

#include <Max6651.h>

#include <vent.hpp>
#include <controller.hpp>
#include <iris.hpp>

const int FAN_ZERO = 0;

Controller::Controller(Max6651ClosedLoop* fan_a,
                       Max6651ClosedLoop* fan_b,
                       Iris* iris_a,
                       Iris* iris_b) :
    both_fans_from_fan_a_state_(this),
    both_fans_from_fan_b_state_(this),
    fan_a_state_(this),
    fan_b_state_(this),
    forced_iris_a_state_(this),
    forced_iris_b_state_(this),
    passive_iris_a_state_(this),
    passive_iris_b_state_(this),
    default_setpoint_celsius_(25.0),
    default_fan_rpm_(1000),
    default_iris_aperture_(openedAperture()),
    state_(&fan_a_state_),
    fans_(),
    irises_()
{
    fans_[0] = fan_a;
    fans_[1] = fan_b;

    irises_[0] = iris_a;
    irises_[1] = iris_b;
}

Controller::~Controller() {
}

void Controller::begin() {
    makeTransition(0, state_);
}

int Controller::minimumFanSpeed() {
    return max(fans_[VENT_A]->minimumSpeed(), fans_[VENT_B]->minimumSpeed());
}

int Controller::maximumFanSpeed() {
    return min(fans_[VENT_A]->minimumSpeed(), fans_[VENT_B]->minimumSpeed());
}

int Controller::totalActualFanSpeed() {

    int fan_a_speed = fans_[VENT_A]->actualSpeed(FAN_ZERO);
    int fan_b_speed = fans_[VENT_B]->actualSpeed(FAN_ZERO);
    return fan_a_speed + fan_b_speed;
}

void Controller::runFan(Vent vent) {
    fans_[vent]->run();
}

void Controller::stopFan(Vent vent) {
    fans_[vent]->stop();
}

void Controller::targetFanSpeed(Vent vent, int rpm) {
    fans_[vent]->targetSpeed(rpm);
}

int Controller::openedAperture() {
    return Iris::openedAperture();
}

int Controller::closedAperture() {
    return Iris::closedAperture();
}

void Controller::targetAperture(Vent vent, int aperture) {
    irises_[vent]->targetAperture(aperture);
}

int Controller::actualAperture(Vent vent) {
    return irises_[vent]->actualAperture();
}

float Controller::defaultSetpointCelsius() {
    return default_setpoint_celsius_;
}

int Controller::defaultFanRpm() {
    return default_fan_rpm_;
}

int Controller::defaultIrisAperture() {
    return default_iris_aperture_;
}

float Controller::transitionDelay() const {
    return 60.0; // seconds
}

float Controller::setpointTemperature(float inside_celsius, float outside_celsius) {
    return max(max(inside_celsius, outside_celsius) + 5.0, 30.0);
}

void Controller::update(float inside_celsius, float cabinet_celsius, float outside_celsius)
{
	float s_setpoint = setpointTemperature(inside_celsius, outside_celsius);
	Serial.print("Setpoint celsius = ");
	Serial.println(s_setpoint);
	state_->update(s_setpoint, cabinet_celsius);
	State* next_state = findNextState(state_);
	makeTransition(state_, next_state);
	state_ = next_state;
}


State* Controller::findNextState(State* state) const
{
	if (state->isUntenableHigher())
	{
		return state->transitionHigher();
	}
	if (state->isUntenableLower())
	{
		return state->transitionLower();
	}
	return state;
}


void Controller::makeTransition(State* previous_state, State* next_state) const
{
	if (next_state != previous_state)
	{
		if (previous_state != 0 && next_state != 0)
		{
			previous_state->exit(next_state);
			Serial.print("Transitioning from ");
			Serial.println(previous_state->name());
		}
		if (next_state != 0)
		{
			next_state->enter(previous_state);
	        Serial.print("Transitioning to ");
	        Serial.println(next_state->name());
		}
	}
}


