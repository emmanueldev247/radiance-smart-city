#include <IRremote.h>

#define LDR_LOW_LIMIT 70

IRrecv IR(6);
const int controlgate = 4;
const int SLledPin = 8; // Street Light Led Pin
const int ldrPin = A0;
const int waterInPin = A1;

int ldrStatus = 0;
int ldr_mode = 1; // 1 - LDR mode (default) ;  0 - remote mode
int on_check = 0; // light check for remote switching on/off; default is 0 (off)

int gateLockdownPin[] = {5, 1}; // Gate lockdown pin
int block1LEDPin[] = {A2, 1}; // BLOCK 1 LEDs
int block2LEDPin[] = {A3, 1}; // BLOCK 2 LEDs
int block3LEDPin[] = {A4, 1}; // BLOCK 3 LEDs
int block4LEDPin[] = {A5, 1}; // BLOCK 4 LEDs

const int alarmBuzzerPin  = 11; // buzzer pin to Board 3
const int fireRedLedPin = 13; // red led for fire alarm
const int fireGreenLedPin = 12;
const int waterRedLedPin = 3; //for water alarm led
const int waterGreenLedPin = 2;


unsigned long smsThreshholdTime = 10000; // threshhold for non-stop SMS

const int flameInPin = 7;
const int fireOutPin = 10;

int isFlame = HIGH; // HIGH MEANS NO FIRE b
bool fireDetected = false;
bool firstFire = false; // for foolproofing
bool timeset = false;
unsigned long previousFireTime = 0;
unsigned long fireDetectedTime = 0;
bool smsSentFire = false;

const int waterOutPin = 9;
int waterLevel;

void setup() {
  // setting pin modes
  Serial.begin(9600);
  pinMode(ldrPin, INPUT);
  pinMode(waterInPin, INPUT);
  pinMode(flameInPin, INPUT);

  pinMode(gateLockdownPin[0], OUTPUT);
  pinMode(block1LEDPin[0], OUTPUT);
  pinMode(block2LEDPin[0], OUTPUT);
  pinMode(block3LEDPin[0], OUTPUT);
  pinMode(block4LEDPin[0], OUTPUT);

  pinMode(fireRedLedPin, OUTPUT);
  pinMode(fireGreenLedPin, OUTPUT);
  pinMode(waterRedLedPin, OUTPUT);
  pinMode(waterGreenLedPin, OUTPUT);
  pinMode(SLledPin, OUTPUT);

  pinMode(controlgate, OUTPUT);
  pinMode(alarmBuzzerPin , OUTPUT);
  pinMode(waterOutPin, OUTPUT);
  pinMode(fireOutPin, OUTPUT);

  // initializing ...
  digitalWrite(SLledPin, LOW);
  digitalWrite(fireRedLedPin, LOW);
  digitalWrite(fireGreenLedPin, HIGH);

  digitalWrite(waterRedLedPin, LOW);
  digitalWrite(waterGreenLedPin, HIGH);

  digitalWrite(controlgate, LOW);
  digitalWrite(alarmBuzzerPin , LOW);
  digitalWrite(waterOutPin, LOW);
  digitalWrite(fireOutPin, LOW);

  digitalWrite(gateLockdownPin[0], LOW);
  digitalWrite(block2LEDPin[0], HIGH);
  delay(500);
  digitalWrite(block4LEDPin[0], HIGH);
  delay(300);
  digitalWrite(block3LEDPin[0], HIGH);
  delay(200);
  digitalWrite(block1LEDPin[0], HIGH);

  Serial.println("IR Receive test");
  IR.enableIRIn();
}

void loop() {
  ldrIrHandler();
  fireWaterHandler();
}

