/*
 * singleforcedirisstate.cpp
 *
 *  Created on: 5 Jan 2014
 *      Author: rjs
 */

#include <Arduino.h>

#include <controller.hpp>

#include <state/singleforcedirisstate.hpp>

SingleForcedIrisState::SingleForcedIrisState(Controller* ctxt, Vent active, Vent dormant) :
    State(ctxt),
    active_(active),
    dormant_(dormant),
    pid_(context().defaultSetpointCelsius(),
         context().defaultIrisAperture(),
         4.0, 1.0, 0.0,
         context().openedAperture(), context().closedAperture())
{
}

SingleForcedIrisState::~SingleForcedIrisState() {
}

bool SingleForcedIrisState::isUntenableLower() const {
    return ( pid_.output() == pid_.outputMaximum()) && (pid_.clampedDuration() > context().transitionDelay());
}

bool SingleForcedIrisState::isUntenableHigher() const {
    return ( pid_.output() == pid_.outputMinimum()) && (pid_.clampedDuration() > context().transitionDelay());
}

void SingleForcedIrisState::enter(State* previous_state) {
    pid_.setOutput(context().actualAperture(active_));
    context().runFan(active_);
    context().targetFanSpeed(active_, context().minimumFanSpeed());
    context().stopFan(dormant_);
    context().targetAperture(dormant_, context().closedAperture());
}

void SingleForcedIrisState::exit(State* next_state) {
}

void SingleForcedIrisState::update(float setpoint_temperature, float cabinet_temperature) {
    pid_.setSetpoint(setpoint_temperature);
    int aperture = pid_.update(cabinet_temperature);
    context().targetAperture(active_, aperture);
    Serial.print(name());
    Serial.print(" : Setting iris ");
    Serial.print(active_ == VENT_A ? 'A' : 'B');
    Serial.print(" to ");
    Serial.println(aperture);
}
