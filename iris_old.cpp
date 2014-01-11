#include <Arduino.h>

#include <I2C.h>

#include <SerialCommand.h>

unsigned long previous_millis = 0;

const unsigned long interval = 500;

// Set up the servo actuators for the irises
const int SERVO_CONTROLLER_ADDRESS = 40;
const int SERVO_CONFIG_REGISTER = 20;
const int SERVO_STANDARD_MODE = 0;

const int SERVO_POSITION_MIN = 0;
const int SERVO_POSITION_MAX = 255;

enum IrisServoId {
    IRIS_SERVO_A = 0,
    IRIS_SERVO_B = 1
};

enum IrisAnalogId {
    IRIS_ANALOG_A = 14,
    IRIS_ANALOG_B = 15
};


void commandIrisPosition(IrisServoId iris_id, int position);

SerialCommand sCmd;     // The demo SerialCommand object


// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.println("What?");
}

void moveIris(IrisServoId id) {
  int aNumber;
  char *arg;

  Serial.println("We're in moveIrisA()");
  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);    // Converts a char string to an integer
    Serial.print("First argument was: ");
    Serial.println(aNumber);
    commandIrisPosition(id, aNumber);
  }
  else {
    Serial.println("No arguments");
  }
}

void moveIrisA() {
    moveIris(IRIS_SERVO_A);
}

void moveIrisB() {
    moveIris(IRIS_SERVO_B);
}

void setup() {
    Serial.begin(9600);
    Serial.println("Initializing actuators");

    I2c.begin();
    I2c.timeOut(100);
    // configure the actuators
    I2c.write(SERVO_CONTROLLER_ADDRESS, SERVO_CONFIG_REGISTER, SERVO_STANDARD_MODE);
    I2c.write(SERVO_CONTROLLER_ADDRESS, IRIS_SERVO_A, SERVO_POSITION_MIN);
    I2c.write(SERVO_CONTROLLER_ADDRESS, IRIS_SERVO_B, SERVO_POSITION_MIN);

    Serial.println("Initializing analogue");
    analogReference(EXTERNAL);

    sCmd.addCommand("A",     moveIrisA);  // Converts two arguments to integers and echos them back
    sCmd.addCommand("B",     moveIrisB);  // Converts two arguments to integers and echos them back
    sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
    Serial.println("Ready");
}

void commandIrisPosition(IrisServoId iris_id, int position) {
    if (position < 0 || position > 255) {
        return;
    }
    I2c.write(SERVO_CONTROLLER_ADDRESS, iris_id, position);
}

int readIrisSensor(IrisAnalogId iris_id) {
    switch (iris_id) {
        case IRIS_ANALOG_A:
            return analogRead(IRIS_ANALOG_A); break;
        case IRIS_ANALOG_B:
            return analogRead(IRIS_ANALOG_B); break;
    }
    return -1;
}

//void loop() {
//    sCmd.readSerial();
//    unsigned long current_millis = millis();
//
//    if (current_millis - previous_millis >= interval) {
//        previous_millis = current_millis;
//        int a = readIrisSensor(IRIS_ANALOG_A);
//        int b = readIrisSensor(IRIS_ANALOG_B);
//        Serial.print("A : ");
//        Serial.print(a);
//        Serial.print(", B : ");
//        Serial.println(b);
//    }
//}


