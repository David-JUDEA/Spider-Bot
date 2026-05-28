<div align="center">

<img src="https://media1.tenor.com/m/G-jz-3WNwFIAAAAd/spider-man-spider-bot-spider-bot.gif" width="450">

<br/>

# 🕷️ Spider-Bot • 8-legged spider robot based on the ESP32-S2

**TIC-RBT1 · Project 3 · ETNA**

![ESP32](https://img.shields.io/badge/ESP32-S2_Mini-E7352C?style=flat-square&logo=espressif&logoColor=white)
![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)
![Toolchain](https://img.shields.io/badge/Toolchain-ESP--IDF-informational?style=flat-square)
![Status](https://img.shields.io/badge/Status-Fonctionnel-brightgreen?style=flat-square)
![Rendering](https://img.shields.io/badge/Rendu-Mai%202026-orange?style=flat-square)

bb;b</div>

## 👥 Team

<table>
  <tr>
    <td valign="middle">
      <strong>Module :</strong> TIC-RBT1 &nbsp;·&nbsp; <strong>Rendu :</strong> Mai 2026<br/>
      <strong>Co-Labs ETNA</strong> · Group of 4<br/><br/>
      <code>corde_t</code><br/>
      <code>judea_d</code><br/>
      <code>kingki_n</code><br/>
      <code src="https://github.com/JustKIKS">brouar_l</code>
    </td>
    <td valign="middle" align="center">
      <!-- Remplace par ton GIF -->
      <img src="https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExNG81Z2tsaWs0dmliaDFmeHhpNmNjbW5jajA3YXM5NWw1bzBqamprayZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/I28GbTWptIZU9fUahx/giphy.gif" width="300">
    </td>
  </tr>
</table>

## 🎯 Presentation

This project involves building and programming an **8-legged spider robot** (a quadruped with two joints per leg) based on the **ESP32-S2 Mini**. The firmware is developed in **C** using the **ESP-IDF** (Espressif IoT Development Framework) toolchain.

Each leg consists of **2 MG90S servos** (hip joint + leg joint), for a total of **8 servos**, controlled via PWM from the microcontroller’s GPIO pins through a hand-wired breadboard.

```
         			 		Leg L3 ──┐      ┌── Leg R3
         					Leg L1 ──┤      ├── Leg R1
                     			   	 │ ESP  │
          					Leg L2 ──┤  32  ├── Leg R2
          					Leg L4 ──┘ –––– └── Leg R4
									  Screen
```

An **SSD1306 OLED display** (128×64, I2C) mounted on top of the robot displays the system status in real time.

## 🧩 Components

| Component                      | Quantity     | Function                                          |
| ------------------------------ | ------------ | ------------------------------------------------- |
| Lolin / WeMos ESP32-S2 Mini    | 1            | Microcontroller — Native USB-C, PWM & I2C support |
| MG90S Servos (metal)           | 8 (+2 spare) | Hip & leg actuators                               |
| SSD1306 0.96" I2C OLED display | 1            | System status display (128×64)                    |
| Small breadboard (~5×7 cm)     | 1            | Matrix of headers & power rails                   |
| 3-pin male headers             | 8            | Servo connectors on breadboard                    |
| Buck converter (5–12V → 5V/3A) | 1            | Stable power supply for ESP32 + servos            |
| KCD1 toggle switch             | 1            | Main power cutoff                                 |
| 22 AWG silicone cable          | ∞            | Power bus & ground                                |
| 30 AWG silicone cable          | ∞            | Servo & I2C signal lines                          |
| Heat-shrink tubing             | ∞            | Junction insulation                               |
| Cable ties                     | ∞            | Internal wiring management                        |
| 3D-printed parts               | ∞            | Chassis, hips, legs, cover                        |
| M2 self-tapping screws         | ∞            | Assembly mounting                                 |
| USB-C cable (5V/3A)            | 1            | Flashing & AC power supply                        |

## 🛠️ Toolchain & Environment

The firmware is developed using **ESP-IDF** (Espressif IoT Development Framework), the official Espressif toolchain for ESP32.

### Installing ESP-IDF

```bash
# 1. Clone ESP-IDF
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf

# 2. Install the tools for ESP32-S2
./install.sh esp32s2

# 3. Set up the environment (must be done at the start of each session)
. ./export.sh
```

> The recommended version is **ESP-IDF v5.x** (LTS). Check compatibility with the ESP32-S2 Mini before using a newer version.

## 📐 Pin Configuration

| Motor / Component | Array Index | GPIO    | Position                    |
| ----------------- | ----------- | ------- | --------------------------- |
| Motor 0           | 0           | GPIO 1  | R1 — front right hip        |
| Motor 1           | 1           | GPIO 2  | R2 — front-center right hip |
| Motor 2           | 2           | GPIO 4  | L1 — front left hip         |
| Motor 3           | 3           | GPIO 6  | L2 — front-center left hip  |
| Motor 4           | 4           | GPIO 8  | R4 — rear right hip         |
| Motor 5           | 5           | GPIO 10 | R3 — rear-center right hip  |
| Motor 6           | 6           | GPIO 13 | L3 — left rear-center hip   |
| Motor 7           | 7           | GPIO 14 | L4 — rear left hip          |
| I2C SDA           | —           | GPIO 33 | SSD1306 data                |
| I2C SCL           | —           | GPIO 35 | SSD1306 clock               |

## 🔌 Wiring Diagram

> The complete diagram is available in the `Spider-Bot/` folder of the repository.

### Overview

```
Power supply (battery or USB-C)
    │
    ├──► KCD1 switch
    │        └──► Buck converter (→ regulated 5V/3A)
    │                  ├──► 5V protoboard rail  ──► Servo VCC (×8)
    │                  └──► ESP32-S2 Mini (5V)
    │
    └──► ESP32-S2 Mini
              ├── GPIO 1,2,4,6,8,10,13,14  ──► Servo signals (×8)
              ├── GPIO 33 (SDA) ──────────► SSD1306 SDA
              └── GPIO 35 (SCL) ──────────► SSD1306 SCL
```

### Wiring guidelines followed

- **22 AWG** — power bus (5V) and ground
- **30 AWG** — servo and I2C signal lines
- Use the shortest possible cables to minimize clutter
- Set the buck converter to **exactly 5.0V** on a multimeter **before** connecting the ESP32

> ⚠️ Never power on without first checking the buck converter’s output voltage. A voltage deviation exceeding 5.5V will destroy the ESP32-S2 Mini and the servos.

## 🏗️ Firmware architecture

```
SPIDERBOT/
├── .vscode/                  - VS Code editor configuration files
├── SpiderBot/                - Main directory of the ESP-IDF project
│   ├── main/                 - Application source code
│   │   ├── CMakeLists.txt    - Compilation configuration for the main folder
│   │   ├── dance.c           - Logic and implementation of movements/dances
│   │   ├── dance.h           - Definitions and headers for movements
│   │   ├── face.c            - Management of the robot's display/face
│   │   ├── face.h            - Headers for the face
│   │   ├── idf_component.yml - Configuration of ESP-IDF component dependencies
│   │   ├── main.c            - Main entry point of the program
│   │   ├── servo.c           - Implementation of servo motor control
│   │   └── servo.h           - Headers for servo motors
│   ├── .gitignore            - Exclusion rules for Git
│   ├── CMakeLists.txt        - Global CMake configuration for the project
│   └── sdkconfig             - Configuration generated by the ESP-IDF tool
└── README.md
```

## 🚀 Installation & Flashing

### Prerequisites

- ESP-IDF v5.x installed and environment variables set (`. ./export.sh`)
- 5V/3A USB-C cable
- The ESP32-S2 Mini in **upload mode** (hold down `BOOT` during startup)

### Build & flash

```bash
# Clone the repository
git clone https://github.com/David-JUDEA/Spider-Bot

# Configure the target
idf.py set-target esp32s2

# Compile
idf.py build

# Flash (adjust the serial port)
idf.py -p /dev/ttyUSB0 flash

# Serial monitor (115200 baud)
idf.py -p /dev/ttyUSB0 monitor
```

> On Windows, replace `/dev/ttyUSB0` with `COM*` (check in Device Manager).  
> Exit the monitor with **Ctrl+q**.

## 🧪 Testing & Adjustments

| Step                     | Description                                                           | Tool               |
| ------------------------ | --------------------------------------------------------------------- | ------------------ |
| **1. Buck converter**    | Check the 5.0V output with a multimeter before making any connections | Multimeter         |
| **2. Wiring continuity** | Test each connection with a multimeter in continuity mode             | Multimeter         |
| **3. ESP32 boot**        | Check the boot logs in the serial monitor                             | `idf.py monitor`   |
| **4. OLED**              | Check the display at boot without the servos connected                | Direct observation |
| **5. A single servo**    | Test the neutral position and then the extremes on a single servo     | Direct observation |
| **6. All servos**        | Check angle consistency across all 8 channels                         | Direct observation |
| **7. Walking sequence**  | Test the full gait with the robot lying flat                          | On the ground      |
| **8. Fine-tuning**       | Adjust the neutral position offsets for each servo                    | Iterative          |

## ⚡ Challenges Encountered

- **Buck converter settings**: A value that was too high (5.3V) nearly damaged a servo. This was resolved by systematically checking the voltage with a multimeter before each power-up.
- **Cable clutter**: 8 servos × 3 wires + I2C created a tangled mess of cables that was difficult to manage within the chassis. Resolved by using exclusively 30 AWG wire for signals and bundling the cables by pin group.
- **Setting up the ESP-IDF toolchain**: Sourcing the environment (`export.sh`) at the start of each session was a source of errors. Solution: Add the alias to `.bashrc` / `.zshrc`.
- **Servo Offset**: The mechanical neutral positions did not correspond exactly to 1500 µs. Resolved by calibrating an offset per servo in the firmware.
- **Screen bug**: We struggle with the settings for the axes x and y on the screen but we manage to display two static eyes.

---

<div align="center">

_Project completed at Co-Labs ETNA · ICT-RBT1 Module · May 2026_

[Corde_t](https://github.com/ThomasC-Banks) • Judea_d • [Kingki_n](https://github.com/lkb113) • [Brouar_l](https://github.com/JustKIKS)

</div>

## Gallery

![]()
![]()
![]()
![]()
![]()
