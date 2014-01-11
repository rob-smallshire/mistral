/*
 * FanAState.hpp
 *
 *  Created on: 26 Dec 2013
 *      Author: rjs
 */

#ifndef FANASTATE_HPP_
#define FANASTATE_HPP_

#include <vent.hpp>
#include <pid.hpp>

#include <state/singlefanstate.hpp>

class FanAState : public SingleFanState {
public:
    FanAState(Controller* ctxt);
    virtual ~FanAState();
    virtual State* transitionLower();
    virtual State* transitionHigher();
};

#endif /* FANASTATE_HPP_ */
