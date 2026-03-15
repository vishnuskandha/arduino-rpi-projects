#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define MQ135_PIN A0

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  dht.begin();
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP280 sensor");
    while (1) {}
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_0_5);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float p = bmp.readPressure() / 100.0F; // hPa
  int mq = analogRead(MQ135_PIN);

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT!");
    delay(2000);
    return;
  }

  // CSV format: time,temp(C),humidity(%),pressure(hPa),air_quality
  Serial.print(millis());
  Serial.print(",");
  Serial.print(t, 2);
  Serial.print(",");
  Serial.print(h, 1);
  Serial.print(",");
  Serial.print(p, 2);
  Serial.print(",");
  Serial.println(mq);

  delay(2000);
}
