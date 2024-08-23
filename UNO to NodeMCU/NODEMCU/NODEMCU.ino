#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
SoftwareSerial from_UNO(D6, D7);

const char* ssid = "TurkTelekom_Z33RE";
const char* password = "bE6457b822dF2";
WiFiServer server(80);
void setup()
{
  Serial.begin(115200);
  from_UNO.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());
  delay(1000);
  Serial.println("NodeMCU ready");  // Add this for debugging
}

void loop()
{
  if (from_UNO.available())
  {
    int state = from_UNO.parseInt();
    Serial.print("Received: ");
    Serial.println(state);
    WiFiClient client = server.available();
    if (client) 
    {
      client.println("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n"+String(state)+"");
      client.stop();
    }
  }
}