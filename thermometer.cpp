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

Thermometer::Thermometer(DallasTemperature & sensors, uint8_t* address, float alpha, const char* name) :
    sensors_(&sensors),
    address_(address),
    smoothed_(85.0f),
    alpha_(alpha),
    name_(name) {
}

void Thermometer::setResolution(uint8_t resolution) {
    sensors_->setResolution(address_, resolution);
}

float Thermometer::rawCelsius() {
    sensors_->requestTemperatures();
    return sensors_->getTempC(address_);
}

void Thermometer::reportError(float new_value) {
    Serial.print("Thermometer error ");
    Serial.print(new_value);
    Serial.print(" for sensor ");
    if (strlen(name_) > 0) {
        Serial.print("'");
        Serial.print(name_);
        Serial.print("' ");
    }
    Serial.print("at address ");
    for (int i = 0; i < 8; ++i) {
        Serial.print(address_[i], HEX);
        Serial.print(' ');
    }
    Serial.println();
}

float Thermometer::celsius() {
    float new_value = rawCelsius();
    if (isError(new_value)) {
        reportError(new_value);
    }
    else {
        smoothed_ = isError(smoothed_) ? new_value : smooth(alpha_, smoothed_, new_value);
    }
    return smoothed_;
}

bool Thermometer::isError(float celsius) {
    return celsius == 85.0 || celsius == -127.0;
}

