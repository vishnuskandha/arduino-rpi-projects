# Fire Detection & Suppression System
Uses Raspberry Pi (OpenCV) for fire detection and Arduino for servo + relay control.
## Tested hardware
- Raspberry Pi (with camera)
- Arduino Uno/Nano
- Relay module and/or 2x SG90 micro servos
- USB cable Pi <-> Arduino

## Circuit mapping
- Arduino: PAN servo -> D9, TILT servo -> D3, Relay -> D13
- Raspberry Pi: CSI camera; USB serial to Arduino
- Power servos/relay from suitable supply (common GND)
