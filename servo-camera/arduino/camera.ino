#include <Servo.h>

Servo panServo;
Servo tiltServo;

int panAngle = 90;
int tiltAngle = 90;

void setup() {
  Serial.begin(9600);
  panServo.attach(9);   // Pan servo pin
  tiltServo.attach(10); // Tilt servo pin

  panServo.write(panAngle);
  tiltServo.write(tiltAngle);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int commaIndex = data.indexOf(',');
    if (commaIndex > 0) {
      panAngle = data.substring(0, commaIndex).toInt();
      tiltAngle = data.substring(commaIndex + 1).toInt();

      // Constrain angles
      panAngle = constrain(panAngle, 0, 180);
      tiltAngle = constrain(tiltAngle, 0, 180);

      // Move servos
      panServo.write(panAngle);
      tiltServo.write(tiltAngle);

      // Debug output
      Serial.print("Pan: "); Serial.print(panAngle);
      Serial.print(" Tilt: "); Serial.println(tiltAngle);
    }
  }
}
