# Arduino & Raspberry Pi Projects

[![CI](https://github.com/vishnuskandha/arduino-rpi-projects/actions/workflows/ci.yml/badge.svg)](https://github.com/vishnuskandha/arduino-rpi-projects/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A collection of 19 Arduino, ESP32, and Raspberry Pi projects covering IoT, robotics, and automation. Each project lives in its own folder with a README, an `arduino/` subfolder for sketches (`.ino`), and/or a `raspberry_pi/` subfolder for Python scripts (`.py`).

## Projects

| Project | Description | Arduino/ESP32 | Raspberry Pi |
|---------|-------------|---------------|--------------|
| [arduino-smart-lock](arduino-smart-lock/) | Keypad PIN and RFID door lock with serial event logging to a Pi | Yes | Yes |
| [bluetooth-car](bluetooth-car/) | Bluetooth joystick controller and car receiver (two Arduinos, HC-05/06) | Yes | No |
| [bluetooth-robot](bluetooth-robot/) | Arduino robot driven by serial commands over a Bluetooth module | Yes | No |
| [esp32-air-quality-monitor](esp32-air-quality-monitor/) | ESP32 reads MQ-135 + DHT22 and serves a live web dashboard | Yes | No |
| [esp32-web-server-ota](esp32-web-server-ota/) | ESP32 soft-AP web server with GPIO control and OTA updates | Yes | No |
| [fire-detection](fire-detection/) | Flame-sensor based fire detection with Arduino | Yes | No |
| [fire-detection-suppression](fire-detection-suppression/) | Pi (OpenCV) fire detection driving Arduino servo/relay suppression | Yes | Yes |
| [ir-remote](ir-remote/) | IR receiver that reacts to remote button presses | Yes | No |
| [led-blink-rpi](led-blink-rpi/) | Blink an LED from a Raspberry Pi GPIO | No | Yes |
| [lora-esp32](lora-esp32/) | Long-range LoRa sender/receiver example with ESP32 + SX127x | Yes | No |
| [mqtt-temperature-logger](mqtt-temperature-logger/) | DHT22 to MQTT on Arduino, logged to CSV and charted on a Pi | Yes | Yes |
| [obstacle-avoiding-robot](obstacle-avoiding-robot/) | Robot that dodges obstacles using an HC-SR04 ultrasonic sensor | Yes | No |
| [pi-fire-tracker](pi-fire-tracker/) | Camera-based hotspot/fire detection on a Raspberry Pi | No | Yes |
| [pir-motion-light](pir-motion-light/) | Motion-activated light with PIR, Arduino or Pi | Yes | Yes |
| [raspberry-pi-motion-detection](raspberry-pi-motion-detection/) | Motion-triggered camera with Telegram image alerts | No | Yes |
| [rfid-access-control](rfid-access-control/) | RC522 RFID reader driving a servo lock | Yes | No |
| [servo-camera](servo-camera/) | Pan/tilt servo camera with optional OpenCV detection | Yes | Yes |
| [ultrasonic](ultrasonic/) | HC-SR04 ultrasonic distance measurement | Yes | No |
| [weather-station](weather-station/) | Multi-sensor weather station with Pi logging/dashboard | Yes | Yes |

## Quick Start

1. Clone the repository:

   ```bash
   git clone https://github.com/vishnuskandha/arduino-rpi-projects.git
   cd arduino-rpi-projects
   ```

2. Pick a project from the table above and open its folder.

3. Read the project's `README.md` for wiring, libraries, and setup.

4. Arduino sketches: open the `.ino` in the Arduino IDE, install the libraries listed in the project README, and upload.

5. Raspberry Pi scripts: install the Python dependencies listed in the project README (for example `pip install -r requirements.txt` if provided) and run the script with `python3 script.py`.

## Repository Layout

```
arduino-rpi-projects/
├── <project>/
│   ├── arduino/          # Arduino/ESP32 sketches (.ino)
│   ├── raspberry_pi/     # Python scripts (.py)
│   └── README.md         # Project documentation
├── .github/workflows/    # CI checks
└── README.md
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## Security

See [SECURITY.md](SECURITY.md) for how to report vulnerabilities.

## License

MIT, see [LICENSE](LICENSE).
