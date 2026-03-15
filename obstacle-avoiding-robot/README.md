# Obstacle Avoiding Robot

A simple robot that navigates by detecting obstacles using an ultrasonic sensor and automatically changing direction.

## 🎯 Features
- Real-time distance measurement (HC-SR04)
- Automatic steering when obstacles detected
- Smooth movement with motor driver (L298N)
- Adjustable detection threshold

## 🛠️ Hardware Required
- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- L298N Motor Driver
- 2x DC Motors (with wheels)
- Chassis kit
- Battery pack (6-12V)
- Jumper wires

## 🔌 Wiring

### Ultrasonic Sensor (HC-SR04)
- VCC → 5V
- Trig → Pin 9
- Echo → Pin 10
- GND → GND

### Motor Driver (L298N)
- IN1 → Pin 8
- IN2 → Pin 7
- IN3 → Pin 6
- IN4 → Pin 5
- ENA → Pin 3 (PWM)
- ENB → Pin 2 (PWM)
- 12V → Battery + (if using 12V)
- GND → Battery - & Arduino GND (common ground)

Motor connections to L298N outputs as per your motor orientation.

## 📜 Code

See `arduino/obstacle_avoid_robot.ino` for the full sketch.

### How it works
1. Measure distance with ultrasonic sensor.
2. If obstacle detected within threshold (e.g., 20 cm), stop.
3. Reverse briefly, then turn in a random or predefined direction.
4. Continue forward until next obstacle.

## 🔧 Calibration
- Adjust `MIN_DISTANCE_CM` to change the safe distance.
- Tweak motor speeds by modifying the PWM values (0-255).

## 📂 Project Structure
```
obstacle-avoiding-robot/
├── arduino/
│   └── obstacle_avoid_robot.ino
└── README.md
```

## 🤝 Contributing
Feel free to improve the logic or add features like line-following or remote control.

## 📄 License
MIT
