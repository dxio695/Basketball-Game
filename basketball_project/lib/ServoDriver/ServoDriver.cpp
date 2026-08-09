#include <ServoDriver.h>
#include <PinMap.h>

#include <ESP32Servo.h>


void ServoDriver::initialize(int pin) {
    servo.attach(pin);
    isInitialized = true;
}

void ServoDriver::spinPositional() {
    if (!isInitialized) return;

    if (millis() - lastMoveTime >= moveInterval) {
        lastMoveTime = millis();
    
        currentAngle += moveAngle;

        if (currentAngle >= 180) {
            currentAngle = 180;
            moveAngle = -moveAngle;
        }

        if (currentAngle <= 0)  {
            currentAngle = 0;
            moveAngle = -moveAngle;
        }

        servo.write(currentAngle);

    }

}