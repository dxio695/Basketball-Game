# Basketball-Game
This is an MCU-based basketball game with IR sensor detection and automated score counting.

<br>

<p align="center">
  <img width="35%" alt="Completed prototype" src="https://github.com/user-attachments/assets/8c157fa5-d847-481b-853e-bd909a2bc59a" />
  &nbsp;&nbsp;&nbsp;
  <img width="50%" alt="Completed prototyp" src="https://github.com/user-attachments/assets/f34b2c3c-9737-45ab-b967-a0910b5d390b" />
</p>

# System Flow Diagram
<p align="center">
<img width="400" alt="System flow diagram" src="https://github.com/user-attachments/assets/78147bbb-1421-4560-b439-0eae33df4829" />
</p>


# (ChatGPT made)

# MCU-Based Basketball Game

An embedded arcade basketball system that uses IR break-beam sensors to detect successful shots and automatically update the score. An ESP32 coordinates sensor input, display updates, servo movement, and audio-visual feedback.

<p align="center">
  <img width="35%" alt="Completed dual-hoop MCU-based basketball game prototype" src="https://github.com/user-attachments/assets/8c157fa5-d847-481b-853e-bd909a2bc59a" />
  &nbsp;&nbsp;&nbsp;
  <img width="50%" alt="Basketball game hardware connected for firmware and electronics testing" src="https://github.com/user-attachments/assets/f34b2c3c-9737-45ab-b967-a0910b5d390b" />
</p>

<p align="center">
  <em>Physical prototype and hardware integration setup</em>
</p>

## System Architecture

The ESP32 acts as the central controller and connects the system’s sensing, display, and electromechanical components.

| Subsystem       | Purpose                                       |
| --------------- | --------------------------------------------- |
| IR sensors      | Detect a ball passing through the hoop        |
| ESP32           | Processes sensor input and manages game logic |
| SSD1309 OLED    | Displays game information and scores          |
| Servo motor     | Controls mechanical movement                  |
| Buzzer and LEDs | Provide audio and visual feedback             |

## Control Flow

1. Read the state of each IR sensor.
2. Detect a valid beam interruption.
3. Register the event as a successful shot.
4. Update the stored score.
5. Refresh the OLED display.
6. Activate the required servo, buzzer, or LED response.

<p align="center">
  <img width="500" alt="System flow diagram for IR sensing, score processing, display updates, and output control" src="https://github.com/user-attachments/assets/78147bbb-1421-4560-b439-0eae33df4829" />
</p>

<p align="center">
  <em>Embedded system control flow</em>
</p>

## Firmware Structure

```text
Basketball-Game/
├── include/
│   └── PinMap.h
├── lib/
│   ├── IRSensorDriver/
│   ├── OLEDDriver/
│   └── ServoDriver/
├── src/
│   └── main.cpp
└── hardware_test/
    ├── irsensor_test/
    ├── oled_test/
    └── servo_test/
```

### Modules

* `IRSensorDriver` isolates shot-detection logic.
* `OLEDDriver` manages display initialization and screen updates.
* `ServoDriver` controls servo position and timing.
* `PinMap.h` centralizes hardware pin assignments.
* `main.cpp` coordinates system state and gameplay behaviour.

## Implementation Details

* Developed in C/C++ using PlatformIO
* Uses modular drivers to separate hardware control from game logic
* Includes dedicated programs for testing each hardware subsystem
* Uses `millis()`-based non-blocking timing for servo control
* Integrates sensing, display, and electromechanical outputs on one controller

## Hardware

* ESP32 microcontroller
* IR break-beam sensors
* SSD1309 OLED display
* Servo motor
* Buzzer
* LEDs
* 3D-printed mechanical components
