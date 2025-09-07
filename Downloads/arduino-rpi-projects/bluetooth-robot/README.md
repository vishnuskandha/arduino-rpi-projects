# Bluetooth Robot

Control a small robot over Bluetooth using an Arduino and a phone app.

## Components
- Arduino Uno/Nano
- Motor driver (L298N or similar)
- HC-05/HC-06 Bluetooth module
- 2x DC motors, chassis, wheels, battery pack

## Arduino
Code in rduino/bt_robot.ino.

## Run (example)
- Pair phone with HC-05 (PIN 1234/0000)
- Use a Bluetooth terminal/joystick app to send F, B, L, R, S

## Wiring
- Bluetooth TX->RX, RX->TX, VCC->5V, GND->GND
- Motor driver IN pins to Arduino D pins; power driver from battery

## Tested hardware
- Arduino Uno/Nano
- HC-05/HC-06 Bluetooth module
- L298N motor driver, 2x DC motors
- Battery pack

## Circuit mapping
- Motor driver IN pins -> Arduino D pins per sketch
- Bluetooth: RX<-TX, TX->RX, VCC->5V, GND->GND
