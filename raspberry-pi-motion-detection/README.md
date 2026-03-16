# Raspberry Pi Motion Detection Camera with Telegram Alerts

A simple security camera using Raspberry Pi camera module or USB webcam. Detects motion via background subtraction and sends an image alert to Telegram on detection.

## 🎯 Features
- Real-time motion detection (OpenCV)
- Automatic Telegram notification with snapshot
- Adjustable sensitivity and region of interest
- Minimal dependencies
- Can run headless

## 🛠️ Hardware Required
- Raspberry Pi 3/4/Zero 2 W
- Raspberry Pi Camera Module or USB webcam
- MicroSD card with Raspberry Pi OS (Bullseye or later)

## 🔌 Wiring
- Camera Module: connect via CSI ribbon cable
- USB webcam: plug into USB port

## 📜 Raspberry Pi Code

See `raspberry_pi/motion_detection.py`.

### Setup
```bash
# On Raspberry Pi
sudo apt update
sudo apt install python3-pip libopencv-dev
pip3 install opencv-python pillow python-telegram-bot
```

### Configuration
Edit `motion_detection.py` and set:
- `TELEGRAM_BOT_TOKEN` — from BotFather
- `TELEGRAM_CHAT_ID` — your user ID
- `CAMERA_INDEX` — 0 for USB webcam, 0 for Pi camera (use Picamera2 backend if needed)

### Usage
```bash
python3 motion_detection.py
```

Press `q` to quit.

### How it works
1. Captures frames from camera.
2. Converts to grayscale and applies Gaussian blur.
3. Computes absolute difference with previous frame.
4. Thresholds and dilates to find motion regions.
5. If enough contours exceed area threshold, triggers alert.
6. Saves snapshot and sends to Telegram with caption.
7. Cooldown period prevents spamming.

## 📂 Project Structure
```
raspberry-pi-motion-detection/
├── raspberry_pi/
│   └── motion_detection.py
└── README.md
```

## 🎛️ Tuning Parameters
- `MIN_AREA` — minimum contour area to count as motion (default 500)
- `THRESHOLD` — binary threshold for difference (default 25)
- `COOLDOWN_SEC` — wait time between alerts (default 10)
- `SAVE_DIR` — where to store snapshots locally

## 📄 License
MIT
