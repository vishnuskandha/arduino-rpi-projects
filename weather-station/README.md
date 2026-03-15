# Weather Station

A simple weather station using an Arduino with multiple sensors and a Raspberry Pi dashboard for logging and visualization.

## 🎯 Features
- Measure temperature, humidity (DHT22)
- Measure barometric pressure (BMP280)
- Measure air quality (MQ-135)
- Log data locally on Raspberry Pi
- Optional: serve a web dashboard

## 🛠️ Hardware Required

### Arduino Side
- Arduino Uno
- DHT22 (temperature & humidity)
- BMP280 (pressure)
- MQ-135 (air quality)
- Resistors (10kΩ for DHT22, others per sensor)
- Breadboard & wires

### Raspberry Pi Side
- Raspberry Pi 3/4
- MicroSD with OS
- Network connection
- (Optional) Display or web browser

## 🔌 Wiring

### DHT22
- VCC → 5V
- DATA → Pin 2
- GND → GND
- Pull-up 10kΩ between VCC and DATA

### BMP280 (I2C)
- VCC → 3.3V
- GND → GND
- SCL → Pin A5 (Arduino) / GPIO3 (Pi) if using Pi directly
- SDA → Pin A4 (Arduino) / GPIO2 (Pi)
- (In this setup, Arduino sends data via Serial to Pi)

### MQ-135
- VCC → 5V
- AOUT → Pin A0
- GND → GND

## 🖥️ Raspberry Pi Data Logger

Python script (`raspberry_pi/weather_logger.py`) reads Serial from Arduino and writes to a CSV file. Optionally, a Flask app can serve a simple chart.

## 📜 Arduino Code
See `arduino/weather_station.ino`.

## 📜 Raspberry Pi Code
See `raspberry_pi/weather_logger.py`.

## 📂 Project Structure
```
weather-station/
├── arduino/
│   └── weather_station.ino
├── raspberry_pi/
│   └── weather_logger.py
└── README.md
```

## 📄 License
MIT
