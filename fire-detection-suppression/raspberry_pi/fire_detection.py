import cv2
import numpy as np
import serial
import time

# Notes:
# - This script uses simple HSV color thresholding as a lightweight stand-in for fire detection.
# - It sends FIRE_DETECTED / NO_FIRE messages to the Arduino over serial.
# - The Arduino sketch `arduino/servo_relay_control.ino` listens for these messages
#   and handles the relay pulse timing itself.

# Serial port to Arduino (adjust if needed)
ARDUINO_PORT = '/dev/ttyUSB0'  # e.g., COM6 on Windows
BAUD = 9600

try:
    arduino = serial.Serial(ARDUINO_PORT, BAUD, timeout=1)
    time.sleep(2)
except Exception as e:
    print('Warning: Could not open serial to Arduino:', e)
    arduino = None

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)

# Heuristic HSV thresholds for fire-like colors (tune to environment)
lower1 = np.array([0, 120, 120])
upper1 = np.array([25, 255, 255])

KERNEL = np.ones((5, 5), np.uint8)
AREA_THRESHOLD = 800  # minimum contour area to consider as fire

last_fire_state = False

while True:
    ret, frame = cap.read()
    if not ret:
        break

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, lower1, upper1)
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, KERNEL, iterations=1)
    mask = cv2.morphologyEx(mask, cv2.MORPH_DILATE, KERNEL, iterations=2)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    fire_detected = False
    if contours:
        c = max(contours, key=cv2.contourArea)
        area = cv2.contourArea(c)
        if area > AREA_THRESHOLD:
            x, y, w, h = cv2.boundingRect(c)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
            fire_detected = True

    # Send events to Arduino only on state changes to reduce chatter
    if fire_detected != last_fire_state and arduino is not None:
        try:
            msg = 'FIRE_DETECTED\n' if fire_detected else 'NO_FIRE\n'
            arduino.write(msg.encode())
        except Exception as e:
            print('Serial write error:', e)
    last_fire_state = fire_detected

    # UI
    cv2.imshow('Fire Detection (HSV)', frame)
    cv2.imshow('Mask', mask)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
if arduino is not None:
    arduino.close()
