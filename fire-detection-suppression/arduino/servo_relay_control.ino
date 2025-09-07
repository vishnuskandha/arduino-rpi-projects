#include <Servo.h>
Servo panServo, tiltServo;
int relayPin = 7;

void setup() {
  panServo.attach(9);
  tiltServo.attach(10);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Example: sweep and trigger relay (simulation)
  for (int pos = 0; pos <= 180; pos += 10) {
    panServo.write(pos);
    delay(200);
  }
  digitalWrite(relayPin, HIGH); // Activate solenoid
  delay(1000);
  digitalWrite(relayPin, LOW);
}
