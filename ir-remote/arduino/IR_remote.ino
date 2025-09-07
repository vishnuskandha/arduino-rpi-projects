const int pirPin = 2;

void setup() {
  Serial.begin(9600);  // Serial to Raspberry Pi
  pinMode(pirPin, INPUT);
}

void loop() {
  int motion = digitalRead(pirPin);
  if (motion == HIGH) {
    Serial.println("MOTION"); // Send motion detected
    delay(1000); // Debounce / avoid flooding
  }
  delay(100);
}
