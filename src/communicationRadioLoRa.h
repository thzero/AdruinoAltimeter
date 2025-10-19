#ifndef _COMMUNICATION_RADIO_LORA_H
#define _COMMUNICATION_RADIO_LORA_H

#include <stdint.h>
#include <Arduino.h>
#include <limits.h>

#include <communicationData.h>
#include <communicationRadio.h>

// #define DEBUG
// #define DEBUG_COMMUNICATION
// #define DEBUG_COMMUNICATION_COMMAND
// #define DEBUG_COMMUNICATION_INTERNAL
// #define DEBUG_COMMUNICATION_PROCESS
// #define DEBUG_COMMUNICATION_QUEUE
// #define DEBUG_COMMUNICATION_READ
// #define DEBUG_COMMUNICATION_SEND

class CommunicationRadioLoRa: public CommunicationRadio {
  public:
    CommunicationRadioLoRa() {
    }

    virtual byte setup(HardwareSerial* port, int address = -1, int networkId = -1, int baud = -1);
    // virtual byte setup(HardwareSerial* port, uint8_t pin_m0 = 4, uint8_t pin_m1 = 5, uint8_t pin_aux = -1, int address = -1, int networkId = -1, int baud = -1);
    int process(unsigned long timestamp, unsigned long delta);

  protected:
    int _baud;
    int _address;
    int _networkId;
    HardwareSerial* _port;
};

#endif