#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN 8
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo lockServo;

const int servoPin = 9;
const int ledPin = 7;

// Replace this with your tag's UID (decimal array)
byte authorizedUID[] = { 123, 45, 67, 89 };

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lockServo.attach(servoPin);
  pinMode(ledPin, OUTPUT);
  lockServo.write(0); // locked position
  Serial.println("Ready to scan RFID tag...");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("UID:");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i]);
    if (i < mfrc522.uid.size - 1) Serial.print(",");
  }
  Serial.println();

  boolean match = true;
  if (mfrc522.uid.size != sizeof(authorizedUID)) {
    match = false;
  } else {
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      if (mfrc522.uid.uidByte[i] != authorizedUID[i]) {
        match = false;
        break;
      }
    }
  }

  if (match) {
    Serial.println("Access Granted");
    lockServo.write(90); // unlock
    digitalWrite(ledPin, HIGH);
    delay(2000);
    lockServo.write(0); // lock again
    digitalWrite(ledPin, LOW);
  } else {
    Serial.println("Access Denied");
    digitalWrite(ledPin, LOW);
  }

  mfrc522.PICC_HaltA();
}
