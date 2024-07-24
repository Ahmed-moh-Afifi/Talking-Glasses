#include "encode.hpp"

void setup()
{
  ttsSerial.begin(115200);
  Serial.begin(115200);
}

void loop()
{
  byte statusRequest[] = {0xFD, 0x00, 0x01, 0x21};
  ttsSerial.write(statusRequest, 4);

  // byte *response = new byte;
  // ttsSerial.readBytes(response, 4);
  // Serial.println(response[0], HEX);
  // delete[] response;

  Serial.println(check_status(), HEX);

  delay(1000);
  sendText("Hello world");
  delay(10000);
}
