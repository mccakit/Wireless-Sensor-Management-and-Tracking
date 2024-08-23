#include <SoftwareSerial.h>
SoftwareSerial to_NodeMCU(6, 7);  // Use parentheses instead of curly braces

void setup()
{
  Serial.begin(115200);  // Add this for debugging
  to_NodeMCU.begin(115200);
  delay(1000);
}
double read_temp{};
void loop()
{
  read_temp = analogRead(A0) * 5.0 / 1023.0 * 100.0;
  to_NodeMCU.println(read_temp,3);  // Use println instead of write for easier parsing
  Serial.println("Sent: "+String(read_temp,3));  // Add this for debugging
  delay(1000);
}