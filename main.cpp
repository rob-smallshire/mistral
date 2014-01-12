/*
 * main.cpp
 *
 *  Created on: 11 Jan 2014
 *      Author: rjs
 */

#include <Arduino.h>

#include <I2C.h>

#include <Max6651.h>
#include <utility/I2CMaster.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#include <iris.hpp>
#include <thermometer.hpp>
#include <controller.hpp>

// Iris actuator allocation
const uint8_t SERVO_CONTROLLER_ADDRESS = 40;
const uint8_t SERVO_CONFIG_REGISTER = 20;
const uint8_t SERVO_STANDARD_MODE = 0;

const int IRIS_SERVO_A = 0;
const int IRIS_SERVO_B = 1;

const int IRIS_ANALOG_A = 14;
const int IRIS_ANALOG_B = 15;

Iris iris_a(SERVO_CONTROLLER_ADDRESS, IRIS_SERVO_A, IRIS_ANALOG_A);
Iris iris_b(SERVO_CONTROLLER_ADDRESS, IRIS_SERVO_B, IRIS_ANALOG_B);

// Fan controller allocation
I2CMaster i2c_master(I2c);
Max6651ClosedLoop fan_a;
Max6651ClosedLoop fan_b;

// Thermometer allocation
const int ONE_WIRE_BUS_PIN = 17;
OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);

DeviceAddress inside_thermometer_address  = {0x28, 0xA7, 0x81, 0xEB, 0x03, 0x00, 0x00, 0xF8}; // yellow
DeviceAddress cabinet_thermometer_address = {0x28, 0x70, 0x5A, 0x71, 0x03, 0x00, 0x00, 0x6D}; // red
DeviceAddress outside_thermometer_address = {0x28, 0xEB, 0x51, 0x71, 0x03, 0x00, 0x00, 0x54}; // blue

Thermometer inside_thermometer(sensors, inside_thermometer_address, 0.05, "Inside");
Thermometer cabinet_thermometer(sensors, cabinet_thermometer_address, 0.05, "Cabinet");
Thermometer outside_thermometer(sensors, outside_thermometer_address, 0.05, "Outside");

Controller controller(&fan_a, &fan_b, &iris_a, &iris_b);

void setup() {
    delay(2000);

    Serial.begin(9600);

    Serial.print("Setup...");

    sensors.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement
    inside_thermometer.setResolution(10);
    cabinet_thermometer.setResolution(10);
    outside_thermometer.setResolution(10);

    I2c.begin();
    I2c.timeOut(100);
    I2c.write(SERVO_CONTROLLER_ADDRESS, SERVO_CONFIG_REGISTER, SERVO_STANDARD_MODE);
    analogReference(EXTERNAL);

    fan_a.begin(ConfigureMax6651(i2c_master, ADDRESS_VCC)
                                .v12()
                                .preScaler(PRESCALER_DIVIDE_BY_2)
                                .tachometerCountTime(TACH_COUNT_TIME_2_0)
                                .tachometerAlarm(true)
                                .minAlarm(true)
                                .maxAlarm(true)
                                .gpio0AsAlertOutput()
                                .gpioAsOutput(1, true)
                                .gpio2AsClockOutput()
                                .gpioAsOutput(3, true)
                                .gpioAsOutput(4, true)
                                .logger(&Serial));

    fan_b.begin(ConfigureMax6651(i2c_master, ADDRESS_GND)
                                .v12()
                                .preScaler(PRESCALER_DIVIDE_BY_2)
                                .tachometerCountTime(TACH_COUNT_TIME_2_0)
                                .tachometerAlarm(true)
                                .minAlarm(true)
                                .maxAlarm(true)
                                .gpio0AsAlertOutput()
                                .gpioAsOutput(1, true)
                                .gpio2AsClockInput()
                                .gpioAsOutput(3, true)
                                .gpioAsOutput(4, true)
                                .logger(&Serial));

   //fan_a.stop();
   //fan_b.stop();

   // TODO: Fan and iris calibration

   controller.begin();

   Serial.println("done.");
}

void loop() {
    float outside_celsius = outside_thermometer.celsius();
    float cabinet_celsius = cabinet_thermometer.celsius();
    float inside_celsius = inside_thermometer.celsius();

    Serial.print(inside_celsius);
    Serial.print(" | ");
    Serial.print(cabinet_celsius);
    Serial.print(" | ");
    Serial.println(outside_celsius);

    controller.update(inside_celsius, cabinet_celsius, outside_celsius);

    delay(1000);
    Serial.println("------------------");
}
