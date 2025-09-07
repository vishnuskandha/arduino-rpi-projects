// Ultrasonic Sensor HC-SR04 Code
// VCC -> 5V
// GND -> GND
// Trig -> Digital Pin 10
// Echo -> Digital Pin 9

const int trigPin = 10;
const int echoPin = 9;

long duration;
int distance;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.println("Ultrasonic Sensor Ready!");
  Serial.println("Distance measurements will appear below:");
  Serial.println("----------------------------------------");
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters
  // Speed of sound = 343 m/s = 0.0343 cm/microsecond
  // Distance = (time * speed) / 2 (divide by 2 because sound travels to object and back)
  distance = duration * 0.034 / 2;
  
  // Print the distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Optional: Add distance in inches
  float distanceInches = distance * 0.393701;
  Serial.print("Distance: ");
  Serial.print(distanceInches);
  Serial.println(" inches");
  
  Serial.println("----------------------------------------");
  
  // Wait before next measurement
  delay(1000);
}

// Optional: Function to get distance reading (for use in other parts of your code)
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long dur = pulseIn(echoPin, HIGH);
  int dist = dur * 0.034 / 2;
  
  return dist;
}