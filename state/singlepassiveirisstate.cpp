/*
 * singlepassiveirisstate.cpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#ifndef SINGLEPASSIVEIRISSTATE_CPP_
#define SINGLEPASSIVEIRISSTATE_CPP_

#include <controller.hpp>

#include <state/singlepassiveirisstate.hpp>

SinglePassiveIrisState::SinglePassiveIrisState(Controller* ctxt, Vent active, Vent dormant) :
    State(ctxt),
    active_(active_),
    dormant_(dormant_),
    pid_(context().defaultSetpointCelsius(),
         context().defaultIrisAperture(),
         4.0, 1.0, 0.0,
         context().openedAperture(), context().closedAperture()) {
}

SinglePassiveIrisState::~SinglePassiveIrisState() {
}

void SinglePassiveIrisState::enter(State* previous_state) {
    context().targetFanSpeed(active_, 0);
    context().targetFanSpeed(dormant_, 0);
    context().targetAperture(dormant_, context().closedAperture());
    pid_.setOutput(context().actualAperture(active_));
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
}

#endif /* SINGLEPASSIVEIRISSTATE_CPP_ */
