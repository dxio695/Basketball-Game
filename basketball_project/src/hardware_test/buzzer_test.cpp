#include <Arduino.h>

const int buzzer_pin = 16;

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  Serial.begin(115200);


}

void loop() {


  digitalWrite(buzzer_pin, LOW);
  Serial.print("1");
  delay(1000);
  digitalWrite(buzzer_pin, HIGH);
  Serial.print("2");
  delay(3000);
  digitalWrite(buzzer_pin, LOW);
  Serial.print("3");
  delay(5000);
  digitalWrite(buzzer_pin, HIGH);
  Serial.print("4");   
  delay(7000);


}