void fireWaterHandler()
{
  // taking readings...
  isFlame = digitalRead(flameInPin);
  waterLevel = analogRead(waterInPin);

  // flame control
  if (isFlame == LOW) {
    timeset = false;
    Serial.println("Fire detected (B2)");
    if (!fireDetected) {
      fireDetected = true;
    }
    if (!firstFire && fireDetected) {
      fireDetectedTime = smsThreshholdTime + millis();
      firstFire = true;
    }
    else {
      fireDetectedTime = millis() - previousFireTime;
    }

    digitalWrite(fireGreenLedPin, LOW);
    digitalWrite(fireRedLedPin, HIGH);
    projectAlarm(1);
    for (int i = 0; i < 3; i++)  {
      digitalWrite(fireRedLedPin, HIGH);
      delay(100);
      digitalWrite(fireRedLedPin, LOW);
      delay(100);
    }
    digitalWrite(fireRedLedPin, HIGH);
  }
  else {
    if (!timeset) {
      previousFireTime = millis();
      timeset = true;
    }
    Serial.println("NO Fire (B2)");
    smsSentFire = false; // Reset the SMS flag if there's no fire
    digitalWrite(fireGreenLedPin, HIGH);
    digitalWrite(fireRedLedPin, LOW);
    digitalWrite(fireOutPin, LOW);

    if (waterLevel < 550) {
      projectAlarm(0);
    }

    if (fireDetectedTime >= smsThreshholdTime) {
      fireDetected = false;
      Serial.println("Time up for duplicate checks ");
    }
  }

  // Check if fire has been detected for 15 seconds and an SMS hasn't been sent
  if (fireDetected && fireDetectedTime >= smsThreshholdTime && !smsSentFire) {
    digitalWrite(fireOutPin, HIGH);
    Serial.println("FIRE SIGNAL sent from Board 2");
    smsSentFire = true;
  }
  else if (isFlame == LOW && fireDetectedTime < smsThreshholdTime) {
    Serial.println("--- DUPLICATE FIRE SIGNAL DENIED -----");
    Serial.println("Time is: " + String(fireDetectedTime) + "\n");
  }


  // WATER CHECK
  if (waterLevel < 470) {
    digitalWrite(waterOutPin, LOW);
    if (isFlame == HIGH) {
      projectAlarm(0);
    }
    if (waterLevel < 300) {
      digitalWrite(waterRedLedPin, LOW);
      digitalWrite(waterGreenLedPin, HIGH);
    }
  }

  if (waterLevel == 0) { // SAFE
    Serial.println("Water level is Empty");

  } else if (waterLevel > 0 && waterLevel < 300) {
    Serial.println("Water level is :" + String(waterLevel));

  } else {
    int value1 = analogRead(waterInPin);
    delay(50);
    int value2 = analogRead(waterInPin);
    delay(50);
    int value3 = analogRead(waterInPin);
    waterLevel = (value1 + value2 + value3) / 3;

    if (waterLevel > 300 && waterLevel < 470) {
      Serial.println("Water level is :" + String(waterLevel));
      Serial.println("Rising level");

      // WARNING
      digitalWrite(waterGreenLedPin, LOW);
      for (int i = 0; i < 3; i++)  {
        digitalWrite(waterRedLedPin, HIGH);
        delay(150);
        digitalWrite(waterRedLedPin, LOW);
        digitalWrite(waterGreenLedPin, HIGH);
        delay(150);
        digitalWrite(waterGreenLedPin, LOW);
      }
      digitalWrite(waterRedLedPin, LOW);
      digitalWrite(waterGreenLedPin, LOW);

    } else {
      Serial.println("Water level is :" + String(waterLevel)); // red led
      Serial.println("DANGER level");

      // DANGEROUS LEVEL

      // BUZZER WATER & LED GOES HERE ALARM ON
      projectAlarm(1);
      digitalWrite(waterGreenLedPin, LOW);
      digitalWrite(waterRedLedPin, HIGH);

      digitalWrite(waterOutPin, HIGH);
      Serial.println("WATER SIGNAL sent from Board 2");
    }
  }
}

void ldrIrHandler() {
  if (ldr_mode == 1) {
    ldrStatus = analogRead(ldrPin);
    Serial.println("LDR reads: " + String(ldrStatus));
    if (ldrStatus <= LDR_LOW_LIMIT) {
      digitalWrite(SLledPin, HIGH);
      Serial.println("It is DARK, LED is ON");
      delay(500);
    }
    else {
      digitalWrite(SLledPin, LOW);
      Serial.println("-------LED OFF--------");
    }
  }

  if (IR.decode()) {
    String ir_code = String(IR.decodedIRData.decodedRawData, HEX);
    Serial.println("Key pressed is: " + String(ir_code));

    if (ir_code == "b946ff00") {
      if (ldr_mode == 1) {
        ldr_mode = 0;
        Serial.println("LDR mode is turned off");
      }
      else {
        ldr_mode = 1;
        Serial.println("LDR mode is turned on");
      }
    }

    else if (ir_code == "ba45ff00") {
      if (on_check == 1 && ldr_mode == 0) {
        digitalWrite(SLledPin, LOW);
        Serial.println("SL turned off (manually)");
        on_check = 0;
      }
      else if (on_check == 0 && ldr_mode == 0) {
        digitalWrite(SLledPin, HIGH);
        Serial.println("SL turned on (manually)");
        on_check = 1;
      }
    }

    else if (ir_code == "bb44ff00") {
      Serial.println("GATE opened/closed with remote (to B1)");
      digitalWrite(controlgate, HIGH);
      delay(500);
      digitalWrite(controlgate, LOW);
    }

    else if (ir_code == "b847ff00") {
      switchLight(gateLockdownPin);
      Serial.println("LOCK DOWN MODE turned on/off");
    }
    else if (ir_code == "f30cff00") {
      switchLight(block1LEDPin);
      Serial.println("Block 1 light turned on/off");
    }

    else if (ir_code == "e718ff00") {
      switchLight(block2LEDPin);
      Serial.println("Block 2 light turned on/off");
    }

    else if (ir_code == "a15eff00") {
      switchLight(block3LEDPin);
      Serial.println("Block 3 light turned off");
    }

    else if (ir_code == "f708ff00") {
      switchLight(block4LEDPin);
      Serial.println("Block 4 light turned off");
    }

    IR.resume();
  }
}

void switchLight(int list[]) {
  if (list[1] == 0) {
    digitalWrite(list[0], HIGH);
    list[1] = 1;
  } else {
    digitalWrite(list[0], LOW);
    list[1] = 0;
  }
}

void projectAlarm(int val) {
  if (val == 1) {
    Serial.println("ALARM SOUNDING!!!");
    for (int i = 0; i < 3; i++) {
      digitalWrite(alarmBuzzerPin , HIGH);
      delay(100);
      digitalWrite(alarmBuzzerPin , LOW);
      delay(100);
    }
    digitalWrite(alarmBuzzerPin , HIGH);
  }
  else {
    digitalWrite(alarmBuzzerPin , LOW);
  }
}

/**
   OFF - ba45ff00
   MODE - b946ff00
   MUTE - b847ff00
   PLAY - bb44ff00
   PREV - bf40ff00
   NEXT - bc43ff00
   EQ - f807ff00
   VOL- - ea15ff00
   VOL+ - f609ff00
   0 - e916ff00
   RPT - e619ff00
   U/SD - f20dff00
   1 - f30cff00
   2 - e718ff00
   3 - a15eff00
   4 - f708ff00
   5 - e31cff00
   6 - a55aff00
   7 - bd42ff00
   8 - ad52ff00
   9 - b54aff00
*/
