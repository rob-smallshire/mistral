/*
 * pid.hpp
 *
 *  Created on: 26 Dec 2013
 *      Author: rjs
 */


#ifndef PID_CONTROLLER_HPP_
#define PID_CONTROLLER_HPP_

class PidController
{
public:
    PidController(float setpoint, float initial_output,
                  float kp, float ki, float kd,
                  float output_min, float output_max);
    float update(float process_value);

    void setSetpoint(float setpoint);
    float setpoint() const;

    void setKp(float kp);
    float kp() const;

    void setKi(float ki);
    float ki() const;

    void setKd(float kd);
    float kd() const;

    void setOutput(float output);
    float output() const;

    float outputMinimum() const;
    float outputMaximum() const;

    float clampedDuration() const;
private:
    PidController(const PidController& other);
    PidController& operator=(const PidController& rhs);
    void reset(float initial_output);
    float next_period();

    float kp_;
    float ki_;
    float kd_;
    float setpoint_;
    float output_min_;
    float output_max_;
    float then_;
    float previous_process_value_;
    float error_;
    float previous_error_;
    float p_;
    float i_;
    float d_;
    float clamped_since_;
    float previous_output_;
};

#endif /* PID_CONTROLLER_HPP_ */


