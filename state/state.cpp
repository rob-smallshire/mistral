/*
 * state.cpp
 *
 *  Created on: 26 Dec 2013
 *      Author: rjs
 */

#include "state.hpp"

State::State(Controller* ctxt) :
    context_(ctxt) {
}


Controller& State::context() const {
    return *context_;
}
