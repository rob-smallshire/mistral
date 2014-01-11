/*
 * fanastate.cpp
 *
 *  Created on: 26 Dec 2013
 *      Author: rjs
 */

#include <controller.hpp>

#include <state/fanastate.hpp>

FanAState::FanAState(Controller* ctxt) :
    SingleFanState(ctxt, VENT_A, VENT_B) {
}

FanAState::~FanAState() {
}

State* FanAState::transitionLower() {
    return &(context().forced_iris_a_state_);
}

State* FanAState::transitionHigher() {
    return &(context().both_fans_from_fan_a_state_);
}
