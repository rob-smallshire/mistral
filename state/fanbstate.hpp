/*
 * FanBState.hpp
 *
 *  Created on: 26 Dec 2013
 *      Author: rjs
 */

#ifndef FANBSTATE_HPP_
#define FANBSTATE_HPP_

#include <vent.hpp>

#include <state/singlefanstate.hpp>

class FanBState : public SingleFanState {
public:
    FanBState(Controller* ctxt);
    virtual ~FanBState();
    virtual State* transitionLower();
    virtual State* transitionHigher();
    virtual const char* name();
};

#endif /* FANBSTATE_HPP_ */
