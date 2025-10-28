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

    virtual byte setup(HardwareSerial* port, int address = -1, int channel = -1, int networkId = -1, int baud = -1);
    // virtual byte setup(HardwareSerial* port, uint8_t pin_m0 = 4, uint8_t pin_m1 = 5, uint8_t pin_aux = -1, int address = -1, int networkId = -1, int baud = -1);
    int available() override;
    int process(unsigned long timestamp, unsigned long delta);
    int read() override;
    byte reset() override;
    virtual void setAddress(uint16_t address);
    virtual void setChannel(uint8_t channel);
    virtual void setNetworkId(uint8_t networkId);
    size_t read(CommunicationHandlerFunctionPtr func, unsigned long timestamp, unsigned long delta) override;
    void writeBytes(uint8_t* byteArray, size_t length) override;
    void writeChars(const char* chars) override;

  protected:
    int _baud;
    uint16_t _address = 0;
    uint16_t _channel = 0;
    uint8_t _networkId = 0;
    HardwareSerial* _port;

    char _message[COMMUNICATION_MAX_MESSAGE_LENGTH];
    int _messageIndex = 0;
};

#endif