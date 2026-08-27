#include <IRSensorDriver.h>
#include "PinMap.h"

#include <Arduino.h>

void IRSensorDriver::initialize(int pin) {
    sensorPin = pin;
    pinMode(sensorPin, INPUT_PULLUP);
    delay(50);
    wasBroken = (digitalRead(sensorPin) == LOW);
    isInitialized = true;
}

bool IRSensorDriver::detectBreak() {
    if (!isInitialized) return false;

    bool isBroken = (digitalRead(sensorPin) == LOW);
    bool justBroke = isBroken && !wasBroken;
    wasBroken = isBroken;

    return justBroke;
}