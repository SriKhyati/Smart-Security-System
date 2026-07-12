# 🔐 Smart Security System

<div align="center">

![ESP32](https://img.shields.io/badge/ESP32-Microcontroller-red?style=for-the-badge\&logo=espressif)
![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D?style=for-the-badge\&logo=arduino)
![FIWARE](https://img.shields.io/badge/FIWARE-Orion_Context_Broker-blue?style=for-the-badge)
![IoT](https://img.shields.io/badge/IoT-Smart%20Security-success?style=for-the-badge)

**An IoT-based Smart Security and Environmental Monitoring System using ESP32 and FIWARE**

*Real-time Motion Detection • Temperature Monitoring • Keypad Authentication • Cloud Integration*

</div>

---

## 📑 Table of Contents

* [Project Overview](#-project-overview)
* [Features](#-features)
* [System Architecture](#-system-architecture)
* [Project Demonstration](#-project-demonstration)
* [Hardware Components](#-hardware-components)
* [Software Stack](#-software-stack)
* [Repository Structure](#-repository-structure)
* [Hardware Connections](#-hardware-connections)
* [Installation](#-installation)
* [Running the Project](#-running-the-project)
* [FIWARE Integration](#-fiware-integration)
* [Project Workflow](#-project-workflow)
* [Project Milestones](#-project-milestones)
* [Future Improvements](#-future-improvements)
* [Team](#-team)
* [Acknowledgements](#-acknowledgements)

---

# 📖 Project Overview

Modern security systems often require expensive infrastructure and proprietary software.

This project demonstrates how an **ESP32-based IoT system** can provide an affordable, scalable, and cloud-connected smart security solution.

The system continuously monitors an indoor environment using multiple sensors and uploads contextual information to the **FIWARE Orion Context Broker** for remote monitoring.

## Key Capabilities

* Motion Detection
* Temperature Monitoring
* Keypad-based Authentication
* Audible Intrusion Alarm
* Cloud Connectivity
* Real-time Context Updates
* Secure HTTPS Communication

---

# ✨ Features

## 🔒 Security

* PIR Motion Detection
* Intrusion Alarm
* Keypad PIN Verification
* Unauthorized Access Detection

## 🌡 Environmental Monitoring

* Temperature Measurement
* Configurable Temperature Thresholds
* Continuous Monitoring

## ☁ Cloud Integration

* Wi-Fi Connectivity
* HTTPS Communication
* FIWARE Orion Context Broker
* Context Entity Updates

## 💻 Embedded System

* ESP32 Controller
* Arduino Framework
* Modular Firmware
* Event-driven Processing

---

# 🏗 System Architecture

```text
                        +-------------------+
                        |   PIR Sensor      |
                        +---------+---------+
                                  |
                                  |
                    +-------------v-------------+
                    |           ESP32           |
                    |---------------------------|
                    | Motion Detection          |
                    | Temperature Monitoring    |
                    | Keypad Authentication     |
                    | Alarm Control             |
                    +------+-------------+------+
                           |             |
                 +---------+             +-----------+
                 |                                   |
        +--------v-------+                  +--------v--------+
        | Active Buzzer  |                  | Temperature     |
        |                |                  | Sensor          |
        +----------------+                  +-----------------+
                           |
                           |
                       Wi-Fi / HTTPS
                           |
                           |
                +----------v-----------+
                | FIWARE IoT Agent     |
                +----------+-----------+
                           |
                +----------v-----------+
                | Orion Context Broker |
                +----------+-----------+
                           |
                  Dashboards / APIs
```

---

`text
docs/images/motion_detection.png
```
```
# 🔧 Hardware Components

| Component         | Purpose                |
| ----------------- | ---------------------- |
| ESP32 DevKit      | Main Controller        |
| PIR Motion Sensor | Motion Detection       |
| DHT11 / DHT22     | Temperature Monitoring |
| 4×4 Matrix Keypad | User Authentication    |
| Active Buzzer     | Alarm                  |
| Breadboard        | Prototyping            |
| Jumper Wires      | Connections            |
| USB Cable         | Programming            |

---

# 💻 Software Stack

### Programming

* Arduino IDE
* C++
* ESP32 Board Package

### Libraries

* WiFi
* WiFiClientSecure
* HTTPClient
* Keypad Library
* DHT Library

### Backend

* Postman
* FIWARE IoT Agent
* Orion Context Broker

---

# 📂 Repository Structure

```text
.
├── docs/
│   ├── architecture/
│   ├── presentation/
│   ├── report/
│   └── images/
│
├── Milestone-1/
│   ├── milestone-1.ino/
│   └── README.md
│
├── Milestone-2/
│   ├── .env/
│   ├── app.py/
│   ├── token_manager.py/
│   ├── arduino-code.ino/
│   └── README.md
│
├── Milestone-3/
│   ├── .env/
│   ├── app.py/
│   ├── token_manager.py/
│   ├── Milestone-3.ino/
│   └── README.md
│
├── Milestone-4/
│   ├── .env/
│   ├── app.py/
│   ├── token_manager.py/
│   ├── Final_Code.ino/
│   └── README.md
│
└── README.md
```

---

# 🔌 Hardware Connections



---

# ⚙ Installation

## Clone Repository

```bash
git clone https://github.com/your-username/your-repository.git
cd your-repository
```

---

## Install Requirements

### Software

* Arduino IDE
* Docker Desktop
* Git

### Arduino Libraries

* WiFi
* HTTPClient
* Keypad
* DHT Sensor Library

---

# ▶ Running the Project

## Start FIWARE

```bash
docker compose up -d
```

---

## Upload ESP32 Firmware

1. Connect ESP32.
2. Select the correct board.
3. Select the correct port.
4. Upload the sketch.
5. Open the Serial Monitor (115200 baud).

---

# ☁ FIWARE Integration

The ESP32 communicates with the Orion Context Broker using secure HTTP requests.

Example Motion Entity

```json
{
  "id":"urn:ngsi-ld:MotionSensor:001",
  "type":"MotionSensor",
  "motionDetected":{
      "value":true
  }
}
```

Example Temperature Entity

```json
{
  "temperature":{
      "value":28.4
  }
}
```

---

# 🔄 Project Workflow

```text
System Starts
      │
      ▼
Connect to Wi-Fi
      │
      ▼
Initialize Sensors
      │
      ▼
Read Motion Sensor
      │
      ├── Motion?
      │      │
      │      ├── Yes
      │      │     ├── Activate Alarm
      │      │     ├── Update FIWARE
      │      │
      │      └── No
      │
      ▼
Read Temperature
      │
      ├── Above Threshold?
      │       │
      │       ├── Generate Warning
      │       └── Continue
      │
      ▼
Read Keypad
      │
      ├── Correct PIN?
      │      │
      │      ├── Yes → Access Granted
      │      └── No → Intrusion Alert
      │
      ▼
Repeat
```

---

# 📈 Project Milestones

| Milestone              | Description                       | Status |
| ---------------------- | --------------------------------- | ------ |
| Milestone 1            | Hardware setup and sensor testing | ✅      |
| Milestone 2            | FIWARE integration                | ✅      |
| Milestone 3            | Complete system integration       | ✅      |
| Milestone 4            | Additional Features               | ✅      |

---

# 🚀 Future Improvements

* Mobile App
* Push Notifications
* Email Alerts
* SMS Alerts
* Camera Integration
* RFID Authentication
* Face Recognition
* Firebase Support
* MQTT Streaming
* AI-based Threat Detection

---


# 🙏 Acknowledgements

This project was developed as part of the **Architectures for Distributed Communication Systems** course at the **University of Lübeck**.

