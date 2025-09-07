# LoRa ESP32 Sender/Receiver

ESP32-based LoRa communication examples.

## Components
- 2x ESP32 + LoRa modules (SX127x)
- Antennas, jumpers

## Arduino
- Sender: rduino/transmitter.ino
- Receiver: rduino/receiver.ino

## Run
- Install Arduino core for ESP32 and LoRa libraries
- Flash both boards and monitor Serial

## Tested hardware
- 2x ESP32 dev boards
- 2x SX127x LoRa modules + antennas

## Circuit mapping
- Wire LoRa to ESP32 SPI (SCK,MISO,MOSI), NSS/CS, RST, DIO0
- Pins depend on your board/module; match library examples
