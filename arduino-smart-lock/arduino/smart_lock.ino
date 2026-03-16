#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Keypad layout
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 6, 7, 8};
byte colPins[COLS] = {9, 10, 11, 12};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// RFID
#define RST_PIN 9
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Servo
Servo lockServo;
const int SERVO_PIN = 3;
const int SERVO_LOCKED = 0;
const int SERVO_UNLOCKED = 90;

// LEDs
const int LED_GRANTED = 2;
const int LED_DENIED = A0;

// PIN code
const char* CORRECT_PIN = "1234";  // change this

String inputPIN = "";
bool accessGranted = false;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  lockServo.attach(SERVO_PIN);
  pinMode(LED_GRANTED, OUTPUT);
  pinMode(LED_DENIED, OUTPUT);
  lockServo.write(SERVO_LOCKED);
  Serial.println("READY");
}

void grantAccess(String method, String id) {
  accessGranted = true;
  lockServo.write(SERVO_UNLOCKED);
  digitalWrite(LED_GRANTED, HIGH);
  delay(2000);
  lockServo.write(SERVO_LOCKED);
  digitalWrite(LED_GRANTED, LOW);
  Serial.print("LOG,");
  Serial.print(method);
  Serial.print(",");
  Serial.println(id);
}

void denyAccess() {
  digitalWrite(LED_DENIED, HIGH);
  delay(1000);
  digitalWrite(LED_DENIED, LOW);
}

void handleKeypad() {
  char key = keypad.getKey();
  if (key) {
    if (key >= '0' && key <= '9') {
      inputPIN += key;
      if (inputPIN.length() == 4) {
        if (inputPIN == CORRECT_PIN) {
          grantAccess("PIN", inputPIN);
        } else {
          denyAccess();
        }
        inputPIN = "";
      }
    } else if (key == '*') {
      inputPIN = ""  // reset
    }
  }
}

void handleRFID() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (i) uid += ":";
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();

  // Simple whitelist (add your tags)
  if (uid == "DE:AD:BE:EF" || uid == "12:34:56:78") {  // example UIDs
    grantAccess("RFID", uid);
  } else {
    denyAccess();
  }

  mfrc522.PICC_HaltA();
}

void loop() {
  handleKeypad();
  handleRFID();
}
