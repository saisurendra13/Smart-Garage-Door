
#include <ESP8266WiFi.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");

  pinMode(D1, OUTPUT);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");

    String request = client.readStringUntil('\r');
    Serial.println(request);

    String command = request.substring(0, request.indexOf(' '));
    Serial.println(command);

    if (command == "open") {
      digitalWrite(D1, HIGH);
      Serial.println("Garage door opened");
    } else if (command == "close") {
      digitalWrite(D1, LOW);
      Serial.println("Garage door closed");
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/plain");
    client.println("");
    client.println("Garage door action executed");
    client.stop();

    Serial.println("Client disconnected");
  }
}