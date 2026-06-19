//
// ============================================================
// SMART SECURITY SYSTEM + FIWARE INTEGRATION
// FINAL STABLE VERSION
// ============================================================
//
// FEATURES:
// - Password protected security system
// - PIR motion detection
// - Ultrasonic intrusion detection
// - DHT11 monitoring
// - RGB status indication
// - Buzzer alarm
// - Alarm pause mode
// - WiFi connectivity
// - Flask backend communication
// - FIWARE integration
//
// ============================================================



// ============================================================
// LIBRARIES
// ============================================================

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include <Keypad.h>
#include <DHT.h>



// ============================================================
// WIFI CONFIGURATION
// ============================================================

const char* ssid = "ITMHDTest";

const char* password = "GK2018!!gk";



// ============================================================
// FLASK BACKEND URL
// ============================================================
//192.168.0.120 // 192.168.0.120 //192.168.0.120


const char* serverName =
"http://192.168.0.120:5050/security";



// ============================================================
// DHT11 CONFIGURATION
// ============================================================

#define DHTPIN 4

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);



// ============================================================
// PIR SENSOR
// ============================================================

#define PIR_PIN 19



// ============================================================
// ULTRASONIC SENSOR
// ============================================================

#define TRIG_PIN 5

#define ECHO_PIN 18



// ============================================================
// RGB LED
// ============================================================

#define RED_PIN 21

#define GREEN_PIN 22

#define BLUE_PIN 23



// ============================================================
// BUZZER
// ============================================================

#define BUZZER_PIN 15



// ============================================================
// KEYPAD
// ============================================================

const byte ROWS = 4;

const byte COLS = 4;

