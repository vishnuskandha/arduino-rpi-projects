#include <Servo.h>

#define PAN_SERVO_PIN 9
#define TILT_SERVO_PIN 3
#define RELAY_PIN 13   // Fire extinguisher solenoid

#define BAUD_RATE 9600

Servo panServo, tiltServo;

// Servo positions
volatile int currentPan = 90;
volatile int currentTilt = 90;
volatile int targetPan = 90;
volatile int targetTilt = 90;

// PD parameters
const float KP = 0.6;
const float KD = 0.15;
const int MAX_STEP = 8;

// Timing
unsigned long lastSerialMillis = 0;
const unsigned long TIMEOUT_MS = 3000;
unsigned long lastMoveMillis = 0;
const unsigned long MOVE_INTERVAL_MS = 20;

// Fire detection
volatile bool fireDetected = false;

// Relay pulse control
unsigned long relayOnMillis = 0;
const unsigned long RELAY_PULSE_MS = 100; // 100 ms pulse

// Helpers
int clampAngle(int v) {
  return constrain(v, 0, 180);
}

void setup() {
  Serial.begin(BAUD_RATE);
  panServo.attach(PAN_SERVO_PIN);
  tiltServo.attach(TILT_SERVO_PIN);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  currentPan = targetPan = 90;
  currentTilt = targetTilt = 90;
  panServo.write(currentPan);
  tiltServo.write(currentTilt);

  Serial.println("Arduino: Fire Servo Ready");
}

void loop() {
  // ------------------ Serial input ------------------
  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    static String serialBuf = "";
    if (c == '\n' || c == '\r') {
      if (serialBuf.length() > 0) {
        processCommand(serialBuf);
        serialBuf = "";
      }
    } else {
      serialBuf += c;
    }
    lastSerialMillis = millis();
  }

  // ------------------ Timeout safe mode ------------------
  if (millis() - lastSerialMillis > TIMEOUT_MS) {
    targetPan = 90;
    targetTilt = 90;
    fireDetected = false;
  }

  // ------------------ PD servo move ------------------
  if (millis() - lastMoveMillis >= MOVE_INTERVAL_MS) {
    lastMoveMillis = millis();
    pdMove();
  }

  // ------------------ Relay pulse handling ------------------
  if (fireDetected) {
    if (millis() - relayOnMillis >= RELAY_PULSE_MS) {
      digitalWrite(RELAY_PIN, LOW); // Turn off after pulse
      fireDetected = false;          // wait for next detection
    }
  }
}

// PD-based smooth motion
void pdMove() {
  static float prevErrorPan = 0;
  static float prevErrorTilt = 0;

  float errorPan = targetPan - currentPan;
  float errorTilt = targetTilt - currentTilt;

  float derivPan = errorPan - prevErrorPan;
  float derivTilt = errorTilt - prevErrorTilt;

  int stepPan = constrain((int)(KP * errorPan + KD * derivPan), -MAX_STEP, MAX_STEP);
  int stepTilt = constrain((int)(KP * errorTilt + KD * derivTilt), -MAX_STEP, MAX_STEP);

  currentPan = clampAngle(currentPan + stepPan);
  currentTilt = clampAngle(currentTilt + stepTilt);

  panServo.write(currentPan);
  tiltServo.write(currentTilt);

  prevErrorPan = errorPan;
  prevErrorTilt = errorTilt;
}

// Process commands from Raspberry Pi
void processCommand(String cmd) {
  cmd.trim();
  if (cmd.length() == 0) return;

  if (cmd.equalsIgnoreCase("FIRE_DETECTED")) {
    fireDetected = true;
    digitalWrite(RELAY_PIN, HIGH);  // Activate valve for pulse
    relayOnMillis = millis();        // start pulse timer
    Serial.println("ACK:FIRE_ON");
    return;
  }

  if (cmd.equalsIgnoreCase("NO_FIRE")) {
    fireDetected = false;
    digitalWrite(RELAY_PIN, LOW);    // deactivate
    Serial.println("ACK:FIRE_OFF");
    return;
  }

  // Parse pan,tilt
  int comma = cmd.indexOf(',');
  if (comma > 0) {
    int p = cmd.substring(0, comma).toInt();
    int t = cmd.substring(comma + 1).toInt();
    if (p >= 0 && p <= 180 && t >= 0 && t <= 180) {
      targetPan = p;
      targetTilt = t;
      Serial.print("ACK:SET:");
      Serial.print(targetPan);
      Serial.print(",");
      Serial.println(targetTilt);
    }
  }
}
