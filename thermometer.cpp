/*
 * thermometer.cpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#include <thermometer.hpp>

namespace {

    float smooth(float alpha, float previous_value, float new_value)
    {
        return alpha * new_value + (1.0 - alpha) * previous_value;
    }

}

Thermometer::Thermometer(DallasTemperature & sensors, uint8_t* address, float alpha) :
    sensors_(&sensors),
    address_(address),
    smoothed_(rawCelsius()),
    alpha_(alpha) {
}

float Thermometer::rawCelsius() {
    return sensors_->getTempC(address_);
}

float Thermometer::celsius() {

    float new_value = rawCelsius();
    return smooth(alpha_, smoothed_, new_value);
}

