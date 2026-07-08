PROJECT OVERVIEW\
The Smart Security System is an IoT-based security monitoring solution developed using ESP32, FIWARE, Flask, MySQL, and Grafana. The system continuously monitors environmental and security-related parameters such as temperature, humidity, motion detection, and distance measurements. Data collected from sensors is transmitted to the FIWARE ecosystem, stored in a database, and visualized through an interactive Grafana dashboard.

The Smart Security System has been extended with advanced security features, including keypad-based arming/disarming, enhanced alarm logic, improved dashboard visualizations, and persistent event logging. The system now provides both real-time monitoring and intelligent security management through the FIWARE ecosystem.

## System Architecture
```text
 ┌──────────────┐
 │   Sensors    │
 │──────────────│
 │ DHT11        │
 │ PIR          │
 │ HC-SR04      │
 │ Keypad       │
 └──────┬───────┘
        │
        ▼
 ┌──────────────┐
 │    ESP32     │
 │──────────────│
 │ RGB LED      │
 │ Buzzer       │
 └──────┬───────┘
        │
        ▼
 ┌──────────────┐
 │ Flask Backend│
 └──────┬───────┘
        │
        ▼
 ┌──────────────┐
 │ FIWARE Orion │
 └──────┬───────┘
        │
        ▼
 ┌──────────────┐
 │    Cygnus    │
 └──────┬───────┘
        │
        ▼
 ┌──────────────┐
 │    MySQL     │
 └──────┬───────┘
        │
        ▼
 ┌──────────────┐
 │   Grafana    │
 └──────────────┘
```

HARDWARE COMPONENTS:

| Component | Purpose |
|------------|------------|
| ESP32 DevKit | Main controller |
| DHT11 Sensor | Temperature & humidity sensing |
| PIR Motion Sensor | Motion detection |
| HC-SR04 Ultrasonic Sensor | Distance measurement |
| 4×4 Keypad | System arming/disarming |
| RGB LED | Status indication |
| Active Buzzer | Alarm notification |
| Breadboard | Circuit prototyping |
| Jumper Wires | Component connections |

Hardware Connections:
| Component                           | Pin/Signal     | ESP32 GPIO |
| ----------------------------------- | -------------- | ---------- |
| DHT11 Temperature & Humidity Sensor | DATA           | GPIO 4     |
| DHT11 Temperature & Humidity Sensor | VCC            | 3.3V       |
| DHT11 Temperature & Humidity Sensor | GND            | GND        |
| PIR Motion Sensor                   | OUT            | GPIO 19    |
| PIR Motion Sensor                   | VCC            | 5V         |
| PIR Motion Sensor                   | GND            | GND        |
| HC-SR04 Ultrasonic Sensor           | TRIG           | GPIO 5     |
| HC-SR04 Ultrasonic Sensor           | ECHO           | GPIO 18    |
| HC-SR04 Ultrasonic Sensor           | VCC            | 5V         |
| HC-SR04 Ultrasonic Sensor           | GND            | GND        |
| Active Buzzer                       | Signal (+)     | GPIO 15    |
| Active Buzzer                       | GND (-)        | GND        |
| RGB LED (Red)                       | Red Channel    | GPIO 21    |
| RGB LED (Green)                     | Green Channel  | GPIO 22    |
| RGB LED (Blue)                      | Blue Channel   | GPIO 23    |
| RGB LED                             | Common Cathode | GND        |
| 4×4 Keypad                          | Row 1 (R1)     | GPIO 13    |
| 4×4 Keypad                          | Row 2 (R2)     | GPIO 12    |
| 4×4 Keypad                          | Row 3 (R3)     | GPIO 14    |
| 4×4 Keypad                          | Row 4 (R4)     | GPIO 27    |
| 4×4 Keypad                          | Column 1 (C1)  | GPIO 26    |
| 4×4 Keypad                          | Column 2 (C2)  | GPIO 25    |
| 4×4 Keypad                          | Column 3 (C3)  | GPIO 33    |
| 4×4 Keypad                          | Column 4 (C4)  | GPIO 32    |

Fizzing Diagram:
<img width="1225" height="579" alt="image" src="https://github.com/user-attachments/assets/597acd3f-09c4-4b5a-a6d7-3513816fdc8f" />

