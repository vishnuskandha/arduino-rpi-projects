# Arduino Smart Lock with Keypad + RFID + Raspberry Pi Logging

A dual-authentication door lock: unlock with either a 4-digit PIN or an RFID card. Access events are logged to a Raspberry Pi via serial (USB).

## 🎯 Features
- Keypad entry (4-digit PIN)
- RFID tag/card entry (RC522)
- Servo lock actuator
- Event logging to Pi (timestamp, method, ID)
- Simple status LEDs

## 🛠️ Hardware Required

### Arduino Side
- Arduino Uno/Nano
- 4x4 Keypad
- MFRC522 RFID-RC522 module
- Servo motor (SG90)
- LEDs: red (denied), green (granted) with 220Ω resistors
- Buzzer (optional)

### Raspberry Pi Side
- Any model with USB port
- Serial connection via USB cable to Arduino

## 🔌 Wiring

### Keypad (4x4)
- Rows: Pins 5,6,7,8
- Columns: Pins 9,10,11,12

### RFID-RC522 (SPI)
- SDA (SS) → Pin 10
- SCK → Pin 13
- MOSI → Pin 11
- MISO → Pin 12
- RST → Pin 9
- 3.3V → 3.3V
- GND → GND

### Servo
- Signal → Pin 3
- VCC → 5V
- GND → GND

### LEDs
- Green (granted) → Pin 2 via resistor
- Red (denied) → Pin A0 via resistor

## 📜 Arduino Code

See `arduino/smart_lock.ino`.

**Setup:** Define your PIN code and authorized RFID UID(s) in the sketch.

**Serial logging:** On access event, Arduino sends a line like:
```
LOG,YYYY-MM-DD HH:MM:SS,PIN,1234
LOG,YYYY-MM-DD HH:MM:SS,RFID,0xDEADBEEF
```
Raspberry Pi reads these lines and appends to `access_log.csv`.

## 📜 Raspberry Pi Code

See `raspberry_pi/serial_logger.py`.

### Usage
```bash
python3 serial_logger.py /dev/ttyACM0
```
(Adjust serial port as needed; on Windows use `COM3`.)

## 📂 Project Structure
```
arduino-smart-lock/
├── arduino/
│   └── smart_lock.ino
├── raspberry_pi/
│   └── serial_logger.py
└── README.md
```

## 📄 License
MIT
