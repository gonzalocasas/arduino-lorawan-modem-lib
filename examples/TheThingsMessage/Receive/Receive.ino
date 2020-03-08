#include <LoRaWANModem.h>
#include <LoRaWANMessage.h>

// Set your AppEUI and  AppKey
const char *appEui = "0000000000000000";
const char *appKey = "00000000000000000000000000000000";

#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan REPLACE_ME

LoRaWANModem modem(loraSerial, debugSerial, freqPlan);

devicedata_t data = api_DeviceData_init_default;

void setup()
{
  pinMode(LED_BUILTIN, INPUT);

  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  debugSerial.println("-- STATUS");
  modem.showStatus();

  debugSerial.println("-- JOIN");
  modem.join(appEui, appKey);

  modem.onMessage(message);

  data.has_motion = true;
  data.has_water = true;
}

void loop()
{
  // Read sensors
  data.motion = digitalRead(LED_BUILTIN) == HIGH;
  data.water = 682;

  // Encode data
  byte *buffer;
  size_t size;

  // Send standard message on port 100
  LoRaWANMessage::encodeDeviceData(&data, &buffer, &size);
  modem.sendBytes(buffer, size, 100);

  delay(10000);
}

void message(const uint8_t *payload, size_t length, port_t port)
{
  //standard message always received on port 100 or more
  if (port >= 100)
  {
    appdata_t appData = api_AppData_init_default;
    LoRaWANMessage::decodeAppData(&appData, payload, length);
  }
}
