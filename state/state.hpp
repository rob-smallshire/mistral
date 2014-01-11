/*
 * state.hpp
 *
 *  Created on: 21 Sep 2012
 *      Author: rjs
 */

#ifndef STATE_HPP_
#define STATE_HPP_

class Controller;

class State
{
protected:
	State(Controller* ctxt);
public:
	virtual ~State();
	virtual bool isUntenableHigher() const = 0;
	virtual bool isUntenableLower() const = 0;
	virtual State* transitionLower() = 0;
	virtual State* transitionHigher() = 0;
	virtual void enter(State* previous_state) = 0;
	virtual void exit(State* next_state) = 0;
	virtual void update(float setpoint_temperature, float cabinet_temperature) = 0;
protected:
	Controller& context() const;
private:
	State(const State& other);
	State& operator=(const State& rhs);

	Controller* context_;
};


#endif /* STATE_HPP_ */
