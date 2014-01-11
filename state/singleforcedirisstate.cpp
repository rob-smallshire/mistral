/*
 * singleforcedirisstate.cpp
 *
 *  Created on: 5 Jan 2014
 *      Author: rjs
 */

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
    context().targetFanSpeed(active_, context().minimumFanSpeed());
    context().targetFanSpeed(dormant_, 0);
    context().targetAperture(dormant_, context().closedAperture());
    pid_.setOutput(context().actualAperture(active_));
}

void SingleForcedIrisState::exit(State* next_state) {
}

void SingleForcedIrisState::update(float setpoint_temperature, float cabinet_temperature) {
    pid_.setSetpoint(setpoint_temperature);
    int aperture = pid_.update(cabinet_temperature);
    context().targetAperture(active_, aperture);
}
