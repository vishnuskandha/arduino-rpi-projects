# Servo Camera + Detection

Pan/tilt camera with optional detection.

## Components
- Arduino (for pan/tilt) and 2x SG90 micro servos
- Raspberry Pi with camera module

## Arduino
rduino/camera.ino

## Raspberry Pi
- aspberry_pi/servo_camera.py
- aspberry_pi/detection_cam.py

## Run (Pi)
- Enable camera, install dependencies in a venv
- Run the script and view stream/detections

## Tested hardware
- Arduino Uno/Nano
- 2x SG90 micro servos
- Relay module (optional)
- Raspberry Pi + camera (optional)

## Circuit mapping
- Arduino: PAN->D9, TILT->D3, Relay->D13
- Raspberry Pi: CSI camera; USB serial to Arduino
