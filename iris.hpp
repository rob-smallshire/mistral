/*
 * iris.hpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#ifndef IRIS_HPP_
#define IRIS_HPP_

class Iris {
public:
    static int openedAperture();
    static int closedAperture();

    Iris(uint8_t servo_controller_address,
         uint8_t servo_id,
         uint8_t analog_pin);

    void targetAperture(int aperture);
    int actualAperture();
private:
    uint8_t servo_controller_address_;
    uint8_t servo_id_;
    uint8_t analog_pin_;
};




#endif /* IRIS_HPP_ */
