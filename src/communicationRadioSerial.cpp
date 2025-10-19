#include <Arduino.h>

#include "communicationRadioSerial.h"

byte CommunicationRadioSerial::setup(HardwareSerial* port, int baud) {
    if (port == nullptr)
        return 1;

    _port = port;
    _baud = baud;

    Serial.println(F("\tSetup communication radio Serial..."));
    _port->setTimeout(10);
    _port->begin(baud);
    Serial.println(F("\t...setup communication radio Serial finished."));
    
    return 0;
}

int CommunicationRadioSerial::available() {
    if (_port == nullptr) {
        Serial.println("Error: no port setup for the serial radio.");
        return false;
    }
    return _port->available();
}

int CommunicationRadioSerial::read() {
    if (_port == nullptr) {
        Serial.println("Error: no port setup for the serial radio.");
        return 0;
    }
    return _port->read();
}

void CommunicationRadioSerial::writeBytes(uint8_t* byteArray, size_t length) {
    if (_port == nullptr) {
        Serial.println("Error: no port setup for the serial radio.");
        return;
    }

    Serial.print(F("CommunicationRadioSerial::writeBytes: buffer length: "));
    Serial.println(length);
    Serial.println(F("CommunicationRadioSerial::writeBytes: message bytes to send: "));
    for (size_t i = 0; i < length; i++)
        Serial.printf(F("%d "), byteArray[i]);
    Serial.println();

    _port->write(byteArray, length);
}

void CommunicationRadioSerial::writeChars(const char* chars) {
    if (_port == nullptr) {
        Serial.println("Error: no port setup for the serial radio.");
        return;
    }
    _port->write(chars);
}