#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  if (!LoRa.begin(915E6)) {
    while (1);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String message = "";
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }
    Serial.println("Received: " + message);
  }
}
