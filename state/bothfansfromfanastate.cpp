#include <controller.hpp>

#include <controller.hpp>

#include <state/bothfansfromfanastate.hpp>

BothFansFromFanAState::BothFansFromFanAState(Controller* ctxt) :
    BothFansState(ctxt) {
}

BothFansFromFanAState::~BothFansFromFanAState() {
}

State* BothFansFromFanAState::transitionHigher() {
    return this;
}

State* BothFansFromFanAState::transitionLower() {
    return &(context().fan_b_state_);
}
