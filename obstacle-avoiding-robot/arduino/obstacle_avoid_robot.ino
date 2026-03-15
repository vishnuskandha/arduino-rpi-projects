const int trigPin = 9;
const int echoPin = 10;
const int motorA1 = 8;
const int motorA2 = 7;
const int motorB1 = 6;
const int motorB2 = 5;
const int enableA = 3;
const int enableB = 2;

const long MIN_DISTANCE_CM = 20;
const int MOTOR_SPEED = 180;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);

  analogWrite(enableA, MOTOR_SPEED);
  analogWrite(enableB, MOTOR_SPEED);

  Serial.begin(9600);
}

void loop() {
  long distance = getDistance();

  if (distance > MIN_DISTANCE_CM || distance == 0) {
    moveForward();
  } else {
    stopMotors();
    delay(200);
    moveBackward();
    delay(300);
    stopMotors();
    delay(100);
    turnRight();
    delay(400);
    stopMotors();
    delay(100);
  }

  delay(50);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  long distance = duration * 0.0343 / 2;
  return distance;
}

void moveForward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void moveBackward() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void turnRight() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void turnLeft() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void stopMotors() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
