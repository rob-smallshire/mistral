/*
 * passiveirisastate.hpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#ifndef PASSIVEIRISBSTATE_HPP_
#define PASSIVEIRISBSTATE_HPP_

#include <state/singlepassiveirisstate.hpp>

class PassiveIrisBState : public SinglePassiveIrisState {
public:
    PassiveIrisBState(Controller* ctxt);
    ~PassiveIrisBState();

    State* transitionHigher();
    State* transitionLower();

};



#endif /* PASSIVEIRISASTATE_HPP_ */
