/*
 * fanbstate.cpp
 *
 *  Created on: 26 Dec 2013
 *      Author: rjs
 */

#include <controller.hpp>

#include <state/fanbstate.hpp>

FanBState::FanBState(Controller* ctxt) :
    SingleFanState(ctxt, VENT_B, VENT_A) {
}

FanBState::~FanBState() {
}

State* FanBState::transitionLower() {
    return &(context().forced_iris_b_state_);
}

State* FanBState::transitionHigher() {
    return &(context().both_fans_from_fan_b_state_);
}

const char * FanBState::name() {
    return "FanBState";
}
