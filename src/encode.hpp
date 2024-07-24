#ifndef ENCODE_H_
#define ENCODE_H_

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "enum.hpp"

#define CHECK_RESPONSE                 \
  {                                    \
    byte response;                     \
    ttsSerial.readBytes(&response, 1); \
    return response == 0x41;           \
  }

SoftwareSerial ttsSerial(10, 11);

bool sendText(String message)
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
  CHECK_RESPONSE;
}

bool set_volume(volume v)
{
  byte query[] = {0x5B, 0x76, 0x30 + v, 0x5D};
  ttsSerial.write(query, 4);
  CHECK_RESPONSE;
}

bool set_speed(speed s)
{
  byte query[] = {0x5B, 0x76, 0x30 + s, 0x5D};
  ttsSerial.write(query, 4);
  CHECK_RESPONSE;
}

bool set_tone(sound_tone t)
{
  byte query[] = {0x5B, 0x76, 0x30 + t, 0x5D};
  ttsSerial.write(query, 4);
  CHECK_RESPONSE;
}

byte check_status()
{
  byte query[] = {0xFD, 0x00, 0x01, 0x21};
  ttsSerial.write(query, 4);
  CHECK_RESPONSE;
}

module_state is_idle()
{
  byte response = check_status();
  switch (response)
  {
  case 0x4E:
    return m_busy;
  case 0x4F:
    return m_idle;
  default:
    return m_error;
  }
}

bool send_ring(ring r)
{
  byte query[] = {0x72, 0x69, 0x6E, 0x67, 0x5F, 0x31 + r};
  ttsSerial.write(query, 6);
  CHECK_RESPONSE;
}

bool send_msg_tone(msg m)
{
  byte query[] = {0x6D, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x5F, 0x31 + m};
  ttsSerial.write(query, 9);
  CHECK_RESPONSE;
}

bool send_alert(alert a)
{
  byte query[] = {0x61, 0x6C, 0x65, 0x72, 0x74, 0x5F, 0x31 + a};
  ttsSerial.write(query, 7);
  CHECK_RESPONSE;
}

#endif // ENCODE_H_
