/*
 * both_fans_state.hpp
 *
 *  Created on: 21 Sep 2012
 *      Author: rjs
 */

#ifndef BOTH_FANS_STATE_HPP_
#define BOTH_FANS_STATE_HPP_


#include "../pid.hpp"

#include "state.hpp"

class Controller;

class BothFansState : public State
{
public:
	BothFansState(Controller* context);
	virtual ~BothFansState();

	virtual bool isUntenableHigher() const;
	virtual bool isUntenableLower() const;
	virtual void enter(State* previous_state);
	virtual void exit(State* previous_state);
	virtual void update(float setpoint_temperature, float cabinet_temperature);
private:
	PidController pid_;
};

#endif /* BOTH_FANS_STATE_HPP_ */
