# Arduino + Raspberry Pi Projects

![License](https://img.shields.io/badge/license-unlicensed-lightgrey)
![Arduino IDE](https://img.shields.io/badge/Arduino%20IDE-2.x-blue)
![Python](https://img.shields.io/badge/Python-3.11%2B-3776AB)

Curated mini-projects for Arduino and Raspberry Pi. Each project has a focused README and direct links to the primary code so you can jump in fast.

## Projects (Quick Links)

| Project | Arduino | Raspberry Pi | What it does |
| --- | --- | --- | --- |
| [bluetooth-car](bluetooth-car/README.md) | [car_receiver.ino](bluetooth-car/arduino/car_receiver.ino), [joystick_controller.ino](bluetooth-car/arduino/joystick_controller.ino) | – | Two-Arduino setup: joystick controller → car receiver via Bluetooth |
| [bluetooth-robot](bluetooth-robot/README.md) | [bt_robot.ino](bluetooth-robot/arduino/bt_robot.ino) | – | Simple Bluetooth-controlled robot (phone app/terminal) |
| [fire-detection](fire-detection/README.md) | [fire_dectection.ino](fire-detection/arduino/fire_dectection.ino) | – | Flame sensor alert with buzzer/LED on Arduino |
| [fire-detection-suppression](fire-detection-suppression/README.md) | [servo_relay_control.ino](fire-detection-suppression/arduino/servo_relay_control.ino) | [fire_detection.py](fire-detection-suppression/raspberry_pi/fire_detection.py) | HSV-based fire detect on Pi, triggers Arduino relay/servo |
| [ir-remote](ir-remote/README.md) | [IR_remote.ino](ir-remote/arduino/IR_remote.ino) | – | Read remote signals and act on buttons |
| [led-blink-rpi](led-blink-rpi/README.md) | – | [led_blink.py](led-blink-rpi/raspberry_pi/led_blink.py) | Blink an LED via GPIO |
| [lora-esp32](lora-esp32/README.md) | [transmitter.ino](lora-esp32/arduino/transmitter.ino), [receiver.ino](lora-esp32/arduino/receiver.ino) | – | ESP32 LoRa TX/RX examples |
| [pi-fire-tracker](pi-fire-tracker/README.md) | – | [pi_fire_tracker.py](pi-fire-tracker/raspberry_pi/pi_fire_tracker.py) | Track hotspots using Pi camera |
| [pir-motion-light](pir-motion-light/README.md) | [pir_led.ino](pir-motion-light/arduino/pir_led.ino) | [pir_light.py](pir-motion-light/raspberry_pi/pir_light.py) | Motion-activated light |
| [servo-camera](servo-camera/README.md) | [camera.ino](servo-camera/arduino/camera.ino) | [servo_camera.py](servo-camera/raspberry_pi/servo_camera.py) | Pan/tilt camera with tracking |
| [ultrasonic](ultrasonic/README.md) | [ultrasonic.ino](ultrasonic/arduino/ultrasonic.ino) | – | HC-SR04 distance measurement |

## Layout

Each project follows:

```
project-name/
├── arduino/             # Arduino sketches (.ino)
├── raspberry_pi/        # Raspberry Pi Python scripts (.py)
└── README.md            # Project description and run instructions
```
