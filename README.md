# OmniNode 📡

A decentralized ESP32 sensor network with mDNS auto-discovery and a Mac-hosted Node-RED dashboard for real-time monitoring.

## 🏗 Architecture
This project implements a **Master-Client** architecture designed for home automation and battery monitoring.

- **The Master (Mac/Local Server):**
    - **Discovery:** Acts as a known mDNS target (`omninode.local`).
    - **Broker:** Runs an MQTT Broker (Mosquitto) to handle incoming data.
    - **Dashboard:** Hosts a Node-RED instance for real-time data visualization on `localhost`.
- **The Nodes (ESP32):**
    - **Discovery:** Automatically finds the Master on the local network via mDNS.
    - **Sensors:** Reports Internal Temp, RSSI, and external DHT22/BMS data.
    - **Communication:** Periodically pushes JSON payloads via MQTT.

## 🛠 Tech Stack
- **Hardware:** ESP32 (S3/C3/DevKit)
- **Firmware:** C++ (VS Code + PlatformIO)
- **Master Software:** Node-RED, Mosquitto MQTT
- **Discovery:** mDNS (Multicast DNS)

## 🚀 Setup Guide

### 1. Master Setup (Mac)
```bash
# Install Homebrew if not installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install MQTT Broker
brew install mosquitto
brew services start mosquitto

# Install Node-RED
npm install -g --unsafe-perm node-red
node-red
```

### 2. ESP32 Firmware
1. Open **VS Code** and install the **PlatformIO** extension.
2. Clone this repo and open the folder.
3. Edit `include/config.h` with your WiFi credentials.
4. Upload to your ESP32.

## 🔋 Roadmap
- [x] mDNS Master Discovery
- [x] Basic Temp/Humidity reporting
- [ ] Battery Voltage via ADC (Voltage Divider)
- [ ] BLE Client for Smart BMS integration
