#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "TurkTelekom_Z33RE";
const char* password = "bE6457b822dF2";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());
  
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/plain", "Hello World");
}

