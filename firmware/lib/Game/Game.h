#pragma once
#include <PinMap.h>
#include <OLEDDriver.h>
#include <IRSensorDriver.h>
#include <ServoDriver.h>

class Game {
    public:
        void initializeGame();
        void startRound();
        void runGame();
        bool isRunning();
    private:
        ServoDriver servo1;
        ServoDriver servo2;
        IRSensorDriver IRsensor1;
        IRSensorDriver IRsensor2;
        OLEDDriver oled;
        int score = 0;
        int secondsLeft = 90;
        unsigned long lastTimerUpdate = 0;
        bool gameRunning = false;

        // LED state
        unsigned long ledOnTime = 0;
        bool ledIsOn = false;

        // Buzzer state
        unsigned long buzzerOnTime = 0;
        bool buzzerIsOn = false;
};