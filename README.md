# OmniNode 📡

A decentralized ESP32 sensor network with mDNS auto-discovery and a Mac-hosted Node-RED dashboard.

## 🏗 Architecture
- **The Master (MacBook Air 2015):** 
    - **Broker:** Mosquitto MQTT (Port 1883).
    - **Discovery:** Broadcasts service via `dns-sd`.
    - **Dashboard:** Node-RED (v4.1.8) hosting the UI at `localhost:1880/ui`.
- **The Nodes (ESP32):**
    - **Discovery:** Automatically finds the Master on the local network via mDNS.
    - **Telemetry:** Reports internal temperature, RSSI (signal strength), and uptime.

---

## 🚀 Setup & Startup Instructions

### 1. Master Setup (Mac)
Ensure you have **Node.js** and **Mosquitto** installed.

**A. Start the MQTT Broker:**
Open a terminal and run Mosquitto with the local config to allow network access:
```bash
/usr/local/sbin/mosquitto -c mosquitto.conf
```

**B. Start mDNS Broadcasting:**
In a new terminal tab, start the "beacon" so ESP32s can find your Mac:
```bash
dns-sd -R "OmniNode Master" _mqtt._tcp . 1883
```

**C. Launch the Dashboard:**
In the project root, install dependencies and start Node-RED:
```bash
npm install
npm start
```
*Access the editor at `http://localhost:1880` and the dashboard at `http://localhost:1880/ui`.*

---

### 2. Node Setup (ESP32)
**A. Generate Configuration:**
Run the Python script to detect your current WiFi SSID:
```bash
python3 generate_config.py
```
*Manually edit `include/config.h` to add your WiFi password.*

**B. Build and Upload:**
1. Open the project in **VS Code** with **PlatformIO**.
2. Connect your ESP32 via USB.
3. Click the **Arrow (→)** icon in the bottom toolbar to upload.

---

## 📂 Repository Structure
- `src/main.cpp`: ESP32 firmware with mDNS/MQTT logic.
- `include/config.h`: (Local only) WiFi and Server credentials.
- `master-config/flows.json`: The Node-RED dashboard configuration.
- `mosquitto.conf`: Configuration to allow remote ESP32 connections.
- `generate_config.py`: Automation script for WiFi setup.

---

## 🔋 Roadmap
- [x] Mac Master setup & ESP32 Handshake.
- [x] Real-time Dashboard (Internal Temp & RSSI).
- [ ] **Next:** Battery Voltage Monitoring via ADC.
- [ ] **Later:** BLE integration for Smart BMS modules.
