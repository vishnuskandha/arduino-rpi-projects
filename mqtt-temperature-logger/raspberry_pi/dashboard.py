#!/usr/bin/env python3
"""
Simple Flask dashboard to display temperature/humidity history.
"""

import os
import csv
from datetime import datetime, timedelta
from flask import Flask, render_template_string, send_file
import pandas as pd

app = Flask(__name__)
LOG_FILE = "sensor_log.csv"

HTML = """
<!doctype html>
<html>
<head>
  <title>Temperature/Humidity Dashboard</title>
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  <style>
    body { font-family: Arial, sans-serif; margin: 20px; }
    .chart { max-width: 900px; margin: auto; }
    .info { text-align: center; margin-bottom: 20px; }
    a { margin: 0 10px; }
  </style>
</head>
<body>
  <div class="info">
    <h1>Sensor Dashboard</h1>
    <a href="/download">Download CSV</a>
    <a href="/clear">Clear Data</a>
  </div>
  <div class="chart">
    <canvas id="chart"></canvas>
  </div>
  <script>
    fetch('/data')
      .then(r => r.json())
      .then(data => {
        const ctx = document.getElementById('chart').getContext('2d');
        new Chart(ctx, {
          type: 'line',
          data: {
            labels: data.timestamps,
            datasets: [
              { label: 'Temperature (°C)', data: data.temps, borderColor: 'red', fill: false },
              { label: 'Humidity (%)', data: data.hums, borderColor: 'blue', fill: false }
            ]
          },
          options: {
            responsive: true,
            scales: {
              x: { ticks: { maxTicksLimit: 12 } }
            }
          }
        });
      });
  </script>
</body>
</html>
"""

def read_csv():
    if not os.path.exists(LOG_FILE):
        return [], [], []
    with open(LOG_FILE, 'r') as f:
        reader = csv.DictReader(f)
        rows = list(reader)
    # limit to last 100 points
    rows = rows[-100:]
    timestamps = [r['timestamp'] for r in rows]
    temps = [float(r['temperature_c']) for r in rows]
    hums = [float(r['humidity_pct']) for r in rows]
    return timestamps, temps, hums

@app.route('/')
def index():
    return render_template_string(HTML)

@app.route('/data')
def data():
    ts, t, h = read_csv()
    return {'timestamps': ts, 'temps': t, 'hums': h}

@app.route('/download')
def download():
    return send_file(LOG_FILE, as_attachment=True)

@app.route('/clear')
def clear():
    with open(LOG_FILE, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['timestamp', 'temperature_c', 'humidity_pct'])
    return "Log cleared."

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
