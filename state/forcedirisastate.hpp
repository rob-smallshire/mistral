/*
 * forcedirisastate.hpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#ifndef FORCEDIRISASTATE_HPP_
#define FORCEDIRISASTATE_HPP_

#include <state/singleforcedirisstate.hpp>

class ForcedIrisAState : public SingleForcedIrisState {
public:
    ForcedIrisAState(Controller* ctxt);
    ~ForcedIrisAState();

    virtual State* transitionHigher();
    virtual State* transitionLower();
};



#endif /* FORCEDIRISASTATE_HPP_ */
