from picamera2 import Picamera2
import cv2
import numpy as np
import time
import serial

# -----------------------------
# Arduino Serial Setup
# -----------------------------
arduino = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
time.sleep(2)

# -----------------------------
# Camera setup (PiCam v2)
# -----------------------------
cam_width, cam_height = 320, 240
fps = 15

picam2 = Picamera2()
video_config = picam2.create_video_configuration(
    main={"size": (cam_width, cam_height), "format": "XRGB8888"},
    controls={"FrameDurationLimits": (int(1e6/fps), int(1e6/fps))}
)
picam2.configure(video_config)
picam2.start()

# -----------------------------
# Servo starting positions
# -----------------------------
prev_pan, prev_tilt = 90, 90

# -----------------------------
# Create HSV Trackbars
# -----------------------------
def nothing(x): pass

cv2.namedWindow("Mask Controls")
cv2.createTrackbar("H_low", "Mask Controls", 0, 179, nothing)
cv2.createTrackbar("S_low", "Mask Controls", 50, 255, nothing)
cv2.createTrackbar("V_low", "Mask Controls", 200, 255, nothing)

cv2.createTrackbar("H_high", "Mask Controls", 20, 179, nothing)
cv2.createTrackbar("S_high", "Mask Controls", 255, 255, nothing)
cv2.createTrackbar("V_high", "Mask Controls", 255, 255, nothing)

# -----------------------------
# Main loop
# -----------------------------
while True:
    frame = picam2.capture_array()

    # Flip camera to correct orientation
    frame = cv2.flip(frame, -1)  # rotate 180° (try -1, 0, or 1 depending on your camera mount)

    frameHSV = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Get trackbar values
    hL = cv2.getTrackbarPos("H_low", "Mask Controls")
    sL = cv2.getTrackbarPos("S_low", "Mask Controls")
    vL = cv2.getTrackbarPos("V_low", "Mask Controls")

    hH = cv2.getTrackbarPos("H_high", "Mask Controls")
    sH = cv2.getTrackbarPos("S_high", "Mask Controls")
    vH = cv2.getTrackbarPos("V_high", "Mask Controls")

    lower = np.array([hL, sL, vL])
    upper = np.array([hH, sH, vH])

    # Mask
    mask = cv2.inRange(frameHSV, lower, upper)
    mask = cv2.GaussianBlur(mask, (5, 5), 0)
    mask = cv2.dilate(mask, None, iterations=2)

    # Contours
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    if contours:
        cnt = max(contours, key=cv2.contourArea)
        area = cv2.contourArea(cnt)
        if area > 150:
            M = cv2.moments(cnt)
            if M["m00"] != 0:
                cx = int(M["m10"] / M["m00"])
                cy = int(M["m01"] / M["m00"])

                # Servo mapping
                pan = int(cx * 180 / cam_width)
                tilt = int(cy * 180 / cam_height)

                # Smooth movement
                pan = int((prev_pan * 0.7 + pan * 0.3))
                tilt = int((prev_tilt * 0.7 + tilt * 0.3))

                # Clamp
                pan = max(10, min(170, pan))
                tilt = max(20, min(150, tilt))  # limit tilt

                # Send to Arduino
                try:
                    command = f"{pan},{tilt}\n"
                    arduino.write(command.encode())
                except Exception as e:
                    print("Serial error:", e)

                prev_pan, prev_tilt = pan, tilt

                # Draw
                cv2.circle(frame, (cx, cy), 10, (0, 0, 255), 2)
                cv2.putText(frame, f"Pan:{pan} Tilt:{tilt}", (10, 20),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 0), 1)

    # Show
    cv2.imshow("Camera Feed", frame)
    cv2.imshow("Mask", mask)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

picam2.stop()
arduino.close()
cv2.destroyAllWindows()
