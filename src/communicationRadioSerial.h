#ifndef _COMMUNICATION_RADIO_SERIAL_H
#define _COMMUNICATION_RADIO_SERIAL_H

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

class CommunicationRadioSerial: public CommunicationRadio {
  public:
    CommunicationRadioSerial() {
    }

    virtual byte setup(HardwareSerial* port, int baud = -1);
    int available() override;
    int read() override;
    void writeBytes(uint8_t* byteArray, size_t length) override;
    void writeChars(const char* chars) override;

  protected:
    int _baud;
    HardwareSerial* _port;
};

#endif