# Basketball Game

An ESP32-based arcade basketball game with automatic shot detection, score tracking, timed gameplay, and electromechanical control. Two IR sensors detect successful shots, two servos operate the moving mechanisms, and an SSD1309 OLED displays the timer and score.

The firmware is written in C++ using the Arduino framework and organized into separate modules for game logic, sensor input, servo control, and display output.

<p align="center">
  <img width="35%" alt="Completed dual-hoop arcade basketball game prototype" src="https://github.com/user-attachments/assets/8c157fa5-d847-481b-853e-bd909a2bc59a" />
  &nbsp;&nbsp;&nbsp;
  <img width="50%" alt="Basketball game prototype during electronics integration and testing" src="https://github.com/user-attachments/assets/f34b2c3c-9737-45ab-b967-a0910b5d390b" />
</p>

<p align="center">
  <em>Completed prototype and electronics integration setup</em>
</p>

## Overview

The system is responsible for:

- **Game Control:** Manages the game state, 90-second timer, scoring, and round transitions.
- **Shot Detection:** Uses two IR sensors to detect balls passing through the hoops.
- **Motion Control:** Drives two servo-controlled moving mechanisms.
- **Display System:** Shows the welcome screen, countdown, remaining time, score, and final result.
- **Player Feedback:** Activates an LED and buzzer after each successful shot.
- **Hardware Testing:** Provides separate test programs for the sensors, servos, OLED, and buzzer.

The ESP32 acts as the central controller and coordinates all input, processing, and output devices.

## System Flow

<p align="center">
  <img width="500" alt="System flow diagram showing initialization, round control, shot detection, scoring, feedback, and final results" src="https://github.com/user-attachments/assets/78147bbb-1421-4560-b439-0eae33df4829" />
</p>

<p align="center">
  <em>System flow from initialization to gameplay and final score display</em>
</p>

## Game Control

The `Game` module manages the main gameplay state. Pressing the start button begins a new round, resets the score to zero, sets the timer to 90 seconds, and displays a countdown on the OLED.

During the round, the controller repeatedly checks the sensors, updates the servo positions, manages the timer, and refreshes the display. Each successful shot adds 10 points.

When the timer reaches zero, the system stops the round, disables any active feedback outputs, and displays the final score.

## Shot Detection

Each hoop contains an IR sensor connected to the ESP32 as a digital input.

The `IRSensorDriver` compares the current sensor state with its previous state. A shot is registered only when the beam changes from unbroken to broken, preventing one ball from being counted repeatedly while it remains inside the sensor beam.

Either sensor can generate a scoring event during the game.

## Motion Control

The system uses two servo motors controlled by separate `ServoDriver` objects.

Each servo repeatedly moves between 0° and 180°. Its direction reverses when it reaches either end of this range, producing continuous back-and-forth movement.

Servo timing is controlled using `millis()` rather than a blocking delay, allowing shot detection, scoring, and display updates to continue while the servos move.

## Display and Feedback

The SSD1309 OLED communicates with the ESP32 using I²C and provides the main player interface.

The display presents:

- A welcome screen
- A starting countdown
- The remaining time
- The current score
- The final score

When a shot is detected, the LED and buzzer activate for 800 ms. Their timing also uses `millis()`, allowing the rest of the game loop to continue running during the feedback period.

## Firmware Structure

```text
basketball_project/
├── include/
│   └── PinMap.h
├── lib/
│   ├── Game/
│   │   ├── Game.cpp
│   │   └── Game.h
│   ├── IRSensorDriver/
│   │   ├── IRSensorDriver.cpp
│   │   └── IRSensorDriver.h
│   ├── OLEDDriver/
│   │   ├── OLEDDriver.cpp
│   │   └── OLEDDriver.h
│   └── ServoDriver/
│       ├── ServoDriver.cpp
│       └── ServoDriver.h
├── src/
│   ├── hardware_test/
│   │   ├── buzzer_test.cpp
│   │   ├── irsensor_test.cpp
│   │   ├── oled_test.cpp
│   │   └── servo_test.cpp
│   └── main.cpp
└── platformio.ini
```

The main firmware is divided into the following modules:

| Module | Responsibility |
|---|---|
| `Game` | Coordinates the complete game state and hardware behaviour |
| `IRSensorDriver` | Detects new IR beam interruptions |
| `ServoDriver` | Controls non-blocking servo movement |
| `OLEDDriver` | Manages all OLED screens and display updates |
| `PinMap.h` | Stores the ESP32 pin assignments |
| `main.cpp` | Initializes the system and starts or runs game rounds |
| `hardware_test/` | Tests individual hardware components independently |

## Hardware Configuration

| Component | Connection | Purpose |
|---|---:|---|
| IR sensor 1 | GPIO 19 | Detects shots through the first hoop |
| IR sensor 2 | GPIO 18 | Detects shots through the second hoop |
| Servo 1 | GPIO 32 | Controls the first moving mechanism |
| Servo 2 | GPIO 33 | Controls the second moving mechanism |
| OLED SDA | GPIO 21 | I²C display data |
| OLED SCL | GPIO 22 | I²C display clock |
| LED | GPIO 26 | Visual shot feedback |
| Buzzer | GPIO 16 | Audio shot feedback |
| Start button | GPIO 27 | Starts a new game round |

## Mechanical Design and Components

The physical game combines electronic control with custom mechanical construction and 3D-printed parts.

The repository includes:

- Fusion 360 design file for the tube and handle assembly
- STEP model for compatibility with other CAD software
- AliExpress bill of materials
- DigiKey bill of materials

The CAD files are stored in the repository root, while the component spreadsheets are available in the [`BOM`](BOM) directory.

## License

This project is available under the [MIT License](LICENSE).
