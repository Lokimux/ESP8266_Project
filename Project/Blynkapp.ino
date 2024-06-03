#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials
char ssid[] = "your_wifi_ssid";
char pass[] = "your_wifi_password";

// Your Blynk auth token
char auth[] = "your_blynk_auth_token";

// Define the LED pin
int ledPin = D0; // or any other pin you're using

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V0) // Virtual pin 0
{
  int value = param.asInt();
  if (value == 1) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}