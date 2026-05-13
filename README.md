PIR Motion Detection Alarm using ESP32

Overview:
This project demonstrates a simple motion detection alarm system using an ESP32, a PIR motion sensor, and a buzzer.

When motion is detected by the PIR sensor:
- The ESP32 turns the buzzer ON
- A message is displayed in the Serial Monitor

When no motion is detected:
- The buzzer turns OFF
- A different message is displayed in the Serial Monitor

Components Required:
| Component                    | Quantity |
| ---------------------------- | -------- |
| ESP32 Development Board      | 1        |
| PIR Motion Sensor (HC-SR501) | 1        |
| Active Buzzer                | 1        |
| Jumper Wires                 | Few      |
| Breadboard (optional)        | 1        |

Hardware Connections
PIR Sensor Connections
| PIR Sensor Pin | ESP32 Pin |
| -------------- | --------- |
| VCC            | 5V        |
| GND            | GND       |
| OUT            | GPIO12    |

Buzzer Connections
| Buzzer Pin   | ESP32 Pin |
| ------------ | --------- |
| + (Positive) | GPIO32    |
| - (Negative) | GND       |

Circuit Diagram:

        ESP32                    PIR Sensor
      ----------               -------------
         5V   -----------------> VCC
        GND   -----------------> GND
        G12   -----------------> OUT


        ESP32                    Buzzer
      ----------               ----------
        G32   -----------------> +
        GND   -----------------> -

How the Code Works:

1. Pin Definitions
   
int pirPin = 12;
  
int buzzerPin = 32;

- pirPin stores the GPIO connected to the PIR sensor
- buzzerPin stores the GPIO connected to the buzzer

2. Setup Function

void setup()

- Runs once when the ESP32 starts.

Tasks performed:
- Configure PIR pin as INPUT
- Configure buzzer pin as OUTPUT
- Start Serial Communication

3. Loop Function

void loop()

- Runs continuously.

Motion Detection

motionState = digitalRead(pirPin);

Reads the signal from the PIR sensor.
- HIGH → Motion detected
- LOW → No motion

4. Buzzer Control

MOTION DETECTED

digitalWrite(buzzerPin, HIGH);

- Turns the buzzer ON continuously.

NO MOTION

digitalWrite(buzzerPin, LOW);

- Turns the buzzer OFF.

Expected Output 

Serial Monitor
When motion is detected:
"Motion Detected! Ringing buzzer..."

When no motion is detected:
"No Motion Detected!"



