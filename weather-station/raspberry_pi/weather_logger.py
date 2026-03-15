import serial
import csv
from datetime import datetime
import os

SERIAL_PORT = '/dev/ttyACM0'  # change as needed (/dev/ttyUSB0, COM3, etc.)
BAUD_RATE = 9600
LOG_FILE = 'weather_log.csv'

def ensure_csv_header():
    if not os.path.exists(LOG_FILE):
        with open(LOG_FILE, mode='w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow(['timestamp', 'elapsed_ms', 'temp_c', 'humidity_pct', 'pressure_hpa', 'air_quality'])

def main():
    ensure_csv_header()
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    while True:
        line = ser.readline().decode('utf-8').strip()
        if line and line.startswith('timestamp'):  # skip header lines if any
            continue
        if ',' in line:
            parts = line.split(',')
            if len(parts) == 5:
                now = datetime.now().isoformat(timespec='seconds')
                row = [now] + parts
                with open(LOG_FILE, mode='a', newline='') as f:
                    writer = csv.writer(f)
                    writer.writerow(row)
                print(f"Logged: {row}")

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("\nStopped.")
