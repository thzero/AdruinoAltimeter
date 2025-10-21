#ifndef _COMMUNICATION_RADIO_LORA_H
#define _COMMUNICATION_RADIO_LORA_H

#include <stdint.h>
#include <Arduino.h>
#include <limits.h>

#include <communicationData.h>
#include <communicationRadio.h>

// #define DEBUG_COMMUNICATION_RADIO_LORA

const int COMMUNICATION_MAX_MESSAGE_LENGTH = 255;

class CommunicationRadioLoRa: public CommunicationRadio {
  public:
    CommunicationRadioLoRa() {
    }

    virtual byte setup(HardwareSerial* port, int address = -1, int networkId = -1, int baud = -1);
    // virtual byte setup(HardwareSerial* port, uint8_t pin_m0 = 4, uint8_t pin_m1 = 5, uint8_t pin_aux = -1, int address = -1, int networkId = -1, int baud = -1);
    int available() override;
    int process(unsigned long timestamp, unsigned long delta);
    int read() override;
    size_t read(CommunicationHandlerFunctionPtr func, unsigned long timestamp, unsigned long delta) override;
    void writeBytes(uint8_t* byteArray, size_t length) override;
    void writeChars(const char* chars) override;

  protected:
    int _baud;
    int _address;
    int _networkId;
    HardwareSerial* _port;

    char _message[COMMUNICATION_MAX_MESSAGE_LENGTH];
    int _messageIndex = 0;
};

#endif