#include "radioLoRa.h"
#include "radioLoRaEbyte.h"

byte radioLoRaEbyte::setup(HardwareSerial* port, uint8_t pin_m0, uint8_t pin_m1, uint8_t pin_aux, int baud) {
    byte results = radioLoRa::setup(port, pin_m0, pin_m1, pin_aux, baud);
    if (results > 0)
        return results;

    Serial.println(F("\tSetup radio LORA transceiver..."));

    bool found = _lora.init(_port, pin_m0, pin_m1, pin_aux, &Serial);
    Serial.print(F("Radio LORA transceiver found: "));
    Serial.println(found);
    if (!found) {
        Serial.println(F("\t...setup radio LORA transceiver failed."));
        return 1;
    }

    int baudRate = _lora.GetUARTBaudRate();
    Serial.printf(F("radioLoRaEbyte::setup.baudRate: %d"), baudRate);
    _baud = 1200;
    if (baudRate > 0)
        _baud = 1200 * (1 << 5);
    Serial.printf(F("radioLoRaEbyte::setup._baud: %d"), _baud);

    // you can print all parameters and is good for debugging
    // if your units will not communicate, print the parameters
    // for both sender and receiver and make sure air rates, channel
    // and address is the same
    _lora.PrintParameters();

    Serial.println(F("\t...setup radio LORA transceiver finished."));

    return 0;
}

void radioLoRaEbyte::process(unsigned long timestamp, unsigned long delta) {
}

void radioLoRaEbyte::write(char* chars) {
    _port->write(chars);
}

void radioLoRaEbyte::write(uint8_t* byteArray, size_t length) {
    _port->write(byteArray, length);
}