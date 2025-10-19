#include "CommunicationRadioLoRaEbyte.h"

byte CommunicationRadioLoRaEbyte::setup(HardwareSerial* port, uint8_t pin_m0, uint8_t pin_m1, uint8_t pin_aux, int address, int networkId, int baud) {
    byte results = CommunicationRadioLoRa::setup(port, address, networkId, baud);
    if (results > 0)
        return results;

    Serial.println(F("\tSetup communication radio LORA transceiver..."));

    if (_port == nullptr)
         return 1;

    _port->end();
    _port->begin(9600);

    bool found = _lora.init(_port, pin_m0, pin_m1, pin_aux, &Serial);
    Serial.print(F("Communication radio LORA transceiver found: "));
    Serial.println(found);
    if (!found) {
        Serial.println(F("\t...setup communication radio LORA transceiver failed."));
        return 1;
    }

    int baudRate = _lora.GetUARTBaudRate();
    Serial.printf(F("CommunicationRadioLoRa::setup.baudRate: %d\n"), baudRate);
    _baud = 1200;
    if (baudRate > 0 && baudRate < 6)
        _baud = 1200 * (1 << baudRate);
    else if (baudRate == 6)
        _baud = 57600;
    else if (baudRate == 7)
        _baud = 115200;
    Serial.printf(F("CommunicationRadioLoRa::setup._baud: %d\n"), _baud);

    _port->end();
    _port->begin(_baud);

    // you can print all parameters and is good for debugging
    // if your units will not communicate, print the parameters
    // for both sender and receiver and make sure air rates, channel
    // and address is the same
    _lora.PrintParameters();

    Serial.println(F("\t...setup communication radio LORA transceiver finished."));

    return 0;
}

int CommunicationRadioLoRaEbyte::available() {
    if (_port == nullptr) {
        Serial.println("Error: no port setup for the LoRa radio.");
        return false;
    }
    return _port->available();
}

int CommunicationRadioLoRaEbyte::read() {
    if (_port == nullptr) {
        Serial.println("Error: no port setup for the LoRa radio.");
        return 0;
    }
    return _port->read();
}

void CommunicationRadioLoRaEbyte::writeBytes(uint8_t* byteArray, size_t length) {
    if (_port == nullptr) {
        Serial.println("Error: no port setup for the LoRa radio.");
        return;
    }

    Serial.print(F("CommunicationRadioLoRaEbyte::writeBytes: buffer length: "));
    Serial.println(length);
    Serial.println(F("CommunicationRadioLoRaEbyte::writeBytes: message bytes to send: "));
    for (size_t i = 0; i < length; i++)
        Serial.printf(F("%d "), byteArray[i]);
    Serial.println();

    _port->write(byteArray, length);
}

void CommunicationRadioLoRaEbyte::writeChars(const char* chars) {
    if (_port == nullptr) {
        Serial.println("Error: no port setup for the LoRa radio.");
        return;
    }
    _port->write(chars);
}