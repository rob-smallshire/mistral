/*
 * Context.hpp
 *
 *  Created on: 22 Sep 2012
 *      Author: rjs
 */

#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include <state/bothfansfromfanastate.hpp>
#include <state/bothfansfromfanbstate.hpp>
#include <state/fanastate.hpp>
#include <state/fanbstate.hpp>
#include <state/forcedirisastate.hpp>
#include <state/forcedirisbstate.hpp>
#include <state/passiveirisastate.hpp>
#include <state/passiveirisbstate.hpp>

class Max6651ClosedLoop;
class Iris;
class Thermometer;

class Controller
{
public:
	Controller(Max6651ClosedLoop* fan_a,
               Max6651ClosedLoop* fan_b,
               Iris* iris_a,
               Iris* iris_b,
               Thermometer* inside_thermometer,
               Thermometer* cabinet_thermometer,
               Thermometer* outside_thermometer);
    ~Controller();

	void update();

	int minimumFanSpeed();
	int maximumFanSpeed();
	int totalActualFanSpeed();
	void targetFanSpeed(Vent vent, int rpm);

	int openedAperture();
	int closedAperture();
	void targetAperture(Vent vent, int aperture);
	int actualAperture(Vent vent);

    BothFansFromFanAState both_fans_from_fan_a_state_;
    BothFansFromFanBState both_fans_from_fan_b_state_;
    FanAState fan_a_state_;
    FanBState fan_b_state_;
    ForcedIrisAState forced_iris_a_state_;
    ForcedIrisBState forced_iris_b_state_;
    PassiveIrisAState passive_iris_a_state_;
    PassiveIrisBState passive_iris_b_state_;

    float defaultSetpointCelsius();
    int defaultFanRpm();
    int defaultIrisAperture();

    float transitionDelay() const;

private:
	State* findNextState(State* state) const;
	void makeTransition(State* previous_state, State* next_state) const;
	float setpointTemperature(float inside, float outside);

    float default_setpoint_celsius_;
    int default_fan_rpm_;
    int default_iris_aperture_;

    State* state_;

    Max6651ClosedLoop* fans_[2];
    Iris* irises_[2];

    Thermometer* inside_thermometer_;
    Thermometer* cabinet_thermometer_;
    Thermometer* outside_thermometer_;

};


#endif /* CONTEXT_HPP_ */
