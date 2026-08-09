#include <Arduino.h>

const int IR_PIN1 = 19;
const int IR_PIN2 = 18;
const int LED_PIN = 26;

int score = 0;
int lastValue1;
int lastValue2;

bool firstDetection = true;

void setup() {
    Serial.begin(115200);

    pinMode(IR_PIN1, INPUT_PULLUP);
    pinMode(IR_PIN2, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);

    digitalWrite(LED_PIN, LOW);

    delay(100);  // Let sensor settle

    lastValue1 = digitalRead(IR_PIN1);
    lastValue2 = digitalRead(IR_PIN2);
}

void loop() {
    int value1 = digitalRead(IR_PIN1);
    int value2 = digitalRead(IR_PIN2);

    // Detect falling edge (HIGH -> LOW)
    if ((value1 == LOW && lastValue1 == HIGH) || (value2 == LOW && lastValue2 == HIGH)) {

        if (firstDetection) {
            // Ignore the first false trigger after powering on
            firstDetection = false;
            Serial.println("First trigger ignored");
        } 
        else {
            score++;

            Serial.println("You scored!");
            Serial.print("Current score: ");
            Serial.println(score);

            digitalWrite(LED_PIN, HIGH);
            delay(2500);
            digitalWrite(LED_PIN, LOW);
        }
    }

    lastValue1 = value1;
    lastValue2 = value2;
}