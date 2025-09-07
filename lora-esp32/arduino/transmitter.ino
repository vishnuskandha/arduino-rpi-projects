#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  if (!LoRa.begin(915E6)) {
    while (1);
  }
}

void loop() {
  LoRa.beginPacket();
  LoRa.print("Hello LoRa");
  LoRa.endPacket();
  delay(2000);
}
