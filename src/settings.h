#ifndef _SEttINGS_H
#define _SEttINGS_H

#include "stateMachineConstants.h"

struct __attribute__((packed)) settingsSampleMeasuresStruct {
    unsigned aborted;
    unsigned apogee;
    unsigned landed;
};

struct __attribute__((packed)) settingsSampleRatesStruct {
    unsigned long airborneAscent;
    unsigned long airborneDescent;
    unsigned long aborted;
    unsigned long ground;
    unsigned long landed;
};

struct __attribute__((packed)) settingStateMachineStruct {
    int altitudeLiftoff = ALTITUDE_LIFTOFF;
    settingsSampleMeasuresStruct sampleMeasures;
    settingsSampleRatesStruct sampleRates;
    // Assumed environmental values
    float altitudeBarometer = 1650.3;  // meters ... map readings + barometer position
    unsigned long timeoutRecording = 600 * 1000 * 1000; // in microseconds
    unsigned long timeOutTimeToApogee = 200 * 1000 * 1000; // in microseconds
};

struct __attribute__((packed)) settingsCommunicationLoRaStruct {
  int address = -1;
  short channel = -1;
  short networkId = -1;
};

struct __attribute__((packed)) settingsCommunicationStruct {
  settingsCommunicationLoRaStruct loRa;
};

struct __attribute__((packed)) settingsStruct {
  settingsCommunicationStruct communication;
  settingStateMachineStruct stateMachine;
};

#endif