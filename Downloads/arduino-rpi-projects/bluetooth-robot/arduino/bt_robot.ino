char command;
int motor1 = 3;
int motor2 = 4;
int motor3 = 5;
int motor4 = 6;

void setup() {
  Serial.begin(9600);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    command = Serial.read();
    if (command == 'F') { digitalWrite(motor1, HIGH); digitalWrite(motor2, LOW); digitalWrite(motor3, HIGH); digitalWrite(motor4, LOW); }
    if (command == 'B') { digitalWrite(motor1, LOW); digitalWrite(motor2, HIGH); digitalWrite(motor3, LOW); digitalWrite(motor4, HIGH); }
    if (command == 'L') { digitalWrite(motor1, LOW); digitalWrite(motor2, HIGH); digitalWrite(motor3, HIGH); digitalWrite(motor4, LOW); }
    if (command == 'R') { digitalWrite(motor1, HIGH); digitalWrite(motor2, LOW); digitalWrite(motor3, LOW); digitalWrite(motor4, HIGH); }
    if (command == 'S') { digitalWrite(motor1, LOW); digitalWrite(motor2, LOW); digitalWrite(motor3, LOW); digitalWrite(motor4, LOW); }
  }
}
