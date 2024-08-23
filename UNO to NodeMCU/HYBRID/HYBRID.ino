#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

const char* ssid = "Redmi Note 10 Pro";
const char* password = "mesecak01";

SoftwareSerial from_UNO(D6, D7);
ESP8266WebServer server(80);

String receivedData = "";

void setup() {
  Serial.begin(115200);
  from_UNO.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());
  
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  Serial.println("NodeMCU ready");
}

void loop() {
  server.handleClient();
  
  if (from_UNO.available()) {
    receivedData = from_UNO.readStringUntil('\n');
    receivedData.trim();
    Serial.print("Received: ");
    Serial.println(receivedData);
  }
}

void handleRoot() {
  server.send(200, "text/plain", receivedData);
}