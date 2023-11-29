#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

#define RED_LED 7
#define GREEN_LED 6
#define BUZZER_PIN 3
#define REMOTE_SIGNAL_PIN 4
#define LOCK_DOWN_PIN 2

#define DOOR_OPEN_POSITION 100
#define DOOR_CLOSED_POSITION 170
#define BUZZER_ERROR_TONE_DELAY 300
#define DOOR_OPEN_TIME 10000  // 10 seconds


// activate and deactivate card here
const char* residentCards[] = {"12 3C F0 1B" , "1D CD FC 30"};
const int numCard = sizeof(residentCards) / sizeof(residentCards[0]);

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo gate;
unsigned long previousMillis = 0;
bool authorized = false;

enum LedState {
  RED,
  GREEN,
  OFF
};

LedState ledState = RED;  // Set the initial state to RED

int is_remote = 0;
int is_lockdown = 0;
int used_remote = 0;

void setup() {
  Serial.begin(9600);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH);  // Turn on the red LED at the beginning

  pinMode(REMOTE_SIGNAL_PIN, INPUT);
  gate.attach(5);
  gate.write(DOOR_CLOSED_POSITION);

  SPI.begin();      // Initiate SPI bus
  mfrc522.PCD_Init();
  if (!mfrc522.PCD_PerformSelfTest()) {
    Serial.println("MFRC522 self-test failed! Check your connections.");
    while (1);  // Stop the program if self-test fails
  }
  Serial.println("Place your card near the reader...\n");
  Serial.println();
}


void loop() {
  unsigned long currentMillis = millis();
  is_remote = digitalRead(REMOTE_SIGNAL_PIN);
  is_lockdown = digitalRead(LOCK_DOWN_PIN);


  // Remote mode
  if (is_remote == 0) {
    used_remote = 0;
  }
  else if (is_remote == 1) {
    if (used_remote != 1) {
      used_remote = 1;
      if (!authorized)  {
        Serial.println("Door opened by remote");
        authorized = true;
        previousMillis = currentMillis;
        door_open(1);
      }
      else {
        Serial.println("Door closed by remote");
        authorized = false;
        door_open(0);
      }
    }
  }

  if (is_lockdown == 1) { // LOCK DOWN MODE
    Serial.println("LOCK DOWN MODE!!!");
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
  else { // Access card scan

    if (ledState == RED) {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
    }
    else if (ledState == GREEN) {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
    }


    if (ledState == GREEN && currentMillis - previousMillis >= DOOR_OPEN_TIME) {
      authorized = false; // trying
      Serial.println("NO card detected & overtime!!!");
      door_open(0);
    }

    if (!mfrc522.PICC_IsNewCardPresent()) {
      if (authorized && currentMillis - previousMillis >= DOOR_OPEN_TIME) {
        authorized = false;
        Serial.println("NO card detected & overtime!!!");
        door_open(0);
      }
    }

    if (!mfrc522.PICC_ReadCardSerial()) {
      Serial.println("NO UID read");
    }

    else {
      Serial.print("UID tag: ");
      String content = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
      }

      Serial.println();
      Serial.print("Message: ");
      content.toUpperCase();


      bool isValid = false;
      for (int i = 0; i < numCard; i++) {
        if (content.substring(1) == residentCards[i]) {
          isValid = true;
          break;
        }
      }

      if (isValid)
      {
        authorized = true;
        Serial.println("Authorized access");
        previousMillis = currentMillis;
        door_open(1);

      } else {
        authorized = false;
        Serial.println("Access denied");
        door_open(0);
        buzzer_sound();
      }
    }
  }
}


void door_open(int val) {
  if (val == 1) {
    if (ledState != GREEN) ledState = GREEN;
  } else {
    if (ledState != RED) ledState = RED;
  }

  if (is_lockdown == 0) {
    digitalWrite(val == 1 ? RED_LED : GREEN_LED, LOW);
    digitalWrite(val == 1 ? GREEN_LED : RED_LED, HIGH);
  }

  Serial.println(val == 1 ? "Door open" : "Door close");

  int targetPos = val == 1 ? DOOR_OPEN_POSITION : DOOR_CLOSED_POSITION;

  if (val == 1) {
    for (int pos = gate.read(); pos >= targetPos; pos--) {
      gate.write(pos);
      delay(7);
    }
  }
  else {
    gate.write(DOOR_CLOSED_POSITION);
  }
}


void buzzer_sound() {
  Serial.println("Buzzer sound (error)");
  noTone(BUZZER_PIN);
  for (int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, 60, 250);
    delay(BUZZER_ERROR_TONE_DELAY);
  }
}
