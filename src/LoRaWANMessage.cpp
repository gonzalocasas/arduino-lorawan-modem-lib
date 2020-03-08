// This file is part of the LoRaWAN Modem library.
// Copyright © 2020 Gonzalo Casas
//
// The library is a direct port of the excellent The Things Network library
// for Arduino Devices by Johan Stokking et al,
// and it (mostly) preserves API compatibility to the original.
//
// Based on the The Things Network library for Arduino Devices
// https://github.com/TheThingsNetwork/arduino-device-lib/
// Copyright © 2017 The Things Network

#include "LoRaWANMessage.h"

bool LoRaWANMessage::decodeAppData(appdata_t *receiveData, const byte *payload, size_t length)
{
  pb_istream_t stream = pb_istream_from_buffer(payload, length);
  if (!pb_decode(&stream, api_AppData_fields, receiveData))
  {
    return false;
  }
#ifdef LED_BUILTIN
  receiveData->light ? digitalWrite(LED_BUILTIN, HIGH) : digitalWrite(LED_BUILTIN, LOW);
#endif
  return true;
}

void LoRaWANMessage::encodeDeviceData(devicedata_t *data, byte **buffer, size_t *size)
{
  byte message[TTN_BUFFER_SIZE];

  pb_ostream_t sendStream = pb_ostream_from_buffer(message, sizeof(message));
  pb_encode(&sendStream, api_DeviceData_fields, data);
  *buffer = message;
  *size = sendStream.bytes_written;
}
