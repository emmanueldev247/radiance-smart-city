#include <Servo.h>
#include <SoftwareSerial.h>

#define BRIDGE_UP_POSITION 70
#define BRIDGE_DOWN_POSITION 0
#define BRIDGE_MOVEMENT_DELAY 20

// global variables
Servo bridgeServo;
Servo bridgeServo2;
SoftwareSerial mySerial(7, 8); // RX, TX

const int fireInPin = 10;
const int waterInPin = 9;
const int servoPin = 5;
const int servoPin2 = 6;

bool bridgeIsUp = false;

int flame_detected, water_detected;

int delayServo = -1;
unsigned long lowStartTime = 0;
unsigned long highStartTime = 0;
unsigned long lowServoDelay = 5000; // 10 seconds in milliseconds
unsigned long highServoDelay = 5000; // 5 seconds in milliseconds

unsigned long smsThreshholdTime = 10000; // threshhold for non-stop SMS
unsigned long previousWaterTime = 0;
unsigned long waterDetectedTime = 0;

bool water_sms = false;
bool fire_sms = false;
bool firstWater = false;
bool is_waterDetected = false;


void setup() {
  Serial.begin(9600); // Open serial communications and wait for port to open
  mySerial.begin(9600); // set the data rate for the SoftwareSerial port

  pinMode(fireInPin, INPUT);
  pinMode(waterInPin, INPUT);

  bridgeServo.attach(servoPin);
  bridgeServo2.attach(servoPin2);
  bridgeServo.write(BRIDGE_DOWN_POSITION);
  bridgeServo2.write(BRIDGE_DOWN_POSITION);
}

void loop() {
  handleFlameSignal();
  handleWaterSignal();
}


void handleFlameSignal(void) {
  // FIRE DETECTION
  flame_detected = digitalRead(fireInPin);
  if (flame_detected == HIGH) {
    Serial.println("Flame signal received...! take action immediately.");
    if (!fire_sms) {
      fire_sms = true;

      call("+2348142151880");
      Serial.println ("Call made successfully");
      sendSMS("+2348142151880", "FIRE ALERT,\nURGENT: Fire reported at Radiance High School: https://maps.app.goo.gl/uK1AxtS4tDk8PfYbA.");
      Serial.println("SMS sent successfully");
    }
    else {
      Serial.println("SMS (Fire) sent earlier.....");
      delay(500);
    }
  }
  else {
    Serial.println("No Fire signal");
    fire_sms = false;
  }
}


