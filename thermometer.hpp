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
    Thermometer(DallasTemperature & sensors, uint8_t* address, float alpha=1.0, const char* name="");
    void setResolution(uint8_t resolution);
    float celsius();
    bool isError(float value);
private:
    float rawCelsius();
    void reportError(float new_value);

    DallasTemperature* sensors_;
    uint8_t* address_;
    float smoothed_;
    float alpha_;
    const char* name_;
};



#endif /* THERMOMETER_HPP_ */
