#ifndef _RADIO_LORA_EBYTE_H
#define _RADIO_LORA_EBYTE_H

#include <stdint.h>
#include <Arduino.h>
#include <limits.h>
#include <EBYTE.h>

#include "radioLoRa.h"
#include "radioLoRaEbyte.h"

// #define DEBUG

class radioLoRaEbyte: public radioLoRa {
  public:
    radioLoRaEbyte() {
    }

    void process(unsigned long timestamp, unsigned long delta) override;
    byte setup(HardwareSerial* port, uint8_t pin_m0 = 4, uint8_t pin_m1 = 5, uint8_t pin_aux = -1, int baud = -1) override;
    void write(char* chars) override;
    void write(uint8_t* byteArray, size_t length) override;
  private:
    EBYTE _lora;
};

#endif