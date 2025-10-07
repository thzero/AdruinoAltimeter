#include "radioLoRa.h"

byte radioLoRa::setup(HardwareSerial* port, uint8_t pin_m0, uint8_t pin_m1, uint8_t pin_aux, int baud) {
    if (port == nullptr)
        return 1;

    _port = port;
    _baud = baud;

    Serial.println(F("\tSetup radio Serial..."));
    _port->setTimeout(10);
    _port->begin(9600);
    Serial.println(F("\t...radio Serial finished."));
    
    return 0;
}