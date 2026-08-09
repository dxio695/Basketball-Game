
/*
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <DIYables_OLED_SSD1309.h>

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C
#define OLED_SDA_PIN 21
#define OLED_SCL_PIN 22

DIYables_OLED_SSD1309 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 40 wide x 35 tall (bigger than before, same slight height-squeeze ratio)
const unsigned char basketball_bmp[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xE7, 0xE0, 0x00,
  0x00, 0x03, 0x9F, 0xF8, 0x00,
  0x00, 0x0F, 0x3F, 0xFC, 0x00,
  0x00, 0x0E, 0xF8, 0x02, 0x00,
  0x00, 0x30, 0x83, 0xFC, 0x00,
  0x00, 0x78, 0x3F, 0xFF, 0x00,
  0x00, 0xF7, 0xFF, 0xFF, 0x80,
  0x00, 0x07, 0xFF, 0xFF, 0xC0,
  0x01, 0xC8, 0x7F, 0xFF, 0xE0,
  0x01, 0xDF, 0x1F, 0xFF, 0xF0,
  0x03, 0x9F, 0xE7, 0xFF, 0xF0,
  0x02, 0x0F, 0xF9, 0xFF, 0xF0,
  0x01, 0xA7, 0xFE, 0x7F, 0xF8,
  0x01, 0x77, 0xFF, 0x3F, 0xF8,
  0x03, 0x7B, 0xFF, 0xCF, 0xF8,
  0x07, 0x7B, 0xFF, 0xE7, 0xF8,
  0x07, 0x7D, 0xFF, 0xF3, 0xF8,
  0x06, 0xFD, 0xFF, 0xF9, 0xF8,
  0x06, 0xFC, 0xFF, 0xFC, 0xF8,
  0x02, 0xFE, 0xFF, 0xFE, 0x78,
  0x02, 0xFE, 0xFF, 0xFF, 0x38,
  0x02, 0xFE, 0x7F, 0xFF, 0xB0,
  0x02, 0xFF, 0x7F, 0xFF, 0xD0,
  0x00, 0x7F, 0x7F, 0xFF, 0xC0,
  0x00, 0x7F, 0x3F, 0xFF, 0xE0,
  0x00, 0x7F, 0xBF, 0xFF, 0xC0,
  0x00, 0x7F, 0xBF, 0xFF, 0xC0,
  0x00, 0x7F, 0xDF, 0xFF, 0x80,
  0x00, 0x3F, 0xCF, 0xFF, 0x00,
  0x00, 0x1F, 0xE7, 0xFE, 0x00,
  0x00, 0x07, 0xF3, 0xFC, 0x00,
  0x00, 0x03, 0xFC, 0x70, 0x00,
  0x00, 0x00, 0x7F, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
};

void setup() {

  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
  if (!display.begin(SSD1309_SWITCHCAPVCC, SCREEN_ADDRESS)) {
      Serial.println(F("SSD1309 allocation failed"));
      for (;;);
  }

  display.clearDisplay();
  // 40x35 icon, centered: (128-40)/2 = 44
  display.drawBitmap(44, 0, basketball_bmp, 40, 35, SSD1309_PIXEL_ON);
  display.setTextSize(2);
  display.setTextColor(SSD1309_PIXEL_ON);
  display.setCursor(16, 37);
  display.println("Welcome!");
  display.setTextSize(1);
  display.setCursor(22, 55);
  display.println("To Basketball Game");
  display.display();

}


// try this way

unsigned long lastTimerUpdate = 0;
int secondLeft = 60;
int score = 0;

void loop() {
  if (millis() - lastTimerUpdate >= 1000) {
    lastTimerUpdate = millis();
    secondLeft--;
  }

  if (irSensorTriggered) {
    score++;
  }

  // timer
  display.clearDisplay();
  display.setCursor(2, 2);
  display.print("Time: ");
  display.print(secondLeft);

  // score
  display.setCursor(2, 16);
  display.print("Score: ");
  display.print(score);

  display.display();
  
}

*/


// test_oled.ino
#include "OLEDDriver.h"

OLEDDriver oled;

int fakeScore = 0;
int fakeSecondsLeft = 30;
unsigned long lastTimerUpdate = 0;

void setup() {
    Serial.begin(115200);

    oled.initializeScreen();
    delay(5000); // let the welcome screen sit for a bit so you can see it

    oled.showCountdownIntro(); // test the 3..2..1 sequence

    lastTimerUpdate = millis();
}

void loop() {
    // fake the timer counting down every 1 sec, same pattern as the real game
    if (millis() - lastTimerUpdate >= 1000) {
        lastTimerUpdate = millis();
        fakeSecondsLeft--;

        // fake a "score" every few seconds just to see it change on screen
        if (fakeSecondsLeft % 3 == 0) {
            fakeScore++;
        }

        if (fakeSecondsLeft <= 0) {
            oled.showResults(fakeScore);
            while (true); // stop here, freeze on results screen
        }
    }

    oled.showGameState(fakeSecondsLeft, fakeScore);
}