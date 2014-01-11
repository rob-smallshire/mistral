/*
 * singlefanstate.cpp
 *
 *  Created on: 26 Dec 2013
 *      Author: rjs
 */

#include <pid.hpp>
#include <controller.hpp>
#include <state/singlefanstate.hpp>

SingleFanState::SingleFanState(Controller* ctxt, Vent active, Vent dormant) :
    State(ctxt),
    active_(active),
    dormant_(dormant_),
    pid_(context().defaultSetpointCelsius(),
     context().defaultFanRpm(),
     -60.0, -2.0, -200,
     context().minimumFanSpeed(),
     context().maximumFanSpeed()){
}

bool SingleFanState::isUntenableHigher() const {
    return (pid_.output() == pid_.outputMaximum()) && (pid_.clampedDuration() > context().transitionDelay());
}

bool SingleFanState::isUntenableLower() const {
    return (pid_.output() == pid_.outputMinimum()) && (pid_.clampedDuration() > context().transitionDelay());
}

void SingleFanState::enter(State* previous_state) {
    pid_.setOutput(context().totalActualFanSpeed());
    context().targetFanSpeed(active_, pid_.output());
    context().targetFanSpeed(dormant_, 0);
    context().targetAperture(active_, context().openedAperture());
    context().targetAperture(dormant_, context().closedAperture());
}

void SingleFanState::exit(State* next_state) {
}

void SingleFanState::update(float setpoint_temperature, float cabinet_temperature) {
    pid_.setSetpoint(setpoint_temperature);
    float rpm = pid_.update(cabinet_temperature);
    context().targetFanSpeed(active_, rpm);
}

