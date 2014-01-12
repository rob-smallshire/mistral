/*
 * singlepassiveirisstate.cpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#ifndef SINGLEPASSIVEIRISSTATE_CPP_
#define SINGLEPASSIVEIRISSTATE_CPP_

#include <Arduino.h>

#include <controller.hpp>

#include <state/singlepassiveirisstate.hpp>

SinglePassiveIrisState::SinglePassiveIrisState(Controller* ctxt, Vent active, Vent dormant) :
    State(ctxt),
    active_(active),
    dormant_(dormant),
    pid_(context().defaultSetpointCelsius(),
         context().defaultIrisAperture(),
         4.0, 1.0, 0.0,
         context().openedAperture(), context().closedAperture()) {
}

SinglePassiveIrisState::~SinglePassiveIrisState() {
}

void SinglePassiveIrisState::enter(State* previous_state) {
    pid_.setOutput(context().actualAperture(active_));
    context().stopFan(active_);
    context().stopFan(dormant_);
    context().targetAperture(dormant_, context().closedAperture());
}

void SinglePassiveIrisState::exit(State* previous_state) {
}

bool SinglePassiveIrisState::isUntenableLower() const {
    return ( pid_.output() == pid_.outputMaximum()) && (pid_.clampedDuration() > context().transitionDelay());
}

bool SinglePassiveIrisState::isUntenableHigher() const {
    return ( pid_.output() == pid_.outputMinimum()) && (pid_.clampedDuration() > context().transitionDelay());
}

void SinglePassiveIrisState::update(float setpoint_temperature, float cabinet_temperature) {
    pid_.setSetpoint(setpoint_temperature);
    int aperture = pid_.update(cabinet_temperature);
    context().targetAperture(active_, aperture);
    Serial.print(name());
    Serial.print(" : Setting iris ");
    Serial.print(active_ == VENT_A ? 'A' : 'B');
    Serial.print(" to ");
    Serial.println(aperture);
}

#endif /* SINGLEPASSIVEIRISSTATE_CPP_ */
