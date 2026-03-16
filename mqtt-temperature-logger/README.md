# MQTT Temperature/Humidity Logger

Arduino (DHT22) publishes sensor data via MQTT. Raspberry Pi subscribes, logs to CSV, and optionally serves a simple live chart.

## 🎯 Features
- Wireless sensor data transmission (no wires beyond power)
- CSV logging on Raspberry Pi with timestamps
- Optional live web dashboard
- Uses lightweight MQTT (Mosquitto)

## 🛠️ Hardware Required

### Arduino Side
- Arduino Uno/Nano
- DHT22 temperature & humidity sensor
- Jumper wires

### Raspberry Pi Side
- Raspberry Pi 3/4
- Mosquitto MQTT broker (installable)
- Optional: Python `flask` for dashboard

## 🔌 Wiring (Arduino + DHT22)
- VCC → 5V
- DATA → Pin 2 (with 10kΩ pull-up resistor to 5V)
- GND → GND

## 📜 Arduino Code

See `arduino/dht22_mqtt.ino`.

**Configuration:** Set WiFi SSID/password and MQTT broker IP (Raspberry Pi's IP). Publishes to topic `sensor/dht22` every 5 seconds.

```cpp
// Example payload: {"temp":23.5,"hum":68.2}
```

## 📜 Raspberry Pi Code

See `raspberry_pi/mqtt_logger.py` and `raspberry_pi/dashboard.py` (optional).

### Setup on Pi
```bash
sudo apt update
sudo apt install mosquitto mosquitto-clients python3-pip
pip3 install paho-mqtt flask
```

Run logger:
```bash
python3 mqtt_logger.py
```

Run dashboard (optional):
```bash
python3 dashboard.py
```
Then open `http://localhost:5000`.

## 📂 Project Structure
```
mqtt-temperature-logger/
├── arduino/
│   └── dht22_mqtt.ino
├── raspberry_pi/
│   ├── mqtt_logger.py
│   └── dashboard.py
└── README.md
```

## 📄 License
MIT
