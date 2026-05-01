#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "config.h" //

// Pin Definitions (Adjust based on your specific ESP32 board)
#define BUTTON_LED_PIN 0   // Often 'Boot' button
#define BUTTON_SEND_PIN 35  // Second button
#define LED_PIN 2          // Internal LED

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid); //

    WiFi.begin(ssid, password); //

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected. IP address: ");
    Serial.println(WiFi.localIP());
}

void discover_master() {
    Serial.println("Searching for Master (omninode.local)...");
    while (true) {
        if (MDNS.begin("esp32-node1")) {
            // Find service "mqtt" over "tcp"
            int n = MDNS.queryService("mqtt", "tcp");
            if (n > 0) {
                Serial.print("Master found! IP: ");
                Serial.println(MDNS.IP(0));
                client.setServer(MDNS.IP(0), 1883);
                break;
            }
        }
        Serial.print(".");
        delay(2000);
    }
}

void send_telemetry() {
    if (!client.connected()) return;

    JsonDocument doc;
    doc["node"] = "ESP32_Primary";
    doc["temp"] = temperatureRead(); // Internal ESP32 chip temp
    doc["rssi"] = WiFi.RSSI();
    doc["uptime"] = millis() / 1000;

    char buffer[256];
    serializeJson(doc, buffer);
    client.publish("omninode/vitals", buffer);
    Serial.println("Data sent to Master.");
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32_Node_1")) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_LED_PIN, INPUT_PULLUP);
    pinMode(BUTTON_SEND_PIN, INPUT_PULLUP);
    
    Serial.begin(115200);
    setup_wifi();
    discover_master();
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // Button 1: Toggle LED
    if (digitalRead(BUTTON_LED_PIN) == LOW) {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        delay(200); // Debounce
    }

    // Button 2: Force MQTT Send
    if (digitalRead(BUTTON_SEND_PIN) == LOW) {
        send_telemetry();
        delay(500); // Debounce
    }

    // Periodic Send (every 30 seconds)
    unsigned long now = millis();
    if (now - lastMsg > 30000) {
        lastMsg = now;
        send_telemetry();
    }
}