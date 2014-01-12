/*
 * forcedirisastate.cpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#include <controller.hpp>

#include <state/forcedirisastate.hpp>

ForcedIrisAState::ForcedIrisAState(Controller* ctxt) :
   SingleForcedIrisState(ctxt, VENT_A, VENT_B) {
}

ForcedIrisAState::~ForcedIrisAState() {
}

State* ForcedIrisAState::transitionHigher() {
    return &(context().fan_a_state_);
}

State* ForcedIrisAState::transitionLower() {
    return &(context().passive_iris_a_state_);
}

const char * ForcedIrisAState::name() {
    return "ForcedIrisAState";
}
