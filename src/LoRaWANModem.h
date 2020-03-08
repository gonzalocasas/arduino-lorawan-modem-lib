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

#ifndef _LORAWANMODEM_H_
#define _LORAWANMODEM_H_

#include <Arduino.h>
#include <Stream.h>
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_SAMD)
#include <avr/pgmspace.h>
#else
#include <pgmspace.h>
#endif

#define TTN_DEFAULT_SF 7
#define TTN_DEFAULT_FSB 2
#define TTN_RETX "7"

#define TTN_PWRIDX_EU868 "1"
#define TTN_PWRIDX_US915 "5"
#define TTN_PWRIDX_AU915 "5"
#define TTN_PWRIDX_AS920_923 "1" // TODO: should be 0, originally not changed because RN2903AS firmware didn't accept that value (probably still using EU868: 1=14dBm)
#define TTN_PWRIDX_AS923_925 "1" // TODO: should be 0
#define TTN_PWRIDX_KR920_923 "1" // TODO: should be 0
#define TTN_PWRIDX_IN865_867 "1" // TODO: should be 0

#define TTN_BUFFER_SIZE 300

                                     typedef uint8_t port_t;

// TTN Response codes
enum ttn_response_t
{
  TTN_ERROR_SEND_COMMAND_FAILED = (-1),
  TTN_ERROR_UNEXPECTED_RESPONSE = (-10),
  TTN_SUCCESSFUL_TRANSMISSION = 1,
  TTN_SUCCESSFUL_RECEIVE = 2
};

// TTN Frequency plans
enum ttn_fp_t
{
  TTN_FP_EU868,
  TTN_FP_US915,
  TTN_FP_AU915,
  TTN_FP_AS920_923,
  TTN_FP_AS923_925,
  TTN_FP_KR920_923,
  TTN_FP_IN865_867
};

// LoRaWAN Modem commands
enum
{
  CMD_GETEVENT = 0x00,
  CMD_GETVERSION = 0x01,
  CMD_RESET = 0x02,
  CMD_FACTORYRESET = 0x03,
  CMD_RESETCHARGE = 0x04,
  CMD_GETCHARGE = 0x05,
  CMD_GETTXPOWEROFFSET = 0x06,
  CMD_SETTXPOWEROFFSET = 0x07,
  CMD_TEST = 0x08,
  CMD_FIRMWAREUPDATE = 0x09,
  CMD_GETTIME = 0x0A,
  CMD_GETSTATUS = 0x0B,
  CMD_SETALARMTIMER = 0x0C,
  CMD_GETTRACE = 0x0D,
  CMD_GETPIN = 0x0E,
  CMD_GETCHIPEUI = 0x0F,
  CMD_GETJOINEUI = 0x10,
  CMD_SETJOINEUI = 0x11,
  CMD_GETDEVEUI = 0x12,
  CMD_SETDEVEUI = 0x13,
  CMD_SETNWKKEY = 0x14,
  CMD_GETCLASS = 0x15,
  CMD_SETCLASS = 0x16,
  CMD_SETMULTICAST = 0x17,
  CMD_GETREGION = 0x18,
  CMD_SETREGION = 0x19,
  CMD_LISTREGIONS = 0x1A,
  CMD_GETADRPROFILE = 0x1B,
  CMD_SETADRPROFILE = 0x1C,
  CMD_GETDMPORT = 0x1D,
  CMD_SETDMPORT = 0x1E,
  CMD_GETDMINFOINTERVAL = 0x1F,
  CMD_SETDMINFOINTERVAL = 0x20,
  CMD_GETDMINFOFIELDS = 0x21,
  CMD_SETDMINFOFIELDS = 0x22,
  CMD_SENDDMSTATUS = 0x23,
  CMD_SETAPPSTATUS = 0x24,
  CMD_JOIN = 0x25,
  CMD_LEAVENETWORK = 0x26,
  CMD_SUSPENDMODEMCOMM = 0x27,
  CMD_GETNEXTTXMAXPAYLOAD = 0x28,
  CMD_REQUESTTX = 0x29,
  CMD_EMERGENCYTX = 0x2A,
  CMD_UPLOADINIT = 0x2B,
  CMD_UPLOADDATA = 0x2C,
  CMD_UPLOADSTART = 0x2D,
  CMD_STREAMINIT = 0x2E,
  CMD_SENDSTREAMDATA = 0x2F,
  CMD_STREAMSTATUS = 0x30,
  CMD_GETBUDHAMODE = 0x31,
  CMD_SETBUDHAMODE = 0x32,
  CMD_GETBUDHACONF = 0x33,
  CMD_SETBUDHACONF = 0x34,
  CMD_GETDEVICEINFO = 0x35,
  CMD_SETDEVICEINFO = 0x36,
};

// LoRaWAN Modem response codes
enum
{
  RC_OK = 0,
  RC_UNKNOWN = 1,
  RC_NOTIMPL = 2,
  RC_NOTINIT = 3,
  RC_INVALID = 4,
  RC_BUSY = 5,
  RC_FAIL = 6,
  RC_BADFMT = 7,        // Bad format
  RC_BADCRC = 8,
  RC_BADSIG = 9,        // Bad signature
  RC_BADSIZE = 10,
  RC_NOSESSION = 11,    // No session available
  RC_FRAMEERROR = 15,
};

// LoRaWAN Modem events
enum
{
  EVT_RESET = 0x00,
  EVT_ALARM = 0x01,
  EVT_JOINED = 0x02,
  EVT_TXDONE = 0x03,
  EVT_DOWNDATA = 0x04,
  EVT_UPLOADDONE = 0x05,
  EVT_SETCONF = 0x06,
  EVT_MUTE = 0x07,
  EVT_STREAMDONE = 0x08,
  EVT_LINKSTATUS = 0x09,
  EVT_JOINFAIL = 0x0A,
};