char keys[ROWS][COLS] = {

  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {
  13,
  12,
  14,
  27
};

byte colPins[COLS] = {
  26,
  25,
  33,
  32
};

Keypad keypad = Keypad(

  makeKeymap(keys),

  rowPins,

  colPins,

  ROWS,

  COLS
);



// ============================================================
// SECURITY VARIABLES
// ============================================================

String correctPIN = "1";

String enteredPIN = "";

bool systemArmed = false;

bool alarmTriggered = false;

bool disarmMode = false;

unsigned long alarmStartTime = 0;

const unsigned long alarmDuration = 5000;



// ============================================================
// RGB FUNCTION
// ============================================================
//
// BLUE  = DISARMED
// GREEN = ARMED
// RED   = ALERT
//

void setColor(
  bool red,
  bool green,
  bool blue
) {

  digitalWrite(
    RED_PIN,
    red
  );

  digitalWrite(
    GREEN_PIN,
    green
  );

  digitalWrite(
    BLUE_PIN,
    blue
  );
}



// ============================================================
// BUZZER FUNCTIONS
// ============================================================

void buzzerOn() {

  digitalWrite(
    BUZZER_PIN,
    HIGH
  );
}

void buzzerOff() {

  digitalWrite(
    BUZZER_PIN,
    LOW
  );
}



// ============================================================
// WRONG PIN ALERT
// ============================================================

void wrongPINAlert() {

  for (int i = 0; i < 2; i++) {

    setColor(
      HIGH,
      LOW,
      LOW
    );

    buzzerOn();

    delay(200);

    setColor(
      LOW,
      LOW,
      LOW
    );

    buzzerOff();

    delay(200);
  }

  //
  // Restore LED state
  //

  if (systemArmed) {

    setColor(
      LOW,
      HIGH,
      LOW
    );
  }

  else {

    setColor(
      LOW,
      LOW,
      HIGH
    );
  }
}



// ============================================================
// ULTRASONIC DISTANCE FUNCTION
// ============================================================

float getDistance() {

  digitalWrite(
    TRIG_PIN,
    LOW
  );

  delayMicroseconds(2);

  digitalWrite(
    TRIG_PIN,
    HIGH
  );

  delayMicroseconds(10);

  digitalWrite(
    TRIG_PIN,
    LOW
  );

  long duration = pulseIn(

    ECHO_PIN,

    HIGH,

    30000
  );

  float distance =
      duration * 0.034 / 2;

  //
  // Remove invalid values
  //

  if (
      distance <= 0 ||
      distance > 400
  ) {

    distance = 400;
  }

  return distance;
}



// ============================================================
// ARM SYSTEM
// ============================================================

void armSystem() {

  systemArmed = true;

  alarmTriggered = false;

  disarmMode = false;

  buzzerOff();

  //
  // GREEN = SYSTEM ARMED
  //

  setColor(
    LOW,
    HIGH,
    LOW
  );

  Serial.println();

  Serial.println(
    "SYSTEM ARMED"
  );
}



// ============================================================
// DISARM SYSTEM
// ============================================================

void disarmSystem() {

  systemArmed = false;

  alarmTriggered = false;

  disarmMode = false;

  buzzerOff();

  //
  // BLUE = SYSTEM DISARMED
  //

  setColor(
    LOW,
    LOW,
    HIGH
  );

  Serial.println();

  Serial.println(
    "SYSTEM DISARMED"
  );
}



// ============================================================
// TRIGGER ALARM
// ============================================================

void triggerAlarm() {

  alarmTriggered = true;

  alarmStartTime = millis();

  //
  // RED = ALERT
  //

  setColor(
    HIGH,
    LOW,
    LOW
  );

  buzzerOn();

  Serial.println();

  Serial.println(
    "!!! INTRUDER ALERT !!!"
  );
}



// ============================================================
// SEND DATA TO FLASK BACKEND
// ============================================================

void sendDataToServer(

  float temperature,

  float humidity,

  int motion,

  float distance
) {

  //
  // Send only if WiFi connected
  //

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    //
    // Connect to Flask backend
    //

    http.begin(serverName);

    //
    // JSON content type
    //

    http.addHeader(
      "Content-Type",
      "application/json"
    );

    //
    // Create JSON object
    //

    StaticJsonDocument<300> doc;

    doc["temperature"] =
        temperature;

    doc["humidity"] =
        humidity;

    doc["motion"] =
        motion;

    doc["distance"] =
        distance;

    doc["armed"] =
        systemArmed;

    doc["alarm"] =
        alarmTriggered;

    //
    // Convert JSON to string
    //

    String jsonString;

    serializeJson(
      doc,
      jsonString
    );

    //
    // Send POST request
    //

    int httpResponseCode =
        http.POST(jsonString);

    //
    // Debug output
    //

    Serial.println();

    Serial.print(
      "HTTP Response: "
    );

    Serial.println(
      httpResponseCode
    );

    //
    // Print backend response
    //

    String response =
        http.getString();

    Serial.println(
      response
    );

    //
    // Close connection
    //

    http.end();
  }

  else {

    Serial.println(
      "WiFi Disconnected"
    );
  }
}



// ============================================================
// SETUP
// ============================================================

void setup() {

  //
  // Start serial monitor
  //

  Serial.begin(115200);

  delay(1000);

  //
  // Start DHT sensor
  //

  dht.begin();

  //
  // Configure PIR
  //

  pinMode(
    PIR_PIN,
    INPUT
  );

  //
  // Configure ultrasonic
  //

  pinMode(
    TRIG_PIN,
    OUTPUT
  );

  pinMode(
    ECHO_PIN,
    INPUT
  );

  //
  // Configure RGB LED
  //

  pinMode(
    RED_PIN,
    OUTPUT
  );

  pinMode(
    GREEN_PIN,
    OUTPUT
  );

  pinMode(
    BLUE_PIN,
    OUTPUT
  );

  //
  // Configure buzzer
  //

  pinMode(
    BUZZER_PIN,
    OUTPUT
  );

  //
  // Initial state
  //

  buzzerOff();

  setColor(
    LOW,
    LOW,
    HIGH
  );



  // ========================================================
  // CONNECT TO WIFI
  // ========================================================

  Serial.println();

  Serial.print(
    "Connecting to WiFi"
  );

  WiFi.begin(
    ssid,
    password
  );

  while (
      WiFi.status() !=
      WL_CONNECTED
  ) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println(
    "WiFi Connected!"
  );

  Serial.print(
    "ESP32 IP Address: "
  );

  Serial.println(
    WiFi.localIP()
  );



  // ========================================================
  // STARTUP MESSAGE
  // ========================================================

  Serial.println();

  Serial.println(
    "================================="
  );

  Serial.println(
    " SMART SECURITY SYSTEM READY"
  );

  Serial.println(
    "================================="
  );

  Serial.println();

  Serial.println(
    "PIN + A -> ARM SYSTEM"
  );

  Serial.println(
    "# -> PAUSE ALARM"
  );

  Serial.println(
    "B -> DISARM SYSTEM"
  );

  Serial.println(
    "* -> CLEAR PIN"
  );

  Serial.println();
}



