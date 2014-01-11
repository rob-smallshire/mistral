/*
 * singleforcedirisstate.hpp
 *
 *  Created on: 5 Jan 2014
 *      Author: rjs
 */

#ifndef SINGLEFORCEDIRISSTATE_HPP_
#define SINGLEFORCEDIRISSTATE_HPP_

#include <state/state.hpp>

class SingleForcedIrisState : public State {
public:
    SingleForcedIrisState(Controller* context, Vent active, Vent dormant);
    ~SingleForcedIrisState();

    virtual bool isUntenableHigher() const;
    virtual bool isUntenableLower() const;
    virtual State* transitionLower();
    virtual State* transitionHigher();
    virtual void enter(State* previous_state);
    virtual void exit(State* next_state);
    virtual void update(float setpoint_temperature, float cabinet_temperature);
private:
    Vent active_;
    Vent dormant_;
    PidController pid_;
};



#endif /* SINGLEFORCEDIRISSTATE_HPP_ */
