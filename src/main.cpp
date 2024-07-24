#include <Arduino.h>
#include <SoftwareSerial.h>
#include "encode.hpp"

void sendText(String message);

SoftwareSerial ttsSerial(10, 11);

void setup()
{
  ttsSerial.begin(115200);
  Serial.begin(115200);
}

void loop()
{
  byte statusRequest[] = {0xFD, 0x00, 0x01, 0x21};
  ttsSerial.write(statusRequest, 4);

  byte *response = new byte;
  ttsSerial.readBytes(response, 4);
  Serial.println(response[0], HEX);
  delete[] response;

  delay(1000);
  sendText("Hello world");
  delay(10000);
}

void sendText(String message)
{
  byte *encoded = new byte[message.length() + 5];
  encoded[0] = 0xFD;
  short length = message.length() + 2;
  encoded[1] = ((byte *)&length)[1];
  encoded[2] = ((byte *)&length)[0];
  encoded[3] = 0x01;
  encoded[4] = 0x01;
  memcpy(encoded + 5, message.c_str(), message.length());
  ttsSerial.write(encoded, message.length() + 5);
}
