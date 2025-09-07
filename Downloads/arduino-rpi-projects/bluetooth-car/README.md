# Bluetooth Car (Controller + Receiver)

This project combines both the Bluetooth joystick controller (transmitter) and the Bluetooth car (receiver). Use two Arduinos and two Bluetooth modules (e.g., HC-05/06).

## Layout
- rduino/joystick_controller.ino — Reads analog joystick and sends movement commands over Bluetooth at 38400 baud.
- rduino/car_receiver.ino — Receives commands over Bluetooth at 38400 baud and drives motors via L293D/L298N.

## Wiring (Receiver)
- Motor driver IN pins to Arduino D4–D7 (per sketch).
- Optional LED/Relay on D8.
- Bluetooth: RX<-TX, TX->RX, VCC->5V, GND->GND.

## Wiring (Controller)
- Joystick VRx->A0, VRy->A1, SW->D7 (pull-up).
- Bluetooth: RX<-TX, TX->RX, VCC->5V, GND->GND.

## Pairing & Baud
- Set both HC-05/06 modules to 38400 baud or change both sketches to 9600.
- Pair controller module with receiver module, then power both boards.

## Protocol
- Controller sends: orward|backward|left|right|stop (newline-terminated).
- Receiver also accepts single-letter aliases: F|B|L|R|S and on|off for D8.

## Tested hardware
- 2x Arduino Uno/Nano
- 2x HC-05/HC-06 Bluetooth modules
- L293D/L298N motor driver, 2x DC motors, chassis
- Dual-axis joystick module
- 7.4–12 V battery for motors

## Circuit mapping
- Receiver: IN1..IN4 -> D4,D5,D6,D7; optional LED/Relay -> D8
- Receiver BT: RX<-TX, TX->RX, VCC->5V, GND->GND
- Controller: VRx->A0, VRy->A1, SW->D7 (INPUT_PULLUP)
- Controller BT: RX<-TX, TX->RX, VCC->5V, GND->GND
