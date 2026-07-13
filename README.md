# 🔐 Smart Security System

<div align="center">

![ESP32](https://img.shields.io/badge/ESP32-Microcontroller-red?style=for-the-badge\&logo=espressif)
![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D?style=for-the-badge\&logo=arduino)
![Flask](https://img.shields.io/badge/Flask-Web_Framework-6A1B9A?style=for-the-badge&logo=flask&logoColor=white)
![Postman](https://img.shields.io/badge/Postman-API_Testing-FF6C37?style=for-the-badge&logo=postman&logoColor=white)
![FIWARE](https://img.shields.io/badge/FIWARE-Orion_Context_Broker-blue?style=for-the-badge)
![Cygnus](https://img.shields.io/badge/FIWARE-Cygnus-005571?style=for-the-badge)
![MySQL](https://img.shields.io/badge/MySQL-Database-4479A1?style=for-the-badge&logo=mysql&logoColor=white)
![IoT](https://img.shields.io/badge/IoT-Sensors-success?style=for-the-badge)
![Grafana](https://img.shields.io/badge/Grafana-Dashboard-F46800?style=for-the-badge&logo=grafana&logoColor=white)

**A cloud-enabled IoT security system that combines motion detection, environmental monitoring, intrusion prevention, historical data storage, and real-time dashboard visualization using ESP32, Flask, FIWARE, Cygnus, MySQL, and Grafana.**

*Real-time Motion Detection • Temperature Monitoring • Keypad Authentication • Cloud Integration*

</div>

---

# 📑 Table of Contents

* [📖 Project Overview](#-project-overview)
* [✨ Features](#-features)
* [🏗️ System Architecture](#-system-architecture)
* [💻 Technology Stack](#-technology-stack)
* [🔧 Hardware Components](#-hardware-components)
* [📂 Repository Structure](#-repository-structure)
* [🔌 Hardware Connections](#-hardware-connections)
* [📡 Fizzing](#-fizzing)
* [🔄 Project Workflow](#-project-workflow)
* [📊 Grafana Dashboard](#-grafana-dashboard)
* [🎯 Use Cases](#-use-cases)
* [📈 Project Milestones](#-project-milestones)
* [🚀 Future Improvements](#-future-improvements)
* [🙏 Acknowledgements](#-acknowledgements)

---

# 📖 Project Overview

Modern security systems often require expensive infrastructure and proprietary software.

This project demonstrates how an **ESP32-based IoT system** can provide an affordable, scalable, and cloud-connected smart security solution.

The system continuously monitors an indoor environment using multiple sensors and uploads contextual information to the **FIWARE Orion Context Broker** for remote monitoring.

---

## ⭐ Key Capabilities

- ✅ Motion Detection using PIR Sensor
- ✅ Temperature & Humidity Monitoring
- ✅ Ultrasonic Distance Measurement
- ✅ Keypad-based Authentication
- ✅ RGB LED Status Indication
- ✅ Audible Intrusion Alarm
- ✅ REST API Communication
- ✅ FIWARE Orion Context Management
- ✅ Historical Data Storage with Cygnus & MySQL
- ✅ Real-time Dashboard Visualization using Grafana
  
---

# ✨ Features

## 🔒 Security

* PIR-based Motion Detection
* Intrusion Alarm using Active Buzzer
* Keypad Authentication
* Unauthorized Access Detection

## 🌡️ Environmental Monitoring

* Temperature Monitoring
* Humidity Monitoring
* Configurable Temperature Thresholds
* Continuous Sensor Monitoring

## ☁ Cloud Integration

* Wi-Fi Connectivity
* REST API Communication
* Flask Backend
* FIWARE Orion Context Broker
* Historical Data Storage
* Grafana Dashboard Visualization

## 💻 Embedded System

* ESP32 Microcontroller
* Arduino Framework
* Modular Firmware
* Event-driven Processing

---

# 🏗️ System Architecture

```text
                    +-------------------------+
                    |       Sensors           |
                    |-------------------------|
                    | DHT11                   |
                    | PIR                     |
                    | HC-SR04                 |
                    | Keypad                  |
                    +-----------+-------------+
                                |
                                |
                                ▼
                    +-------------------------+
                    |         ESP32           |
                    |-------------------------|
                    | RGB LED                 |
                    | Active Buzzer           |
                    +-----------+-------------+
                                |
                           Wi-Fi / REST API
                                |
                                ▼
                    +-------------------------+
                    |      Flask Backend      |
                    +-----------+-------------+
                                |
                                ▼
                    +-------------------------+
                    | FIWARE Orion Context    |
                    | Broker                  |
                    +-----------+-------------+
                                |
                                ▼
                    +-------------------------+
                    |        Cygnus           |
                    +-----------+-------------+
                                |
                                ▼
                    +-------------------------+
                    |        MySQL            |
                    +-----------+-------------+
                                |
                                ▼
                    +-------------------------+
                    |       Grafana           |
                    +-------------------------+
```

---

# 💻 Technology Stack

| Layer            | Technology   |
| ---------------- | ------------ |
| Microcontroller  | ESP32        |
| Development IDE  | Arduino IDE  |
| Programming      | C++, Python  |
| Backend          | Flask        |
| API Testing      | Postman      |
| IoT Platform     | FIWARE Orion |
| Data Persistence | Cygnus       |
| Database         | MySQL        |
| Visualization    | Grafana      |

---

# 🔧 HARDWARE COMPONENTS:
| Component                 | Purpose                        |
|---------------------------|--------------------------------|
| ESP32 DevKit              | Main controller                |
| DHT11 Sensor              | Temperature & humidity sensing |
| PIR Motion Sensor         | Motion detection               |
| HC-SR04 Ultrasonic Sensor | Distance measurement           |
| 4×4 Keypad                | System arming/disarming        |
| RGB LED                   | Status indication              |
| Active Buzzer             | Alarm notification             |
| Breadboard                | Circuit prototyping            |
| Jumper Wires              | Component connections          |

---

# 📂 Repository Structure

```text
.
├── docs/
│   └── presentation
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

| Component | Pin/Signal | ESP32 Connection |
|------------|------------|------------------|
| **DHT11 Temperature & Humidity Sensor** | DATA | GPIO 4 |
| | VCC | 3.3V |
| | GND | GND |
| **PIR Motion Sensor** | OUT | GPIO 19 |
| | VCC | 5V |
| | GND | GND |
| **HC-SR04 Ultrasonic Sensor** | TRIG | GPIO 5 |
| | ECHO | GPIO 18 |
| | VCC | 5V |
| | GND | GND |
| **Active Buzzer** | Signal (+) | GPIO 15 |
| | GND (-) | GND |
| **RGB LED** | Red | GPIO 21 |
| | Green | GPIO 22 |
| | Blue | GPIO 23 |
| | Common Cathode | GND |
| **4×4 Matrix Keypad** | Row 1 (R1) | GPIO 13 |
| | Row 2 (R2) | GPIO 12 |
| | Row 3 (R3) | GPIO 14 |
| | Row 4 (R4) | GPIO 27 |
| | Column 1 (C1) | GPIO 26 |
| | Column 2 (C2) | GPIO 25 |
| | Column 3 (C3) | GPIO 33 |
| | Column 4 (C4) | GPIO 32 |

---

# 📡 Fizzing 

<img width="1225" height="579" alt="image" src="https://github.com/user-attachments/assets/597acd3f-09c4-4b5a-a6d7-3513816fdc8f" />

---

# 🔄 Project Workflow

# 🔄 Project Workflow

```text
                          🚀 System Start
                                │
                                ▼
                    Connect ESP32 to Wi-Fi
                                │
                                ▼
                Initialize Sensors & Actuators
                                │
                                ▼
        ┌───────────────────────────────────────────┐
        │            Read Sensor Data               │
        │                                           │
        │ • DHT11 → Temperature & Humidity          │
        │ • PIR → Motion Detection                  │
        │ • HC-SR04 → Distance Measurement          │
        │ • Keypad → User Authentication            │
        └───────────────────────────────────────────┘
                                │
                                ▼
                     Is the System Armed?
                        ┌────────┴────────┐
                        │                 │
                      No                  Yes
                        │                 │
                        ▼                 ▼
              Continue Monitoring   Motion Detected?
                                         │
                               ┌─────────┴─────────┐
                               │                   │
                              No                  Yes
                               │                   │
                               ▼                   ▼
                     Continue Monitoring   Activate RGB LED
                                           Activate Buzzer
                                                   │
                                                   ▼
                                      Collect Sensor Readings
                                                   │
                                                   ▼
                                  Send Data to Flask Backend
                                                   │
                                                   ▼
                               Update FIWARE Orion Context Broker
                                                   │
                                                   ▼
                              Cygnus Stores Historical Data
                                                   │
                                                   ▼
                                   Save Data into MySQL
                                                   │
                                                   ▼
                                Update Grafana Dashboard
                                                   │
                                                   ▼
                                   Repeat Monitoring Cycle
```
---

# 📊 Grafana Dashboard 
An interactive dashboard was created to visualize security and environmental data.

---

##The dashboard displays:

- 🌡️ Temperature
- 💧 Humidity
- 🚶 Motion Detection Events
- 📏 Distance Measurements
- 🚨 Security Alerts
- 📈 Historical Sensor Trends

---

## Dashboard Preview

<img width="1093" height="532" alt="image" src="https://github.com/user-attachments/assets/7d17987f-eda5-490e-8e94-f84dd992eef5" />

---

# 🎯 Use Cases

This Smart Security and Environmental Monitoring System can be deployed in various real-world scenarios where security, environmental monitoring, and remote accessibility are required.

| Use Case                            | Description                                                                           |
| ----------------------------------- | ------------------------------------------------------------------------------------- |
| 🏠 **Smart Homes**                  | Detect unauthorized entry, monitor room temperature, and trigger real-time alarms.    |
| 🏢 **Offices & Workspaces**         | Secure restricted areas with motion detection and keypad-based access control.        |
| 🏭 **Industrial Facilities**        | Monitor sensitive zones, detect intrusions, and track environmental conditions.       |
| 📦 **Warehouses & Storage**         | Protect valuable inventory while monitoring storage temperatures.                     |
| 🖥️ **Server Rooms & Data Centers** | Detect unauthorized access and monitor temperatures to prevent equipment overheating. |
| 🔬 **Laboratories**                 | Restrict access to research areas and continuously monitor laboratory conditions.     |
| 🏫 **Educational Institutions**     | Secure classrooms, laboratories, and equipment rooms with cloud-based monitoring.     |
| 🏥 **Healthcare Facilities**        | Protect medicine storage areas and monitor temperature-sensitive environments.        |


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

---
