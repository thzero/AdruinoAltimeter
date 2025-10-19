#include <Arduino.h>

#include "communicationRadioLoRa.h"

byte CommunicationRadioLoRa::setup(HardwareSerial* port, int address, int networkId, int baud) {
    if (port == nullptr)
        return 1;

    _port = port;
    _baud = baud;
    if (_baud == -1)
        _baud = 9600;
    _address = address;
    _networkId = networkId;

    Serial.println(F("\tSetup communication radio LoRa Serial..."));
    _port->setTimeout(10);
    _port->begin(baud);
    Serial.println(F("\t...setup communication radio LoRa Serial finished."));
    
    return 0;
}