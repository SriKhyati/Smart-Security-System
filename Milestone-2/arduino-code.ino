// Include WiFi library for ESP32 WiFi connection
#include <WiFi.h>

// Include HTTP library for sending HTTP requests
#include <HTTPClient.h>

// =====================
// PIN DEFINITIONS
// =====================

// PIR sensor connected to GPIO12
#define PIR_PIN 12

// Buzzer connected to GPIO32
#define BUZZER_PIN 32

// =====================
// WIFI CREDENTIALS
// =====================

// WiFi network name
const char* ssid = "I******t";

// WiFi password
const char* password = "G*******gk";

// =====================
// FLASK SERVER URLS
// =====================

// Flask API endpoint for sending motion data
const char* motionUrl =
"http://192.1**.0.***:5050/motion"; // IP Address has to be changed - ifconfig

// Flask API endpoint for reading alarm state
const char* alarmUrl =
"http://192.1**.0.***:5050/alarm";

// =====================
// SETUP
// =====================

// setup() runs only once when ESP32 starts
void setup() {

  // Start Serial Monitor communication
  Serial.begin(115200);

  // Configure PIR pin as INPUT
  pinMode(PIR_PIN, INPUT);

  // Configure buzzer pin as OUTPUT
  pinMode(BUZZER_PIN, OUTPUT);

  // Start WiFi connection using SSID and password
  WiFi.begin(ssid, password);

  // Print message while connecting to WiFi
  Serial.print("Connecting to WiFi");

  // Keep checking until WiFi gets connected
  while (WiFi.status() != WL_CONNECTED) {

    // Small delay for stability
    delay(500);

    // Print dots while waiting
    Serial.print(".");
  }

  // Print success message after WiFi connection
  Serial.println("\nWiFi Connected!");

  // Print ESP32 IP address
  Serial.print("ESP32 IP: ");

  // Display local IP address
  Serial.println(WiFi.localIP());
}

// =====================
// LOOP
// =====================

// loop() runs continuously forever
void loop() {

  // Store previous motion state
  static bool lastMotion = false;

  // Read PIR sensor value
  int motion =
      digitalRead(PIR_PIN);

  // =====================
  // MOTION DETECTED
  // =====================

  // Check if motion becomes HIGH
  if (motion == HIGH &&
      lastMotion == false) {

    // Print motion message
    Serial.println(
      "Motion Detected!"
    );

    // Send motion=true to Flask backend
    sendMotion(true);

    // Update last motion state
    lastMotion = true;
  }

  // =====================
  // NO MOTION
  // =====================

  // Check if motion becomes LOW
  if (motion == LOW &&
      lastMotion == true) {

    // Print no motion message
    Serial.println(
      "No Motion"
    );

    // Send motion=false to Flask backend
    sendMotion(false);

    // Update last motion state
    lastMotion = false;
  }

  // =====================
  // CLOUD ALARM CONTROL
  // =====================

  // Get alarm state from Flask backend
  bool alarm =
      getAlarmState();

  // If alarm is true
  if (alarm) {

    // Turn buzzer ON
    digitalWrite(
      BUZZER_PIN,
      HIGH
    );

    // Print buzzer status
    Serial.println(
      "BUZZER ON"
    );

  } else {

    // Turn buzzer OFF
    digitalWrite(
      BUZZER_PIN,
      LOW
    );

    // Print buzzer status
    Serial.println(
      "BUZZER OFF"
    );
  }

  // Wait 1 second before next loop
  delay(1000);
}

// =====================
// SEND MOTION FUNCTION
// =====================

// Function for sending motion data to Flask
void sendMotion(bool state) {

  // Check WiFi connection
  if (WiFi.status() ==
      WL_CONNECTED) {

    // Create HTTP client object
    HTTPClient http;

    // Start connection to Flask motion API
    http.begin(motionUrl);

    // Set request header as JSON
    http.addHeader(
      "Content-Type",
      "application/json"
    );

    // Create JSON data
    String jsonData =
      "{\"motion\": " +
      String(state ?
             "true" :
             "false")
      + "}";

    // Print outgoing JSON
    Serial.print(
      "Sending JSON: "
    );

    // Display JSON in Serial Monitor
    Serial.println(jsonData);

    // Send POST request to Flask
    int responseCode =
      http.POST(jsonData);

    // Print HTTP response code
    Serial.print(
      "HTTP Response: "
    );

    // Display response code
    Serial.println(responseCode);

    // Close HTTP connection
    http.end();

  } else {

    // Print WiFi error message
    Serial.println(
      "WiFi Disconnected"
    );
  }
}

// =====================
// GET ALARM STATE
// =====================

// Function for reading alarm state from Flask
bool getAlarmState() {

  // Create HTTP client object
  HTTPClient http;

  // Connect to Flask alarm API
  http.begin(alarmUrl);

  // Send GET request
  int httpResponseCode =
      http.GET();

  // Default alarm state
  bool alarmState = false;

  // Check if request successful
  if (httpResponseCode > 0) {

    // Read response from server
    String response =
        http.getString();

    // Print response title
    Serial.println(
      "Alarm Response:"
    );

    // Display response JSON
    Serial.println(response);

    // Check if response contains "true"
    if (response.indexOf(
          "true") > 0) {

      // Set alarm state true
      alarmState = true;
    }
  }

  // Close HTTP connection
  http.end();

  // Return alarm state
  return alarmState;
}
