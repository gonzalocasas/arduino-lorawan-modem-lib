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

#ifndef _LORAWANMESSAGE_H_
#define _LORAWANMESSAGE_H_

#include "LoRaWANModem.h"
#include "pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "deviceData.pb.h"
#include "appData.pb.h"

typedef api_DeviceData devicedata_t;
typedef api_AppData appdata_t;

class LoRaWANMessage
{
public:
  static void encodeDeviceData(devicedata_t *data, uint8_t **buffer, size_t *size);
  static bool decodeAppData(appdata_t *receiveData, const uint8_t *payload, size_t size);
};

#endif
