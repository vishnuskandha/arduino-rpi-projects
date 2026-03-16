# ESP32 Air Quality Monitor with Web Dashboard

ESP32 reads MQ-135 gas sensor and DHT22 temperature/humidity, then serves a web page displaying real-time values and a simple history chart.

## 🎯 Features
- WiFi hotspot + station mode (connects to your router)
- Onboard web server with live readings
- Simple chart of recent history (kept in RAM)
- No external dependencies — runs standalone

## 🛠️ Hardware Required
- ESP32 DevKit V1
- MQ-135 gas sensor (air quality)
- DHT22 temperature & humidity sensor
- Breadboard & jumper wires

## 🔌 Wiring

### MQ-135
- VCC → 5V (or 3.3V if your module supports)
- AOUT → Pin 34 (ADC1)
- GND → GND

### DHT22
- VCC → 5V
- DATA → Pin 4 (with 10kΩ pull-up to 5V)
- GND → GND

## 📜 Arduino Code

See `arduino/air_quality.ino`.

### Configuration
Set WiFi credentials:
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

Web server runs on port 80. Access via `http://<esp32-ip>`.

### Web UI
- Auto-refreshes values every 2 seconds via AJAX
- Displays current AQI (approximate from MQ-135 ppm), temperature, humidity
- Line chart of last 30 samples

## 📂 Project Structure
```
esp32-air-quality-monitor/
├── arduino/
│   └── air_quality.ino
└── README.md
```

## 📄 License
MIT
