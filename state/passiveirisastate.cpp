/*
 * passiveirisastate.cpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#include <controller.hpp>

#include <state/passiveirisastate.hpp>

PassiveIrisAState::PassiveIrisAState(Controller* ctxt) :
   SinglePassiveIrisState(ctxt, VENT_A, VENT_B) {
}

PassiveIrisAState::~PassiveIrisAState() {
}

State* PassiveIrisAState::transitionHigher() {
    return &(context().forced_iris_b_state_);
}

State* PassiveIrisAState::transitionLower() {
    return this;
}

const char * PassiveIrisAState::name() {
    return "PassiveIrisAState";
}
