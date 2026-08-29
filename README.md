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

## System Operation

### Game Control

- Pressing the start button resets the score to **0** and begins a **90-second** round after the starting screen and **3–2–1** countdown.
- During gameplay, the controller updates all subsystems. When the timer reaches **0**, the game stops and the OLED displays the final score.

### Shot Detection

- Two IR sensors on **GPIO 19** and **GPIO 18** detect new **HIGH-to-LOW** transitions, preventing repeated counts while a beam remains blocked.
- A successful detection from either hoop adds **10 points**.

### Motion Control

- Two servos on **GPIO 32** and **GPIO 33** move from **0° to 180°**, reverse direction, and return to **0°**.
- Movement uses non-blocking `millis()` timing, allowing sensing and display updates to continue.

### Display and Feedback

- The OLED shows the welcome screen, countdown, remaining time, current score, and final result.
- Each successful shot activates the LED and buzzer for **800 ms**.

## Firmware Structure

```text
Firmware/
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
| [`Game`](Firmware/lib/Game) | Coordinates the complete game state and hardware behaviour |
| [`IRSensorDriver`](Firmware/lib/IRSensorDriver) | Detects new IR beam interruptions |
| [`ServoDriver`](Firmware/lib/ServoDriver) | Controls non-blocking servo movement |
| [`OLEDDriver`](Firmware/lib/OLEDDriver) | Manages all OLED screens and display updates |
| [`PinMap.h`](Firmware/include/PinMap.h) | Stores the ESP32 pin assignments |
| [`main.cpp`](Firmware/src/main.cpp) | Initializes the system and starts or runs game rounds |
| [`hardware_test/`](Firmware/src/hardware_test) | Tests individual hardware components independently |

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

## Mechanical Design

The physical structure was modelled in Fusion 360 and divided into four subassemblies so that each part could be developed, exported, and fabricated independently.

<p align="center">
  <img width="700" alt="3D modelled Court" src="https://github.com/user-attachments/assets/59b71d1a-8b7f-4310-a6b2-31a61b3ebb73" />
</p>

<p align="center">
  <em>Fusion 360 model of the complete basketball court assembly</em>
</p>

The mechanical design is organized as follows:

| Subassembly | Models | Responsibility |
|---|---|---|
| [`Basketball`](Enclosure/Basketball) | `Hoop`, `Pole` | Forms the scoring target and supports the hoop in position |
| [`Court`](Enclosure/Court) | `test2_court` | Defines the complete court structure and overall mechanical layout |
| [`Fan`](Enclosure/Fan) | `Fan Blade` | Provides the rotating element used by the ball-launching mechanism |
| [`Launcher`](Enclosure/Launcher) | `Base`, `Tube` | Supports the launcher and guides the ball through the mechanism |

Each model is provided in two formats:

- **Fusion 360 (`.f3d`):** Preserves the editable design history for further modification.
- **STEP (`.step`):** Provides a widely compatible model for other CAD and manufacturing software.

All mechanical design files are stored in the [`Enclosure`](Enclosure) directory.

## Bill of Materials

Component purchasing was documented in separate spreadsheets for AliExpress and DigiKey. Each sheet records the vendor, part details, quantity, unit price, stock status, delivery estimate, total cost in NZD, and purchase link.

| BOM | Components Covered |
|---|---|
| [AliExpress BOM](BOM/design_comp_bom_aliexpress.xlsx) | 2.42-inch OLED, I²S microphone, I²S audio amplifier, mini speaker, and MG90S 180°/360° servo options |
| [DigiKey BOM](BOM/design_comp_bom_digikey.xlsx) | SEN0503 IR break-beam sensors and WT-1205 buzzer |

The two spreadsheets provide the sourcing information used during prototype development. Reused, supplied, or structural items may not be included in these purchase requests.

## License

This project is available under the [MIT License](LICENSE).
