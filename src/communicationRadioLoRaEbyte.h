#ifndef _COMMUNICATION_RADIO_LORA_EBYTE_H
#define _COMMUNICATION_RADIO_LORA_EBYTE_H

#include <stdint.h>
#include <Arduino.h>
#include <limits.h>
#include <EBYTE.h>

#include "communicationRadioLoRa.h"

class CommunicationRadioLoRaEbyte: public CommunicationRadioLoRa {
  public:
    CommunicationRadioLoRaEbyte() {
    }

    byte setup(HardwareSerial* port, uint8_t pin_m0 = 4, uint8_t pin_m1 = 5, uint8_t pin_aux = -1, int address = -1, int networkId = -1, int baud = -1);
  private:
    EBYTE _lora;
};

#endif