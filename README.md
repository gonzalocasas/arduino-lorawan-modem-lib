# LoRaWAN Modem Arduino Library

[![Build Status](https://travis-ci.org/ttn-zh/arduino-lorawan-modem-lib.svg?branch=master)](https://travis-ci.org/ttn-zh/arduino-lorawan-modem-lib)

This is an [Arduino Library](https://www.arduino.cc/en/Guide/Libraries) for Arduino devices supporting a LoRaWAN Serial/Soft Modem to communicate to [The Things Network](https://www.thethingsnetwork.org).

## Installation

* Install the library by [Using the Library Manager](https://www.arduino.cc/en/Guide/Libraries#toc3)
* **OR** by [Importing the .zip library](https://www.arduino.cc/en/Guide/Libraries#toc4) using either the [master](https://github.com/ttn-zh/arduino-lorawan-modem-lib/archive/master.zip) or one of the [releases](https://github.com/ttn-zh/arduino-lorawan-modem-lib/releases) ZIP files.

## Documentation

* API Reference:
  * [LoRaWANModem](docs/LoRaWANModem.md)
  * [LoRaWANMessage](docs/LoRaWANMessage.md)
* [The Things Network Documentation](https://www.thethingsnetwork.org/docs/devices/arduino/)

## Examples

The library comes with [examples](examples). After installing the library you need to restart the Arduino IDE before they can be found under **File > Examples > LoRaWANModem**.

## Credits

The library is a direct port of the excellent [`The Things Network` library for Arduino Devices](https://github.com/TheThingsNetwork/arduino-device-lib) by [Johan Stokking et al](AUTHORS), and it (mostly) preserves API compatibility to the original.
