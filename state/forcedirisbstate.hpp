/*
 * forcedirisastate.hpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#ifndef FORCEDIRISBSTATE_HPP_
#define FORCEDIRISBSTATE_HPP_

class ForcedIrisBState : public SingleForcedIrisState {
public:
    ForcedIrisBState(Controller* ctxt);
    ~ForcedIrisBState();

    virtual State* transitionHigher();
    virtual State* transitionLower();
};



#endif /* FORCEDIRISBSTATE_HPP_ */
