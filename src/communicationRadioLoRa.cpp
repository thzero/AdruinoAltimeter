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

int CommunicationRadioLoRa::available() {
    if (_port == nullptr) {
        Serial.println("Error: no port setup for the LoRa radio.");
        return false;
    }

    return _port->available();
}

int CommunicationRadioLoRa::read() {
    if (_port == nullptr) {
        Serial.println("Error: no port setup for the LoRa radio.");
        return 0;
    }

    int value = _port->read();
    Serial.print("read: ");
    Serial.println(value);
    return value;
    // return _port->read();
}

size_t CommunicationRadioLoRa::read(CommunicationHandlerFunctionPtr func, unsigned long timestamp, unsigned long delta) {
    if (_port == nullptr) {
        Serial.println("Error: no port setup for the LoRa radio.");
        return -1;
    }

    if (_port->available() <= 0)
        return -1;

    Serial.println("CommunicationRadioLoRa::read.....");
    Serial.println(_port->available());
    while (_port->available() > 0) {
        char incomingChar = _port->read();
            Serial.print("Message: ");
            Serial.println(_message);
        if (incomingChar == '\n') {
            Serial.println();
            Serial.println(F("--------------"));
            _message[_messageIndex] = '\0'; // Null-terminate the string
            Serial.print("Message: ");
            Serial.println(_message);
            Serial.println(F("--------------"));
            Serial.println();
            _messageIndex = 0;
            continue;
        } 
        
        if (_messageIndex < COMMUNICATION_MAX_MESSAGE_LENGTH - 1)
        _message[_messageIndex++] = incomingChar;
    }

    return _messageIndex;
}

void CommunicationRadioLoRa::writeBytes(uint8_t* byteArray, size_t length) {
    if (_port == nullptr) {
        Serial.println("Error: no port setup for the LoRa radio.");
        return;
    }

#ifdef DEBUG_COMMUNICATION_RADIO_LORA
    Serial.print(F("CommunicationRadioLoRaEbyte::writeBytes: buffer length: "));
    Serial.println(length);
    Serial.println(F("CommunicationRadioLoRaEbyte::writeBytes: message bytes to send: "));
    for (size_t i = 0; i < length; i++)
        Serial.printf(F("%d "), byteArray[i]);
    Serial.println();
#endif

    _port->write(byteArray, length);
}

void CommunicationRadioLoRa::writeChars(const char* chars) {
    if (_port == nullptr) {
        Serial.println("Error: no port setup for the LoRa radio.");
        return;
    }
    _port->write(chars);
}