/*
 * forcedirisbstate.cpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#include <controller.hpp>

#include <state/forcedirisbstate.hpp>

ForcedIrisBState::ForcedIrisBState(Controller* ctxt) :
   SingleForcedIrisState(ctxt, VENT_B, VENT_A) {
}

ForcedIrisBState::~ForcedIrisBState() {
}

State* ForcedIrisBState::transitionHigher() {
    return &(context().fan_b_state_);
}

State* ForcedIrisBState::transitionLower() {
    return &(context().passive_iris_b_state_);
}

const char * ForcedIrisBState::name() {
    return "ForcedIrisBState";
}
