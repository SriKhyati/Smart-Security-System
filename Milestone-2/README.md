Smart Security System using ESP32 + FIWARE + OAuth2 + Flask

Overview

This milestone extends the basic PIR motion detection system into a distributed IoT architecture using:

ESP32
FIWARE Orion Context Broker
Keyrock Identity Manager (OAuth2)
Flask Backend Server
REST APIs

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
