#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// WiFi
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Sensors
#define DHT_PIN 4
#define DHT_TYPE DHT22
#define MQ135_PIN 34  // ADC

DHT dht(DHT_PIN, DHT_TYPE);
WebServer server(80);

// History (circular buffer)
const int HISTORY_LEN = 30;
float temp_history[HISTORY_LEN] = {0};
float hum_history[HISTORY_LEN] = {0};
float aqi_history[HISTORY_LEN] = {0};
int hist_idx = 0;
bool hist_filled = false;

float readMQ135() {
  // Raw ADC (0-4095) to voltage (0-3.3V)
  int raw = analogRead(MQ135_PIN);
  float voltage = raw * (3.3 / 4095.0);
  // TODO: convert to ppm (requires calibration). For now return raw voltage.
  return voltage;
}

float calculateAQI(float voltage) {
  // Placeholder: linear mapping 0-3.3V to 0-500 ppm, then AQI scale
  float ppm = voltage * 151.5; // rough approx
  if (ppm < 50) return ppm * 0.5;
  if (ppm < 100) return 50 + (ppm - 50) * 0.8;
  if (ppm < 300) return 90 + (ppm - 100) * 0.4;
  return 150 + (ppm - 300) * 0.2;
}

void updateHistory(float t, float h, float aqi) {
  temp_history[hist_idx] = t;
  hum_history[hist_idx] = h;
  aqi_history[hist_idx] = aqi;
  hist_idx = (hist_idx + 1) % HISTORY_LEN;
  if (hist_idx == 0) hist_filled = true;
}

String getChartDataJS() {
  String out = "[";
  int count = hist_filled ? HISTORY_LEN : hist_idx;
  for (int i = 0; i < count; i++) {
    if (i) out += ",";
    out += String(aqi_history[i]);
  }
  out += "]";
  return out;
}

const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Air Quality</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  <style>
    body { font-family: Arial, sans-serif; margin: 20px; background: #f0f0f0; }
    .card { background: white; padding: 15px; border-radius: 10px; margin-bottom: 15px; }
    .value { font-size: 1.5em; font-weight: bold; }
    .unit { font-size: 0.8em; color: #666; }
  </style>
</head>
<body>
  <h1>Air Quality Monitor</h1>
  <div class="card">
    <p>Temperature: <span id="t" class="value">--</span><span class="unit">°C</span></p>
    <p>Humidity: <span id="h" class="value">--</span><span class="unit">%</span></p>
    <p>Air Quality Index (approx): <span id="a" class="value">--</span></p>
  </div>
  <div class="card">
    <canvas id="chart"></canvas>
  </div>
  <script>
    async function fetchData() {
      let r = await fetch('/data');
      let d = await r.json();
      document.getElementById('t').innerText = d.temp.toFixed(1);
      document.getElementById('h').innerText = d.hum.toFixed(1);
      document.getElementById('a').innerText = d.aqi.toFixed(1);
      chart.data.labels = d.labels;
      chart.data.datasets[0].data = d.aqi_hist;
      chart.update();
    }
    const ctx = document.getElementById('chart').getContext('2d');
    const chart = new Chart(ctx, {
      type: 'line',
      data: {
        labels: [],
        datasets: [{ label: 'AQI', data: [], borderColor: 'blue', fill: false }]
      },
      options: { responsive: true }
    });
    setInterval(fetchData, 2000);
    fetchData();
  </script>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "text/html", MAIN_page);
}

void handleData() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float voltage = readMQ135();
  float aqi = calculateAQI(voltage);

  if (!isnan(t) && !isnan(h)) {
    updateHistory(t, h, aqi);
  }

  int count = hist_filled ? HISTORY_LEN : hist_idx;
  String labels = "[";
  String aqi_vals = "[";
  for (int i = 0; i < count; i++) {
    if (i) { labels += ","; aqi_vals += ","; }
    labels += String(-(count - i));
    aqi_vals += String(aqi_history[i]);
  }
  labels += "]";
  aqi_vals += "]";

  String json = "{\"temp\":" + String(t,1) + ",\"hum\":" + String(h,1) + ",\"aqi\":" + String(aqi,1) + ",\"labels\":" + labels + ",\"aqi_hist\":" + aqi_vals + "}";
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/data", HTTP_GET, handleData);
  server.begin();
}

void loop() {
  server.handleClient();
}
