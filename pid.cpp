#include <math.h>

#include <Arduino.h>

#include <pid.hpp>

PidController::PidController(float setpoint, float initial_output,
                             float kp, float ki, float kd,
                             float output_min, float output_max) :
    kp_(kp),
    ki_(ki),
    kd_(kd),
    setpoint_(setpoint),
    output_min_(output_min),
    output_max_(output_max)
{
    reset(initial_output);
}

void PidController::reset(float initial_output)
{
    then_ = millis();
    previous_process_value_ = NAN;
    error_ = 0.0f;
    previous_error_ = NAN;
    p_ = 0.0f;
    i_ = initial_output;
    d_ = 0.0f;
    clamped_since_ = 0;
    clamped_ = false;

    if (i_ > output_max_)
    {
         i_ = output_max_;
    }

    if (i_ < output_min_)
    {
        i_ = output_min_;
    }

    previous_output_ = i_;
}


float PidController::next_period()
{
    unsigned long now = millis();
    unsigned long dt = now - then_;
    then_ = now;
    if (dt == 0) {
        dt = 1; // Always at least one millisecond
    }
    return dt / 1000.0f;
}

float PidController::update(float process_value)
{
    float dt = next_period();
    error_ = setpoint_ - process_value;

    p_ = kp_ * error_;
    i_ += ki_ * error_ * dt;

    if (isnan(previous_error_)) {
        previous_error_ = error_;
    }

    d_ = kd_ * (error_ - previous_error_) / dt;

    float output = p_ + i_ + d_;

    Serial.print("dt = ");
    Serial.print(dt);
    Serial.print("error_ = ");
    Serial.print(error_);
    Serial.print(", p_ = ");
    Serial.print(p_);
    Serial.print(", i_ = ");
    Serial.print(i_);
    Serial.print(", d_ = ");
    Serial.print(d_);
    Serial.println();

    if (output > output_max_)
    {
        i_ -= output - output_max_;
        output = output_max_;
        if (isnan(clamped_since_))
        {
            clamped_since_ = millis();
            clamped_ = true;
        }
    }
    else if (output < output_min_)
    {
        i_ += output_min_ - output;
        output = output_min_;
        if (isnan(clamped_since_))
        {
            clamped_since_ = millis();
            clamped_ = true;
        }
    }
    else
    {
        clamped_ = false;
    }

    previous_output_ = output;
    previous_error_ = error_;

    return output;
}

void PidController::setSetpoint(float setpoint)
{
    setpoint_ = setpoint;
}

float PidController::setpoint() const
{
    return setpoint_;
}

void PidController::setKp(float kp)
{
    kp_ = kp;
}

float PidController::kp() const
{
    return kp_;
}

void PidController::setKi(float ki)
{
    ki_ = ki;
}

float PidController::ki() const
{
    return ki_;
}

void PidController::setKd(float kd)
{
    kd_ = kd;
}

float PidController::kd() const
{
    return kd_;
}

void PidController::setOutput(float output)
{
    reset(output);
}

float PidController::output() const
{
    return previous_output_;
}

float PidController::outputMinimum() const
{
    return output_min_;
}

float PidController::outputMaximum() const
{
    return output_max_;
}

float PidController::clampedDuration() const
{
    return clamped_ ? 0.0f : (millis() - clamped_since_) / 1000.0f;
}

