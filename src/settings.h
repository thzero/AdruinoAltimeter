#ifndef _SEttINGS_H
#define _SEttINGS_H

#include "stateMachineConstants.h"

struct __attribute__((packed)) settingsSampleMeasuresStruct {
    int aborted;
    int apogee;
    int landed;
};

struct __attribute__((packed)) settingsSampleRatesStruct {
    int airborneAscent;
    int airborneDescent;
    int aborted;
    int ground;
    int landed;
};

struct __attribute__((packed)) settingStateMachineStruct {
    int altitudeLiftoff = ALTITUDE_LIFTOFF;
    settingsSampleMeasuresStruct sampleMeasures;
    settingsSampleRatesStruct sampleRates;
    // Assumed environmental values
    float altitudeBarometer = 1650.3;  // meters ... map readings + barometer position
    int timeoutRecording = 300 * 10000;
    int timeOutTimeToApogee = 20000;
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