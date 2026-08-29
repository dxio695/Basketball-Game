#pragma once


#include <Wire.h>
#include <DIYables_OLED_SSD1309.h>


constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;
constexpr int OLED_RESET = -1;
constexpr uint8_t SCREEN_ADDRESS = 0x3C;


class OLEDDriver {
    public:
        void initializeScreen();
        void showCountdownIntro();
        void showGameState(int secondsLeft, int score);
        void showResults(int finalScore);


    private:
        DIYables_OLED_SSD1309 display{SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET};

        bool isInitialized = false;

        int count = 0;

        static const unsigned char basketball_bmp[] PROGMEM;

};

