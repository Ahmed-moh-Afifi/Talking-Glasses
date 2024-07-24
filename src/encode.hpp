#include <Arduino.h>

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
