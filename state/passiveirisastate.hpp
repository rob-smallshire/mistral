/*
 * passiveirisastate.hpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#ifndef PASSIVEIRISASTATE_HPP_
#define PASSIVEIRISASTATE_HPP_

#include <state/singlepassiveirisstate.hpp>

class PassiveIrisAState : public SinglePassiveIrisState {
public:
    PassiveIrisAState(Controller* ctxt);
    ~PassiveIrisAState();

    State* transitionHigher();
    State* transitionLower();
    virtual const char* name();
};



#endif /* PASSIVEIRISASTATE_HPP_ */
