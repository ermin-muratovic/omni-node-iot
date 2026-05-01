import subprocess
import os

def get_wifi_ssid():
    # macOS command to get the current SSID
    cmd = "/System/Library/PrivateFrameworks/Apple80211.framework/Resources/airport -I"
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    out, err = process.communicate()
    
    for line in out.decode('utf-8').split('\n'):
        if " SSID" in line:
            return line.split(": ")[1].strip()
    return "YOUR_WIFI_NAME"

ssid = get_wifi_ssid()
config_content = f"""#ifndef CONFIG_H
#define CONFIG_H

// Auto-generated WiFi Credentials
const char* ssid = "{ssid}";
const char* password = "YOUR_WIFI_PASSWORD"; // Script cannot safely grab passwords

// MQTT Settings
const char* mqtt_server = "omninode.local"; 

#endif
"""

# Ensure the include directory exists
os.makedirs("include", exist_ok=True)

with open("include/config.h", "w") as f:
    f.write(config_content)

print(f"✅ Generated include/config.h with SSID: {ssid}")