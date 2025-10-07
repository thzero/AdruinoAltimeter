#ifndef _RADIO_LORA_H
#define _RADIO_LORA_H

#include <stdint.h>
#include <Arduino.h>
#include <limits.h>

// #define DEBUG

class radioLoRa {
  public:
    radioLoRa() {
    }

    virtual void process(unsigned long timestamp, unsigned long delta);
    virtual byte setup(HardwareSerial* port, uint8_t pin_m0 = 4, uint8_t pin_m1 = 5, uint8_t pin_aux = -1, int baud = -1);
    virtual void write(char* chars);
    virtual void write(uint8_t* byteArray, size_t length);

  protected:
    int _baud;
    HardwareSerial* _port;
};

#endif