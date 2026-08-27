#include <Game.h>
#include <Arduino.h>
#include <PinMap.h>

Game game;

bool lastButtonState = HIGH;

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP); // unpressed = HIGH, pressed = LOW
    game.initializeGame();
}

void loop() {
    int buttonState = digitalRead(BUTTON_PIN);
    bool buttonPressed = (buttonState == LOW && lastButtonState == HIGH); // falling edge
    lastButtonState = buttonState;


    if (buttonPressed && !game.isRunning()) {
        game.startRound();
    }

    game.runGame();
}