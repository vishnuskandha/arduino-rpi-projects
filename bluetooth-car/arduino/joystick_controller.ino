#include <SoftwareSerial.h>

// Configure SoftwareSerial for Bluetooth communication
SoftwareSerial BT(2, 3); // RX, TX for BLE module

// Joystick analog input pins
#define JOY_VRX A0 // Analog pin for X-axis
#define JOY_VRY A1 // Analog pin for Y-axis

// Optional joystick button pin
#define JOY_BTN 7

// --- Calibration Values ---
// These are crucial. You'll need to adjust them based on your specific joystick.
// Read your joystick's resting values using the debug code and enter them here.
#define CENTER_X 512 // Center value for X-axis (typically around 512)
#define CENTER_Y 512 // Center value for Y-axis (typically around 512)
#define DEADZONE 100 // Area around the center where no movement is detected (prevents drift)
#define MOVEMENT_THRESHOLD 200 // How far the joystick must move from the deadzone to trigger an action

// --- State Variables ---
String lastSentCommand = ""; // To avoid sending redundant commands

void setup() {
  // Initialize Serial communication at 38400 baud
  Serial.begin(38400);
  // Initialize Bluetooth serial communication at 38400 baud
  BT.begin(38400);

  // Set the button pin as an input with an internal pull-up resistor
  pinMode(JOY_BTN, INPUT_PULLUP);

  Serial.println("Joystick Controller Ready!");
  Serial.println("Calibrating... Please keep joystick centered.");
  delay(1500); // Give a moment for setup

  // Initial calibration check can be added here if needed, but the loop handles it.
  Serial.println("Calibration complete. Ready to send commands.");
}

void loop() {
  // Read raw analog values from the joystick
  int xVal = analogRead(JOY_VRX);
  int yVal = analogRead(JOY_VRY);
  bool buttonPressed = digitalRead(JOY_BTN) == LOW; // Button is LOW when pressed

  // Calculate deviation from the center for X and Y axes
  int xDiff = xVal - CENTER_X;
  int yDiff = yVal - CENTER_Y;

  String currentCommand = "stop"; // Default command is 'stop'

  // --- Determine Movement Command ---

  // Check if the joystick is outside the deadzone for any axis
  if (abs(xDiff) < DEADZONE && abs(yDiff) < DEADZONE) {
    // Joystick is in the neutral/deadzone
    currentCommand = "stop";
  } else if (yDiff > MOVEMENT_THRESHOLD) {
    // Joystick pushed forward (up on the axis)
    currentCommand = "forward";
  } else if (yDiff < -MOVEMENT_THRESHOLD) {
    // Joystick pulled backward (down on the axis)
    currentCommand = "backward";
  } else if (xDiff < -MOVEMENT_THRESHOLD) {
    // Joystick pushed left
    currentCommand = "left";
  } else if (xDiff > MOVEMENT_THRESHOLD) {
    // Joystick pushed right
    currentCommand = "right";
  }
  // If it's not neutral but doesn't meet a specific threshold, it might be a slight drift.
  // We default to 'stop' if no clear direction is detected.

  // --- Send Command Only if it Changes ---
  if (currentCommand != lastSentCommand) {
    sendCommand(currentCommand);
    lastSentCommand = currentCommand; // Update the last sent command
  }

  // --- Handle Button Press ---
  if (buttonPressed) {
    // Send "on" command when button is pressed
    // We send it directly without checking lastSentCommand to ensure it's registered
    Serial.println("Button pressed - Sending ON command.");
    BT.print("on\n"); // Send "on" followed by a newline
    // Add a small delay to prevent rapid re-triggering and debounce
    delay(300);
  }

  // Small delay to prevent overwhelming the serial buffer or Bluetooth module
  delay(100);
}

// Function to send command via Bluetooth and print to Serial Monitor
void sendCommand(String command) {
  BT.print(command);
  BT.print('\n'); // CRITICAL: Append a newline character
  Serial.print("Sent: ");
  Serial.println(command);
}