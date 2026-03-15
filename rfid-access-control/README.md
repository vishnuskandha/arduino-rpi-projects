# RFID Access Control System

A simple access control system using an RFID reader (RC522) and a servo lock to control entry.

## 🎯 Features
- Read RFID tags (Mifare Classic)
- Compare against a whitelist
- Unlock servo on authorized tag
- Serial feedback for debugging

## 🛠️ Hardware Required
- Arduino Uno
- MFRC522 RFID Reader Module
- RFID Tags/Cards (Mifare Classic)
- Servo Motor (e.g., SG90 or MG996R)
- LED (optional, for status)
- Resistor (220Ω for LED)
- Breadboard & jumper wires

## 🔌 Wiring

### MFRC522 (SPI)
- SDA (SS) → Pin 10
- SCK → Pin 13
- MOSI → Pin 11
- MISO → Pin 12
- IRQ → Not connected
- RST → Pin 8
- 3.3V → 3.3V
- GND → GND

### Servo
- Signal → Pin 9
- VCC → 5V
- GND → GND

### LED (optional)
- Anode → Pin 7 via 220Ω resistor
- Cathode → GND

## 📜 Code

See `arduino/rfid_access_control.ino`.

### Setup
- Replace `UNAUTHORIZED_UID[]` with the UID of your authorized tag(s) in decimal.
- You can print the tag UID to Serial when scanning an unknown tag to capture it.

## 📂 Project Structure
```
rfid-access-control/
├── arduino/
│   └── rfid_access_control.ino
└── README.md
```

## 📄 License
MIT
