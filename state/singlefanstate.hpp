/*
 * singlefanstate.hpp
 *
 *  Created on: 26 Dec 2013
 *      Author: rjs
 */

#ifndef SINGLEFANSTATE_HPP_
#define SINGLEFANSTATE_HPP_


#include <vent.hpp>

#include <state/state.hpp>

class PidController;

class SingleFanState : public State {
public:
    SingleFanState(Controller* context, Vent active, Vent dormant);
    ~SingleFanState();
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



#endif /* SINGLEFANSTATE_HPP_ */