// LoRaWAN Modem status
enum
{
  STAT_BROWNOUT = (1 << 0),
  STAT_CRASH = (1 << 1),
  STAT_MUTE = (1 << 2),
  STAT_JOINED = (1 << 3),
  STAT_SUSPEND = (1 << 4),
  STAT_UPLOAD = (1 << 5),
  STAT_JOINING = (1 << 6),
  STAT_STREAM = (1 << 7),
};

// Downlink request types
enum
{
  REQ_RESET = 0x00,
  REQ_FUOTA = 0x01,
  REQ_UPLOADDONE = 0x02,
  REQ_GETINFO = 0x03,
  REQ_SETCONF = 0x04,
  REQ_REJOIN = 0x05,
  REQ_MUTE = 0x06,
  REQ_SETDMINFO = 0x07,
  REQ_STREAM = 0x08,
  REQ_ALCSYNC = 0x09,
};

// Uplink info tags (TLV?)
enum
{
  INF_STATUS = 0x00,
  INF_CHARGE = 0x01,
  INF_VOLTAGE = 0x02,
  INF_TEMP = 0x03,
  INF_SIGNAL = 0x04,
  INF_UPTIME = 0x05,
  INF_RXTIME = 0x06,
  INF_FIRMWARE = 0x07,
  INF_ADRMODE = 0x08,
  INF_JOINEUI = 0x09,
  INF_INTERVAL = 0x0A,
  INF_REGION = 0x0B,
  INF_RFU = 0x0C,
  INF_CRASHLOG = 0x0D,
  INF_UPLOAD = 0x0E,
  INF_RSTCOUNT = 0x0F,
  INF_DEVEUI = 0x10,
  INF_OWNCNT = 0x11,
  INF_SESSION = 0x12,
  INF_CHIPEUI = 0x13,
  INF_STREAM = 0x14,
  INF_STREAMPAR = 0x15,
  INF_APPSTATUS = 0x16,
  INF_ALCSYNC = 0x17,
  INF_MAX
};

// DM interval units
enum
{
  UNIT_S = 0x00,
  UNIT_D = 0x40,
  UNIT_H = 0x80,
  UNIT_M = 0xC0,
};

// ADR profiles
enum
{
  ADRP_NETWORK = 0x00,
  ADRP_LONGRANGE = 0x01,
  ADRP_LOWPOWER = 0x02,
  ADRP_CUSTOM = 0x03,
};

class LoRaWANModem
{
private:
  Stream *modemStream;
  Stream *debugStream;
  ttn_fp_t fp;
  uint8_t sf;
  uint8_t fsb;
  bool adr;
  char buffer[512];
  bool baudDetermined = false;
  void (*messageCallback)(const uint8_t *payload, size_t size, port_t port);

  void clearReadBuffer();
  size_t readLine(char *buffer, size_t size, uint8_t attempts = 3);
  size_t readResponse(uint8_t prefixTable, uint8_t indexTable, uint8_t index, char *buffer, size_t size);
  size_t readResponse(uint8_t table, uint8_t index, char *buffer, size_t size);

  void debugPrintIndex(uint8_t index, const char *value = NULL);
  void debugPrintMessage(uint8_t type, uint8_t index, const char *value = NULL);

  void autoBaud();
  void configureEU868();
  void configureUS915(uint8_t fsb);
  void configureAU915(uint8_t fsb);
  void configureAS920_923();
  void configureAS923_925();
  void configureKR920_923();
  void configureIN865_867();
  void configureChannels(uint8_t fsb);
  bool setSF(uint8_t sf);
  bool waitForOk();

  void sendCommand(uint8_t table, uint8_t index, bool appendSpace, bool print = true);
  bool sendMacSet(uint8_t index, const char *value);
  bool sendChSet(uint8_t index, uint8_t channel, const char *value);
  bool sendJoinSet(uint8_t type);
  bool sendPayload(uint8_t mode, uint8_t port, uint8_t *payload, size_t len);
  void sendGetValue(uint8_t table, uint8_t prefix, uint8_t index);

public:
  bool needsHardReset = false;

  LoRaWANModem(Stream &modemStream, Stream &debugStream, ttn_fp_t fp, uint8_t sf = TTN_DEFAULT_SF, uint8_t fsb = TTN_DEFAULT_FSB);
  void reset(bool adr = true);
  void resetHard(uint8_t resetPin);
  void showStatus();
  size_t getHardwareEui(char *buffer, size_t size);
  size_t getAppEui(char *buffer, size_t size);
  uint16_t getVDD();
  void onMessage(void (*cb)(const uint8_t *payload, size_t size, port_t port));
  bool provision(const char *appEui, const char *appKey);
  bool join(const char *appEui, const char *appKey, int8_t retries = -1, uint32_t retryDelay = 10000);
  bool join(int8_t retries = -1, uint32_t retryDelay = 10000);
  bool personalize(const char *devAddr, const char *nwkSKey, const char *appSKey);
  bool personalize();
  ttn_response_t sendBytes(const uint8_t *payload, size_t length, port_t port = 1, bool confirm = false, uint8_t sf = 0);
  ttn_response_t poll(port_t port = 1, bool confirm = false);
  void sleep(uint32_t mseconds);
  void wake();
  void saveState();
  void linkCheck(uint16_t seconds);
  uint8_t getLinkCheckGateways();
  uint8_t getLinkCheckMargin();
};

#endif
