# OmniNode 📡

A self-organizing ESP32 sensor network using mDNS auto-discovery and MQTT telemetry to a Mac-hosted Node-RED dashboard.

## 🏗 Current Architecture
- **Master (MacBook Air 2015):** 
  - **MQTT Broker:** Mosquitto (running on port 1883).
  - **Discovery:** Broadcasts `_mqtt._tcp` via `dns-sd`.
  - **Dashboard:** Node-RED (v4.1.8) on Node v24.15.
- **Nodes (ESP32):**
  - **Discovery:** Finds Master via mDNS query.
  - **Telemetry:** Internal Temp, RSSI, and Uptime via JSON over MQTT.

## 🛠 Tech Stack
- **Hardware:** ESP32 DevKit.
- **Framework:** Arduino / PlatformIO.
- **Communication:** MQTT + mDNS.

## 🚀 Recent Milestones
- [x] Mac Master setup (Mosquitto + Node-RED).
- [x] Successful End-to-End Handshake (ESP32 -> Mac).
- [x] Real-time Dashboard with SENDER #1 Gauges.

## 🔋 Roadmap
- [ ] Implement Battery Monitoring (ADC Voltage Divider).
- [ ] Add BLE/Bluetooth smart BMS integration.
- [ ] Auto-generate dashboard cards for new nodes dynamically.
```

---

### Pro-Tip: The "Persist" Button
In Node-RED, now that you've imported the flow, click on the **Dashboard** tab in the right-hand sidebar (the little chart icon). Here, you can change the theme (Dark/Light) or change the title of the page to "OmniNode Vitals" to make it look even more professional.

**You are now ready for the next phase. Are you going to start wiring the battery voltage divider, or do you want to add a second ESP32 node first?**