/*
 * linearactuator.cpp
 *
 *  Created on: 2 Jan 2014
 *      Author: rjs
 */

#include <I2C.h>

#include <iris.hpp>

Iris::Iris(uint8_t servo_controller_address, uint8_t servo_id, uint8_t analog_pin) :
    servo_controller_address_(servo_controller_address),
    servo_id_(servo_id),
    analog_pin_(analog_pin) {
}

void Iris::targetAperture(int aperture) {
    if (aperture < openedAperture() || aperture > closedAperture()) {
       return;
    }
    I2c.write(servo_controller_address_, servo_id_, (uint8_t)aperture);
}

int Iris::actualAperture() {
    return (closedAperture() - openedAperture()) * (analogRead(analog_pin_) / 1023.0f) + openedAperture();
}

