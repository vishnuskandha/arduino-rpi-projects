# PIR Motion Light

Turn on a light when motion is detected.

## Components
- Arduino or Raspberry Pi
- PIR sensor
- LED/relay

## Arduino
rduino/pir_led.ino

## Raspberry Pi
aspberry_pi/pir_light.py

## Run
- Wire PIR OUT to input pin
- Upload sketch or run Python script

## Tested hardware
- Arduino or Raspberry Pi
- PIR motion sensor
- LED/relay

## Circuit mapping
- Arduino: PIR OUT -> D2; LED -> D13 or via resistor
- Raspberry Pi: PIR -> GPIO23, LED/relay -> GPIO24 (per script)
