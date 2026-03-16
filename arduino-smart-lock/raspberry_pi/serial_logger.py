#!/usr/bin/env python3
"""
Serial logger for Arduino Smart Lock.
Reads lines like: LOG,YYYY-MM-DD HH:MM:SS,PIN,1234
or: LOG,YYYY-MM-DD HH:MM:SS,RFID,0xDEADBEEF
"""

import sys
import serial
import csv
import os
from datetime import datetime

SERIAL_PORT = sys.argv[1] if len(sys.argv) > 1 else '/dev/ttyACM0'
BAUD = 115200
LOG_FILE = 'access_log.csv'

def ensure_header():
    if not os.path.isfile(LOG_FILE):
        with open(LOG_FILE, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow(['timestamp', 'method', 'identifier'])

def main():
    ensure_header()
    ser = serial.Serial(SERIAL_PORT, BAUD, timeout=1)
    print(f"[logger] Listening on {SERIAL_PORT}...")
    while True:
        try:
            line = ser.readline().decode('utf-8').strip()
            if not line.startswith('LOG,'):
                continue
            parts = line.split(',)
            if len(parts) < 4:
                continue
            method = parts[1]  # PIN or RFID
            identifier = parts[2]
            now = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            with open(LOG_FILE, 'a', newline='') as f:
                writer = csv.writer(f)
                writer.writerow([now, method, identifier])
            print(f"[logger] {now} {method} {identifier}")
        except Exception as e:
            print(f"[error] {e}")

if __name__ == '__main__':
    main()
