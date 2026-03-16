# ESP32 Web Server + GPIO Control + OTA

A compact ESP32 project that creates a WiFi access point with a built-in web server. Control GPIO pins, read sensor values, and update firmware over-the-air (OTA) without USB.

## 🎯 Features
- Soft AP hotspot (no external router needed)
- Web interface to toggle GPIO pins and read ADC
- OTA firmware update via upload form
- RESTful endpoints for automation
- Simple JSON responses

## 🛠️ Hardware Required
- ESP32 DevKit V1
- Optional: LEDs, buttons, sensors for GPIO demo

## 🔌 Wiring
No external wiring required unless you attach devices to GPIO pins.
Recommended test:
- LED + resistor on GPIO 2 (built-in LED on many boards)

## 📜 Arduino Code

See `arduino/esp32_web_server.ino`.

### Configuration
Change these in the sketch:
```cpp
const char* apSSID = "ESP32-AP";
const char* apPassword = "12345678"; // min 8 chars
```

### OTA Update
1. In Arduino IDE: `Sketch > Export Compiled Binary` (produces .bin)
2. Copy `.bin` to a computer on the ESP32's WiFi network.
3. Visit `http://192.168.4.1/update` and upload the binary.
4. ESP32 restarts with new firmware.

### API Endpoints
- `GET /` — Web UI
- `GET /gpio?pin=<num>` — read pin state
- `POST /gpio?pin=<num>&state=<0|1>` — set pin output
- `POST /update` — OTA firmware upload
- `GET /status` — JSON with free heap, uptime

## 📂 Project Structure
```
esp32-web-server-ota/
├── arduino/
│   └── esp32_web_server.ino
└── README.md
```

## 🚀 Quick Start
1. Open Arduino IDE, select your ESP32 board.
2. Install required libraries: `WiFi`, `WebServer`, `Update`, `ArduinoJson` (if used).
3. Upload the sketch.
4. Connect to the `ESP32-AP` WiFi network (password: `12345678`).
5. Open `http://192.168.4.1` in a browser.

## 📄 License
MIT
