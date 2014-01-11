/*
 * singlepassiveirisstate.hpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#ifndef SINGLEPASSIVEIRISSTATE_HPP_
#define SINGLEPASSIVEIRISSTATE_HPP_

class SinglePassiveIrisState : public State {
public:
    SinglePassiveIrisState(Controller* ctxt, Vent active, Vent dormant);
    ~SinglePassiveIrisState();
    virtual bool isUntenableHigher() const;
    virtual bool isUntenableLower() const;
    virtual State* transitionLower();
    virtual State* transitionHigher();
    virtual void enter(State* previous_state);
    virtual void exit(State* previous_state);
    virtual void update(float setpoint_temperature, float cabinet_temperature);
private:
    Vent active_;
    Vent dormant_;
    PidController pid_;
};



#endif /* SINGLEPASSIVEIRISSTATE_HPP_ */
