/*
 * thermometer.hpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#ifndef THERMOMETER_HPP_
#define THERMOMETER_HPP_

#include <OneWire.h>
#include <DallasTemperature.h>

class Thermometer {
public:
    Thermometer(DallasTemperature & sensors, DeviceAddress address, float alpha=1.0);
    float celsius();
private:
    float rawCelsius();

    DallasTemperature* sensors_;
    uint8_t* address_;
    float smoothed_;
    float alpha_;
};



#endif /* THERMOMETER_HPP_ */
