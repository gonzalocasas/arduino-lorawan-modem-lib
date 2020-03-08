#include <LoRaWANModem.h>

const char *appEui = "0000000000000000";
const char *appKey = "00000000000000000000000000000000";

const char *devAddr = "00000000";
const char *nwkSKey = "00000000000000000000000000000000";
const char *appSKey = "00000000000000000000000000000000";

#define loraSerial Serial1
#define debugSerial Serial

LoRaWANModem modem(loraSerial, debugSerial, TTN_FP_EU868);

LoRaWANModem modem2(loraSerial, debugSerial, TTN_FP_US915, 10);

LoRaWANModem modem3(loraSerial, debugSerial, TTN_FP_AS923_925, 10, 4);

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  modem.provision(appEui, appKey);

  modem.join(appEui, appKey);

  modem.join(appEui, appKey, 3);

  modem.join(appEui, appKey, 3, 60000);

  modem.join();

  modem.join(3);

  modem.join(3, 60000);

  modem.personalize(devAddr, nwkSKey, appSKey);

  modem.personalize();

  modem.showStatus();

  modem.onMessage(message);
}

void loop()
{
  byte payload[1] = {0x00};
  modem.sendBytes(payload, sizeof(payload));

  modem.sendBytes(payload, sizeof(payload), 2);

  modem.sendBytes(payload, sizeof(payload), 2, true);

  modem.poll();

  modem.poll(2);

  modem.poll(2, true);
}

void message(const uint8_t *payload, size_t length, port_t port) {}