// ============================================================
// MAIN LOOP
// ============================================================

void loop() {

  //
  // ========================================================
  // HANDLE KEYPAD
  // ========================================================
  //

  char key = keypad.getKey();

  if (key) {

    //
    // Pause alarm mode
    //

    if (
        key == '#' &&
        alarmTriggered
    ) {

      disarmMode = true;

      //
      // Pause buzzer
      //

      buzzerOff();

      Serial.println();

      Serial.println(
        "ENTER DISABLE PIN"
      );

      enteredPIN = "";
    }

    //
    // ARM SYSTEM
    //

    else if (key == 'A') {

      if (
          enteredPIN ==
          correctPIN
      ) {

        armSystem();
      }

      else {

        Serial.println();

        Serial.println(
          "WRONG PIN"
        );

        wrongPINAlert();
      }

      enteredPIN = "";
    }

    //
    // DISARM SYSTEM
    //

    else if (key == 'B') {

      //
      // Allow disarm only after #
      //

      if (disarmMode) {

        if (
            enteredPIN ==
            correctPIN
        ) {

          disarmSystem();
        }

        else {

          Serial.println();

          Serial.println(
            "WRONG PIN"
          );

          //
          // Resume alarm
          //

          buzzerOn();

          setColor(
            HIGH,
            LOW,
            LOW
          );

          Serial.println(
            "ALARM RESUMED"
          );
        }
      }

      else {

        Serial.println();

        Serial.println(
          "PRESS # FIRST"
        );
      }

      enteredPIN = "";
    }

    //
    // CLEAR PIN
    //

    else if (key == '*') {

      enteredPIN = "";

      Serial.println();

      Serial.println(
        "PIN CLEARED"
      );
    }

    //
    // STORE PIN DIGITS
    //

    else {

      enteredPIN += key;

      //
      // Hide actual digits
      //

      Serial.print("*");
    }
  }



  //
  // ========================================================
  // SECURITY LOGIC
  // ========================================================
  //

  if (systemArmed) {

    //
    // Read sensor values
    //

    float temperature =
        dht.readTemperature();

    float humidity =
        dht.readHumidity();

    int motion =
        digitalRead(PIR_PIN);

    float distance =
        getDistance();



    //
    // Display sensor readings
    //

    Serial.println();

    Serial.print("Temp: ");

    Serial.print(
      temperature
    );

    Serial.print(
      " C | Humidity: "
    );

    Serial.print(
      humidity
    );

    Serial.print(
      " % | Distance: "
    );

    Serial.print(
      distance
    );

    Serial.print(
      " cm | Motion: "
    );

    Serial.println(
      motion
    );



    //
    // Intrusion detection logic
    //

    bool intrusionDetected = false;

    //
    // Motion detected
    //

    if (motion == HIGH) {

      intrusionDetected = true;
    }

    //
    // Object too close
    //

    if (distance < 15) {

      intrusionDetected = true;
    }

    //
    // Trigger alarm only once
    //

    if (
        intrusionDetected &&
        !alarmTriggered
    ) {

      triggerAlarm();
    }



    //
    // Send data to Flask backend
    //

    sendDataToServer(

      temperature,

      humidity,

      motion,

      distance
    );



    //
    // Auto reset alarm
    //

    if (alarmTriggered) {

      unsigned long currentTime =
          millis();

      if (
          currentTime -
          alarmStartTime >=
          alarmDuration
      ) {

        alarmTriggered = false;

        disarmMode = false;

        buzzerOff();

        //
        // Return to GREEN
        //

        setColor(
          LOW,
          HIGH,
          LOW
        );

        Serial.println(
          "Alarm Reset"
        );
      }
    }
  }

  //
  // System disarmed
  //

  else {

    buzzerOff();
  }

  //
  // Delay for stability
  //

  delay(3000);
}