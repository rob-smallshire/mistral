/*
 * bothfansfromfanbstate.cpp
 *
 *  Created on: 5 Jan 2014
 *      Author: rjs
 */


#include <controller.hpp>

#include <state/bothfansfromfanbstate.hpp>

BothFansFromFanBState::BothFansFromFanBState(Controller* ctxt) :
    BothFansState(ctxt) {
}

BothFansFromFanBState::~BothFansFromFanBState() {
}

State* BothFansFromFanBState::transitionHigher() {
    return this;
}

State* BothFansFromFanBState::transitionLower() {
    return &(context().fan_a_state_);
}

const char * BothFansFromFanBState::name() {
    return "BothFansFromFanBState";
}