SOFTWARE COMPONENTS:
- Python Flask
- FIWARE Orion Context Broker
- FIWARE Cygnus
- Postman 
- MySQL Database
- Grafana

IMPLEMENTED FEATURES

-> 1. Real-Time Sensor Monitoring\
The ESP32 continuously reads data from:

DHT11 Sensor
- Temperature (°C)
- Humidity (%)
  
PIR Sensor
- Motion Detection
- Intrusion Monitoring
  
Ultrasonic Sensor
- Distance Measurement (cm)
  
Buzzer
- Activated when motion is detected


-> 2. Data Transmission\
Sensor readings are sent from ESP32 to the Flask backend through HTTP requests.

Example reading:

Temp: 22.8°C\
Humidity: 51%\
Distance: 43.93 cm\
Motion: 0

Backend response:

{
  "message": "Security Data Sent Successfully",
  "orion_status": 204
}

The 204 response confirms successful updates to Orion Context Broker.

-> 3. FIWARE Integration\
Orion Context Broker\
The Flask backend updates a Smart Security entity inside Orion.

Entity Attributes:

{\
  "temperature": 22.8,\
  "humidity": 51,\
  "distance": 43.93,\
  "motion": 0,\
  "armed": true\
}

Cygnus Subscription

Cygnus subscribes to entity updates and stores historical data in MySQL.

Subscription Status:

{
  "status": "active",
  "description": "Notify Cygnus"
}

-> 4. Data Persistence
Sensor readings are automatically stored in MySQL using Cygnus.

Stored Information:
- Timestamp
- Temperature
- Humidity
- Distance
- Motion Status
- Armed Status

This enables historical analysis and long-term monitoring.

## System Workflow

```text
User enters password
        |
        v
System armed / disarmed using keypad
        |
        v
ESP32 reads sensor values
        |
        v
DHT11 → Temperature & Humidity
PIR → Motion Detection
HC-SR04 → Distance Measurement
        |
        v
Is system armed?
        |
   +----+----+
   |         |
  No        Yes
   |         |
   v         v
Normal    Motion detected?
monitoring     |
               +----+----+
               |         |
              No        Yes
               |         |
               v         v
          Continue     Activate alarm
          monitoring   RGB LED + Buzzer
               |         |
               +----+----+
                    |
                    v
ESP32 sends data to Flask Backend
                    |
                    v
Flask updates FIWARE Orion Context Broker
                    |
                    v
Cygnus stores historical data
                    |
                    v
MySQL Database
                    |
                    v
Grafana Dashboard Visualization
```

GRAFANA DASHBOARD\
An interactive dashboard was created to visualize security and environmental data.

Visualization:
<img width="1093" height="532" alt="image" src="https://github.com/user-attachments/assets/7d17987f-eda5-490e-8e94-f84dd992eef5" />


Dashboard Panels

- System Status\
Displays: SYSTEM ARMED\
Indicates whether the security system is active.

- Intrusion Detection\
Shows the latest motion detection status.

Values:
SAFE or INTRUSION DETECTED

- Total Intrusion Count\
Displays the total number of times motion was detected.

Purpose:\
-> Security analytics\
-> Event frequency monitoring

- Temperature Monitoring\
Visualization Type: Time Series Graph\
Displays temperature trends over time.

- Humidity Monitoring\
Visualization Type: Gauge

Thresholds:
| Range    | Status |
| -------- | ------ |
| 0 – 30 %  | Dry    |
| 30 – 60 %  | Normal |
| 60 – 100 % | Humid  |

- Distance Monitoring\
Visualization Type: Time Series Graph\
Displays object proximity measurements from the ultrasonic sensor.

- Security Event Log\
Contains:\
-> Timestamp\
-> Sensor Attribute\
-> Sensor Value

Provides historical records of all security events.

Challenges Encountered:
- ESP32 Wi-Fi reconnection
- Orion entity updates
- Cygnus subscription configuration
- Grafana SQL queries
- Sensor calibration

Future Improvements:
- Email/SMS notifications
- Camera integration
- Mobile application
- Face recognition
- MQTT communication
- Cloud deployment
- AI-based anomaly detection

RESULTS\
The completed system provides a scalable and modular smart security platform capable of monitoring environmental conditions and intrusion events while maintaining historical records for future analysis.
