#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "ESP8266-AP";
const char* password = "12345678";

AsyncWebServer server(80);

void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", "<h1>ESP8266 Access Point</h1>");
  });

  server.begin();
}

void loop() {
  new_stations = WiFi.softAPgetStationNum();
  if (current_stations < new_stations) { // Device is Connected
    current_stations = new_stations;
    Serial.print("New Device Connected to SoftAP... Total Connections: ");
    Serial.println(current_stations);
  }
  if (current_stations > new_stations) { // Device is Disconnected
    current_stations = new_stations;
    Serial.print("Device disconnected from SoftAP... Total Connections: ");
    Serial.println(current_stations);
  }
}