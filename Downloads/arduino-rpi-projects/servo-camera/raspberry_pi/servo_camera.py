import cv2
import numpy as np
import serial
import time

# Arduino connection
arduino = serial.Serial('COM6', 9600)
time.sleep(2)

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)

# Previous angles for smoothing
prev_pan_angle = 90
prev_tilt_angle = 90
smoothing_factor = 0.2
last_fire = False
FIRE_AREA_THRESHOLD = 1500  # tune to environment
COOLDOWN_FRAMES = 8
cooldown = 0

# Kalman filter
kalman = cv2.KalmanFilter(4,2)
kalman.measurementMatrix = np.array([[1,0,0,0],[0,1,0,0]], np.float32)
kalman.transitionMatrix = np.array([[1,0,1,0],[0,1,0,1],[0,0,1,0],[0,0,0,1]], np.float32)
kalman.processNoiseCov = np.eye(4, dtype=np.float32) * 0.03

# Red color HSV
lower_red1 = np.array([0, 120, 70])
upper_red1 = np.array([10, 255, 255])
lower_red2 = np.array([170, 120, 70])
upper_red2 = np.array([180, 255, 255])

# Tilt calibration (adjust these values according to your servo)
tilt_min = 50    # top position
tilt_max = 130   # bottom position

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.flip(frame, 1)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    mask1 = cv2.inRange(hsv, lower_red1, upper_red1)
    mask2 = cv2.inRange(hsv, lower_red2, upper_red2)
    mask = cv2.bitwise_or(mask1, mask2)

    kernel = np.ones((5,5), np.uint8)
    mask = cv2.erode(mask, kernel, iterations=1)
    mask = cv2.dilate(mask, kernel, iterations=2)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    if contours:
        c = max(contours, key=cv2.contourArea)
        area = cv2.contourArea(c)
        if area > 500:
            M = cv2.moments(c)
            if M["m00"] != 0:
                cx = int(M["m10"]/M["m00"])
                cy = int(M["m01"]/M["m00"])

                # Kalman prediction
                measured = np.array([[np.float32(cx)], [np.float32(cy)]])
                kalman.correct(measured)
                predicted = kalman.predict()
                pred_x, pred_y = int(predicted[0]), int(predicted[1])

                # Draw dynamic pointer
                cv2.drawContours(frame, [c], -1, (0,255,0),2)
                cv2.circle(frame,(pred_x,pred_y),7,(255,0,0),-1)

                # Map to pan (horizontal) and tilt (vertical)
                frame_width = frame.shape[1]
                frame_height = frame.shape[0]

                pan_angle = int(np.interp(frame_width - pred_x, [0, frame_width], [0,180]))
                tilt_angle = int(np.interp(pred_y, [0, frame_height], [tilt_min, tilt_max]))  # calibrated tilt

                # Smooth angles
                pan_angle = int(prev_pan_angle + smoothing_factor*(pan_angle - prev_pan_angle))
                tilt_angle = int(prev_tilt_angle + smoothing_factor*(tilt_angle - prev_tilt_angle))

                # Send to Arduino
                arduino.write(f'{pan_angle},{tilt_angle}\n'.encode())

                prev_pan_angle = pan_angle
                prev_tilt_angle = tilt_angle

                # Fire event with hysteresis based on contour area
                fire_now = area >= FIRE_AREA_THRESHOLD
                if fire_now and not last_fire:
                    try:
                        arduino.write(b'FIRE_DETECTED\n')
                    except Exception as e:
                        print('Serial error (fire event):', e)
                    last_fire = True
                    cooldown = COOLDOWN_FRAMES
                else:
                    if cooldown > 0:
                        cooldown -= 1
                    else:
                        if last_fire and not fire_now:
                            try:
                                arduino.write(b'NO_FIRE\n')
                            except Exception as e:
                                print('Serial error (fire event):', e)
                            last_fire = False

    cv2.imshow("Dual Servo Auto-Calibrated", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
arduino.close()
