#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(2, 3); // RX, TX for HC-05

// L293D Motor Driver pins
#define MOTOR_LEFT_IN1 4  // M1 IN1
#define MOTOR_LEFT_IN2 5  // M1 IN2
#define MOTOR_RIGHT_IN1 6  // M2 IN1
#define MOTOR_RIGHT_IN2 7  // M2 IN2

void setup() {
  Serial.begin(38400); // <<< Baud rate set to match HC-05 module
  BT.begin(38400);     // <<< Baud rate set to match HC-05 module

  // Initialize motor pins
  pinMode(MOTOR_LEFT_IN1, OUTPUT);
  pinMode(MOTOR_LEFT_IN2, OUTPUT);
  pinMode(MOTOR_RIGHT_IN1, OUTPUT);
  pinMode(MOTOR_RIGHT_IN2, OUTPUT);

  // LED/Relay pin (your original pin 8)
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);

  // Stop all motors initially
  stopCar();

  Serial.println("Bluetooth Car Ready!");
}

void loop() {
  if (BT.available()) {
    String command = BT.readStringUntil('\n'); // Reads until newline
    command.trim(); // Remove any leading/trailing whitespace
    Serial.println("Received: " + command); // Log received command

    // LED/Device control
    if (command == "on") {
      digitalWrite(8, HIGH);
      Serial.println("LED/Device ON");
    } else if (command == "off") {
      digitalWrite(8, LOW);
      Serial.println("LED/Device OFF");
    }

    // Car movement controls
    else if (command == "forward" || command == "F") {
      moveForward();
    } else if (command == "backward" || command == "B") {
      moveBackward();
    } else if (command == "left" || command == "L") {
      turnLeft();
    } else if (command == "right" || command == "R") {
      turnRight();
    } else if (command == "stop" || command == "S") {
      stopCar();
    }
  }
}

// Motor control functions
void moveForward() {
  // Left motors forward
  digitalWrite(MOTOR_LEFT_IN1, HIGH);
  digitalWrite(MOTOR_LEFT_IN2, LOW);
  // Right motors forward
  digitalWrite(MOTOR_RIGHT_IN1, HIGH);
  digitalWrite(MOTOR_RIGHT_IN2, LOW);
  Serial.println("Moving Forward");
}

void moveBackward() {
  // Left motors backward
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  digitalWrite(MOTOR_LEFT_IN2, HIGH);
  // Right motors backward
  digitalWrite(MOTOR_RIGHT_IN1, LOW);
  digitalWrite(MOTOR_RIGHT_IN2, HIGH);
  Serial.println("Moving Backward");
}

void turnLeft() {
  // Left motors backward, Right motors forward
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  digitalWrite(MOTOR_LEFT_IN2, HIGH);
  digitalWrite(MOTOR_RIGHT_IN1, HIGH);
  digitalWrite(MOTOR_RIGHT_IN2, LOW);
  Serial.println("Turning Left");
}

void turnRight() {
  // Left motors forward, Right motors backward
  digitalWrite(MOTOR_LEFT_IN1, HIGH);
  digitalWrite(MOTOR_LEFT_IN2, LOW);
  digitalWrite(MOTOR_RIGHT_IN1, LOW);
  digitalWrite(MOTOR_RIGHT_IN2, HIGH);
  Serial.println("Turning Right");
}

void stopCar() {
  // Stop all motors
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  digitalWrite(MOTOR_LEFT_IN2, LOW);
  digitalWrite(MOTOR_RIGHT_IN1, LOW);
  digitalWrite(MOTOR_RIGHT_IN2, LOW);
  Serial.println("Car Stopped");
}