#pragma once

#include <PinMap.h>
#include <ESP32Servo.h>


class ServoDriver {
    public:
        void initialize(int pin);
        void spinPositional();

    private:
        Servo servo;
        bool isInitialized = false;

        unsigned long lastMoveTime = 0;
        int currentAngle = 0;
        int moveAngle = 5; 
        const int moveInterval = 500;

};
