#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>

// AP credentials
const char* apSSID = "ESP32-AP";
const char* apPassword = "12345678";  // minimum 8 characters

WebServer server(80);

// HTML for the control page
const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial, sans-serif; margin: 20px; background: #f0f0f0; }
    .card { background: white; padding: 20px; border-radius: 10px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); margin-bottom: 20px; }
    h1 { margin-top: 0; color: #333; }
    .btn { padding: 10px 20px; margin: 5px; border: none; border-radius: 5px; cursor: pointer; color: white; }
    .on { background: #4CAF50; }
    .off { background: #f44336; }
    .status { font-weight: bold; margin-left: 10px; }
    form { margin-top: 10px; }
    input[type=file] { margin: 10px 0; }
    input[type=submit] { background: #2196F3; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; }
  </style>
</head>
<body>
  <div class="card">
    <h1>ESP32 Web Server</h1>
    <p>GPIO Control | <a href="/update">Firmware Update (OTA)</a></p>
  </div>

  <div class="card">
    <h2>GPIO Control</h2>
    <form method="POST" action="/gpio">
      <label>Pin number:</label>
      <input type="number" name="pin" min="0" max="39" required>
      <label>State:</label>
      <select name="state">
        <option value="1">HIGH (1)</option>
        <option value="0">LOW (0)</option>
      </select>
      <button type="submit" class="btn on">Set Output</button>
    </form>
    <form method="GET" action="/gpio">
      <label>Read pin:</label>
      <input type="number" name="pin" min="0" max="39" required>
      <button type="submit" class="btn off">Read</button>
    </form>
  </div>

  <div class="card">
    <h2>Status</h2>
    <pre id="stats">Loading...</pre>
    <script>
      function fetchStatus() {
        fetch('/status').then(r=>r.json()).then(data=> {
          document.getElementById('stats').textContent = JSON.stringify(data, null, 2);
        });
      }
      setInterval(fetchStatus, 2000);
      fetchStatus();
    </script>
  </div>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "text/html", MAIN_page);
}

void handleGPIO() {
  if (server.method() == HTTP_GET) {
    if (server.hasArg("pin")) {
      int pin = server.arg("pin").toInt();
      if (pin >= 0 && pin <= 39) {
        int state = digitalRead(pin);
        server.send(200, "text/plain", String(state));
      } else {
        server.send(400, "text/plain", "Invalid pin");
      }
    } else {
      server.send(400, "text/plain", "Missing 'pin' parameter");
    }
  } else if (server.method() == HTTP_POST) {
    if (server.hasArg("pin") && server.hasArg("state")) {
      int pin = server.arg("pin").toInt();
      int state = server.arg("state").toInt();
      if (pin >= 0 && pin <= 39) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, state);
        server.send(200, "text/plain", "OK");
      } else {
        server.send(400, "text/plain", "Invalid pin");
      }
    } else {
      server.send(400, "text/plain", "Missing parameters");
    }
  } else {
    server.send(405, "text/plain", "Method Not Allowed");
  }
}

void handleStatus() {
  long uptime = millis() / 1000;
  long freeHeap = ESP.getFreeHeap();
  String json = "{\"uptime\":" + String(uptime) + ",\"freeHeap\":" + String(freeHeap) + ",\"ssid\":\"" + String(apSSID) + "\"}";
  server.send(200, "application/json", json);
}

// OTA: index and upload handler
void handleUpdatePage() {
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "text/html", R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head><title>Firmware Update</title></head>
    <body>
      <h1>OTA Firmware Update</h1>
      <form method='POST' action='/update' enctype='multipart/form-data'>
        <input type='file' name='update' accept='.bin'>
        <input type='submit' value='Update'>
      </form>
    </body>
    </html>
  )rawliteral");
}

void handleUpdateUpload() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    Serial.setDebugOutput(true);
    Serial.printf("Update: %s\n", upload.filename.c_str());
    if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { // start with max available size
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) { // true to set the reboot flag
      Serial.printf("Update Success: %u bytes. Rebooting...\n", upload.totalSize);
    } else {
      Update.printError(Serial);
    }
    Serial.setDebugOutput(false);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Booting...");

  // Start Soft AP
  WiFi.softAP(apSSID, apPassword);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/gpio", HTTP_GET | HTTP_POST, handleGPIO);
  server.on("/status", HTTP_GET, handleStatus);
  server.on("/update", HTTP_GET, handleUpdatePage);
  server.on("/update", HTTP_POST, [](){ server.send(200); }, handleUpdateUpload);

  // Catch-all for 404
  server.onNotFound([]() {
    server.send(404, "text/plain", "Not Found");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  delay(1);
}
