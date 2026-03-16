#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// WiFi
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// MQTT
const char* mqtt_server = "192.168.1.100";  // Raspberry Pi IP
const int mqtt_port = 1883;
const char* mqtt_topic = "sensor/dht22";

WiFiClient espClient;
PubSubClient client(espClient);

// DHT
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

long lastMsg = 0;
float temp = 0.0, hum = 0.0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32DHT-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retry in 5s");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;

    hum = dht.readHumidity();
    temp = dht.readTemperature();

    if (isnan(hum) || isnan(temp)) {
      Serial.println("Failed to read DHT");
      return;
    }

    // Build JSON payload (simple manual)
    String payload = "{\"temp\":";
    payload += String(temp, 2);
    payload += ",\"hum\":";
    payload += String(hum, 2);
    payload += "}";

    Serial.print("Publish: ");
    Serial.println(payload);
    client.publish(mqtt_topic, payload.c_str());
  }
}
