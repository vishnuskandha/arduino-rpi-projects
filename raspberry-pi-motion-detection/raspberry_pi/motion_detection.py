#!/usr/bin/env python3
"""
Motion detection camera with Telegram alerts.
Run on Raspberry Pi with camera module or USB webcam.
"""

import cv2
import time
import os
import datetime
from telegram import Bot
from telegram.error import TelegramError
from dotenv import load_dotenv

load_dotenv()

# --- Configuration ---
TELEGRAM_BOT_TOKEN = os.getenv("TELEGRAM_BOT_TOKEN")
TELEGRAM_CHAT_ID = os.getenv("TELEGRAM_CHAT_ID")
CAMERA_INDEX = 0  # 0 for USB webcam; for Pi camera use Picamera2 (not shown)
SAVE_DIR = "motion_snapshots"
os.makedirs(SAVE_DIR, exist_ok=True)

# Motion detection parameters
MIN_AREA = 500         # minimum contour area to trigger
THRESHOLD = 25         # pixel difference threshold
COOLDOWN_SEC = 10      # minimum seconds between alerts
RESOLUTION = (640, 480)

# --- Telegram Bot ---
bot = Bot(token=TELEGRAM_BOT_TOKEN) if TELEGRAM_BOT_TOKEN else None

async def send_telegram_alert(image_path, caption):
    if not bot or not TELEGRAM_CHAT_ID:
        print("[telegram] Skipping send: not configured")
        return False
    try:
        with open(image_path, 'rb') as f:
            await bot.send_photo(chat_id=TELEGRAM_CHAT_ID, photo=f, caption=caption)
        print(f"[telegram] Alert sent: {image_path}")
        return True
    except TelegramError as e:
        print(f"[telegram] ERROR: {e}")
        return False

# --- Motion Detection ---
def main():
    print("[motion] Starting camera...")
    cap = cv2.VideoCapture(CAMERA_INDEX)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, RESOLUTION[0])
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, RESOLUTION[1])

    time.sleep(2.0)  # let camera warm up

    prev_frame = None
    last_alert_time = 0

    while True:
        ret, frame = cap.read()
        if not ret:
            print("[motion] Failed to grab frame")
            break

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        gray = cv2.GaussianBlur(gray, (21, 21), 0)

        if prev_frame is None:
            prev_frame = gray
            continue

        frame_diff = cv2.absdiff(prev_frame, gray)
        thresh = cv2.threshold(frame_diff, THRESHOLD, 255, cv2.THRESH_BINARY)[1]
        thresh = cv2.dilate(thresh, None, iterations=2)

        contours, _ = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        motion_detected = False
        for cnt in contours:
            if cv2.contourArea(cnt) < MIN_AREA:
                continue
            motion_detected = True
            (x, y, w, h) = cv2.boundingRect(cnt)
            cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
            break  # only need one large contour

        if motion_detected:
            now = time.time()
            if now - last_alert_time > COOLDOWN_SEC:
                last_alert_time = now
                timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
                filename = os.path.join(SAVE_DIR, f"motion_{timestamp}.jpg")
                cv2.imwrite(filename, frame)
                print(f"[motion] Alert! Saved {filename}")
                # Send to Telegram (async)
                try:
                    import asyncio
                    asyncio.run(send_telegram_alert(filename, f"Motion detected at {timestamp}"))
                except Exception as e:
                    print(f"[telegram] send failed: {e}")

        cv2.imshow("Motion Detection", frame)
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            break

        prev_frame = gray

    cap.release()
    cv2.destroyAllWindows()
    print("[motion] Stopped.")

if __name__ == "__main__":
    main()