void handleWaterSignal(void) {
  // WATER DETECTION
  water_detected = digitalRead(waterInPin);
  if (delayServo == -1) {

    if (water_detected == HIGH) {
      Serial.println("water level is HIGH\n");
      if (!is_waterDetected) {
        is_waterDetected = true;
        previousWaterTime = millis();
      }

      if (!firstWater && is_waterDetected) {
        waterDetectedTime = smsThreshholdTime + millis();
        firstWater = true;
      }
      else {
        waterDetectedTime = millis() - previousWaterTime;
      }

      if (highStartTime == 0) {
        // If the sensor is HIGH and the timer hasn't started, start the timer
        highStartTime = millis();
      }

      if (millis() - highStartTime >= highServoDelay) {
        // If 5 seconds have passed, move the servo to high
        bridgeLevel(1);
        delayServo = -1;
      }
      else {
        Serial.println("Delayed");
        // not yet time
        delayServo = 1;
      }
      lowStartTime = 0; // Reset the low timer when the sensor is HIGH


      if (waterDetectedTime >= smsThreshholdTime && !water_sms) {
        call("+2348142151880");
        Serial.println ("Call made successfully");
        sendSMS("+2348142151880", "FLOOD ALERT,\n\nURGENT: Rising water levels detected at Radiance High School: https://maps.app.goo.gl/uK1AxtS4tDk8PfYbA.");
        Serial.println("SMS sent successfully");
        water_sms = true;
      }
      else {
        Serial.println("SMS (Water) sent earlier.....");
      }
    }
    else {
      // water_detected == LOW
      Serial.println("water level dropped");
      water_sms = false;
      if (waterDetectedTime >= smsThreshholdTime) {
        is_waterDetected = false;
        Serial.println("Time up for duplicate water checks ");
      }

      if (lowStartTime == 0) {
        // If the sensor is LOW and the timer hasn't started, start the timer
        lowStartTime = millis();
      }

      if (millis() - lowStartTime >= lowServoDelay) {
        // If 7 seconds has passed, move the servo
        bridgeLevel(0);
        delayServo = -1;
      }
      else {
        delayServo = 0;
      }
      highStartTime = 0; // Reset the high timer when the sensor is LOW
    }
  }
  else if (delayServo == 0) {
    Serial.print("Time to go low...? - ");
    if (millis() - lowStartTime >= lowServoDelay) {
      // If 7 seconds have passed, move the servo low

      bridgeLevel(0);
      delayServo = -1;
      Serial.println("Success");
    }
    else {
      Serial.println("Failed... \nTime: " + String(millis() - lowStartTime));
      delayServo = 0;
    }
  }

  else if (delayServo == 1) {
    Serial.print("Time to go high...? - ");
    if (millis() - highStartTime >= highServoDelay) {
      // If 5 seconds have passed, move the servo high
      bridgeLevel(1);
      delayServo = -1;
      Serial.println("Success");
    }
    else {
      Serial.println("Failed... \nTime: " + String(millis() - highStartTime));
      delayServo = 1;
    }
  }
}


void bridgeLevel(int val) {
  Serial.println(val == 1 ? "Bridge going up" : "Bridge going down");
  delay(100);
  int targetPos = val == 1 ? BRIDGE_UP_POSITION : BRIDGE_DOWN_POSITION;


  if (val == 1) {
    if (!bridgeIsUp) {
      bridgeIsUp = true;
      for (int pos = 0; pos <= targetPos; pos++) {
        bridgeServo.write(pos);
        bridgeServo2.write(pos);
        delay(BRIDGE_MOVEMENT_DELAY);
      }
    }
  }
  else {
    if (bridgeIsUp) {
      bridgeIsUp = false;
      for (int pos = bridgeServo.read(); pos >= targetPos; pos--) {
        bridgeServo.write(pos);
        bridgeServo2.write(pos);
        delay(BRIDGE_MOVEMENT_DELAY);
      }
    }
  }
}


void call (String mobileNumber) {
  // Function to call a local cell
  mySerial.println("AT"); //Handshaking with SIM900
  readResponse();
  mySerial.println ("ATD+ " + mobileNumber + ";"); // Calling number // try no space
  readResponse();
  delay(300);
  mySerial.println();
  readResponse();
  delay(8000); // wait for 3 seconds …
  mySerial.println ("ATH"); // Ends the call
  readResponse();
  delay(300);
  mySerial.println();
}


void sendSMS(String mobileNumber, String msgBody) {
  // Function to send SMS to a local cell
  mySerial.println("AT"); // check connection
  readResponse(); // read modem response
  delay(300);
  mySerial.println("AT+CMGF=1");// SET MODULE TO TEXT MODE
  readResponse(); // read modem response
  delay(300);
  mySerial.println("AT+CMGS=\"" + mobileNumber + "\""); // sender mobile number
  readResponse(); // read modem response
  delay(300);
  mySerial.println(msgBody); // enter msg body
  readResponse(); // read modem response
  delay(300);
  mySerial.print((char)26); // indicates end of sms and then sends msg
}


void readResponse() {
  //simple function for reading modem response
  String response = mySerial.readStringUntil("OK");
  Serial.println(response);

  if (response.indexOf("ERROR") != -1) {
    Serial.println("Error in COMMS command execution");
  }
}
