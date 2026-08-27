#include <ESP32Servo.h>

#include <PinMap.h>


Servo servo1;
Servo servo2;

void setup() {
  servo1.attach(SERVO1_PIN);  // attaches the servo on ESP32 pin
  servo2.attach(SERVO2_PIN);

}

void loop() {
  for (int i = 0; i <= 180; i += 15) {
    servo1.write(i);
    servo2.write(i);
    delay(500);
  }

  for (int i = 180; i >= 0; i -= 15) {
    servo1.write(i);
    servo2.write(i);
    delay(500);
  }

}

