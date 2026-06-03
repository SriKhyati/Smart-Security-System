Smart Security System using ESP32 + FIWARE + OAuth2 + Flask

Overview

This milestone extends the basic PIR motion detection system into a distributed IoT architecture using:

- ESP32
- FIWARE Orion Context Broker
- Keyrock Identity Manager (OAuth2)
- Flask Backend Server
- REST APIs

The ESP32 detects motion using a PIR sensor and sends motion data to a Flask backend over WiFi.

The Flask backend:

authenticates with FIWARE using OAuth2
obtains an access token from Keyrock IDM
updates the Orion Context Broker entity

The ESP32 also retrieves alarm status from the cloud and remotely controls a buzzer.

This demonstrates:

- Bidirectional Communication
- Cloud-controlled IoT devices
- Distributed Communication Architecture
- OAuth2 Authentication
- Real-time Context Updates

PROCESS: 
- CONNECT HARDWARE
- VS Code --> fiware-motion-project
- Terminal -> cd backend -> source venv/bin/activate -> (venv) -> python3 app.py -> Running on http://127.0.0.1:5050 (Flask Backend is Working)
- Verify Alarm API -> http://127.0.0.1:5050/alarm -> Expected: {"alarm": true} -> Flask ↔ Orion ↔ OAuth2 (Works)
- Arduino IDE -> Upload code
- TEST MOTION SENSOR: 
    - Wave hand in front of PIR sensor.
- Expected:
Motion Detected!
Sending JSON: {"motion": true}
HTTP Response: 200
- CREATE PATCH REQUEST
    - PATCH
        - URL:
            - https://broker.fiware.itm.uni-luebeck.de/v2/entities/PIR001/attrs
             - HEADERS
             - KEY	VALUE
                - Content-Type - application/json
                - X-Auth-Token	- token (Oauth2)
                - fiware-service - itm
                - fiware-servicepath - /archvek/SS26
             - BODY → raw → JSON - { "alarm": { "value": true, "type": "Boolean"} }
             - BUZZER ON AND buzzer turns ON physically.
              
- FINAL:
1. PIR detects motion
2. ESP32 sends motion to Flask
3. Flask authenticates using OAuth2
4. Orion entity updates
5. Cloud stores state
6. Alarm attribute updated remotely
7. ESP32 fetches alarm state
8. Cloud remotely controls buzzer
