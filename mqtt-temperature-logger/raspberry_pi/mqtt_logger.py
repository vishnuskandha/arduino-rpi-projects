#!/usr/bin/env python3
"""
MQTT Temperature/Humidity Logger
Subscribes to sensor topic and logs readings to CSV.
"""

import os
import csv
import time
import datetime
import paho.mqtt.client as mqtt

MQTT_BROKER = "localhost"  # or Pi's IP if running elsewhere
MQTT_PORT = 1883
MQTT_TOPIC = "sensor/dht22"

LOG_FILE = "sensor_log.csv"

def on_connect(client, userdata, flags, rc):
    print(f"[mqtt] Connected with result code {rc}")
    client.subscribe(MQTT_TOPIC)

def on_message(client, userdata, msg):
    try:
        payload = msg.payload.decode('utf-8')
        # Expected: {"temp":23.5,"hum":68.2}
        import json
        data = json.loads(payload)
        temp = data.get('temp')
        hum = data.get('hum')
        timestamp = datetime.datetime.now().isoformat(timespec='seconds')
        file_exists = os.path.isfile(LOG_FILE)
        with open(LOG_FILE, 'a', newline='') as f:
            writer = csv.writer(f)
            if not file_exists:
                writer.writerow(['timestamp', 'temperature_c', 'humidity_pct'])
            writer.writerow([timestamp, temp, hum])
        print(f"[log] {timestamp} temp={temp}°C hum={hum}%")
    except Exception as e:
        print(f"[mqtt] Error processing message: {e}")

def main():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    client.loop_forever()

if __name__ == '__main__':
    main()
