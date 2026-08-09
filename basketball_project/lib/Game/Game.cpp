#include <Game.h>
#include <PinMap.h>
#include <Arduino.h>

void Game::initializeGame() {
    // servo
    servo1.initialize(SERVO1_PIN);
    servo2.initialize(SERVO2_PIN);
    // IR sensor
    IRsensor1.initialize(IR1_PIN);
    IRsensor2.initialize(IR2_PIN);
    // LED
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    // Buzzer
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, HIGH); // HIGH = silent (low-level trigger)
    // oled
    oled.initializeScreen();
}

void Game::startRound() {
    score = 0;
    secondsLeft = 90;
    oled.showCountdownIntro();
    gameRunning = true;
    lastTimerUpdate = millis();
}

void Game::runGame() {
    if (!gameRunning) return;

    servo1.spinPositional();
    servo2.spinPositional();

    if (IRsensor1.detectBreak() || IRsensor2.detectBreak()) {
        score += 10;

        digitalWrite(LED_PIN, HIGH);
        ledIsOn = true;
        ledOnTime = millis();

        digitalWrite(BUZZER_PIN, LOW);
        buzzerIsOn = true;
        buzzerOnTime = millis();
    }

    if (ledIsOn && millis() - ledOnTime >= 800) {
        digitalWrite(LED_PIN, LOW);
        ledIsOn = false;
    }

    if (buzzerIsOn && millis() - buzzerOnTime >= 800) {
        digitalWrite(BUZZER_PIN, HIGH); // silence
        buzzerIsOn = false;
    }

    if (millis() - lastTimerUpdate >= 1000) {
        lastTimerUpdate = millis();
        secondsLeft--;
        if (secondsLeft <= 0) {
            secondsLeft = 0;
            gameRunning = false;
            digitalWrite(LED_PIN, LOW);
            digitalWrite(BUZZER_PIN, HIGH);
            ledIsOn = false;
            buzzerIsOn = false;
            oled.showResults(score);
            return;
        }
    }

    oled.showGameState(secondsLeft, score);
}

bool Game::isRunning() {
    return gameRunning;
}