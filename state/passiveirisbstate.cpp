/*
 * passiveirisastate.cpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#include <controller.hpp>

#include <state/passiveirisbstate.hpp>

PassiveIrisBState::PassiveIrisBState(Controller* ctxt) :
   SinglePassiveIrisState(ctxt, VENT_B, VENT_A) {
}

State* PassiveIrisBState::transitionHigher() {
    return &(context().forced_iris_a_state_);
}

State* PassiveIrisBState::transitionLower() {
    return this;
}
