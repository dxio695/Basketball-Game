#pragma once

#include <PinMap.h>


class IRSensorDriver {
    public:
        void initialize(int pin);
        bool detectBreak();

    private:
        int sensorPin;
        bool isInitialized = false;
        bool wasBroken = false;
};