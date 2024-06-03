#include <WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "your_ssid";
const char* password = "your_password";

ESP8266WebServer server(80);

// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";

void setup() {
  Serial.begin(115200);
  
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status()!= WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    String request = client.readStringUntil('\r');
    
    if (request.indexOf("/5/on")!= -1) {
      Serial.println("GPIO 5 is ON");
      digitalWrite(output5, HIGH);
      output5State = "on";
    }
    if (request.indexOf("/5/off")!= -1) {
      Serial.println("GPIO 5 is OFF");
      digitalWrite(output5, LOW);
      output5State = "off";
    }
    if (request.indexOf("/4/on")!= -1) {
      Serial.println("GPIO 4 is ON");
      digitalWrite(output4, HIGH);
      output4State = "on";
    }
    if (request.indexOf("/4/off")!= -1) {
      Serial.println("GPIO 4 is OFF");
      digitalWrite(output4, LOW);
      output4State = "off";
    }
    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE html><html>");
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
    client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
    client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
    client.println(".button:hover {background-color: #44A88B;}</style></head>");
    
    client.println("<body><h1>ESP8266 Web Server</h1>");
    client.println("<p>GPIO 5 - State " + output5State + "</p>");
    client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
    client.println("<p><a href=\"/5/off\"><button class=\"button\">OFF</button></a></p>");
    client.println("<p>GPIO 4 - State " + output4State + "</p>");
    client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
    client.println("<p><a href=\"/4/off\"><button class=\"button\">OFF</button></a></p>");
    client.println("</body></html>");
    
    delay(1);
    client.stop();
  }
}