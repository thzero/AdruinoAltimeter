#ifndef _COMMUNICATION_ALTIMETER_DATA_H
#define _COMMUNICATION_ALTIMETER_DATA_H

#include "flightData.h"

struct __attribute__((packed)) communicationMonitorDataStruct {
  float cpuTemp = 0.0;
  float cpuTempMax = 0.0;
  int memoryHeap = 0;
  int memoryRam = 0;
  int memoryStack = 0;
  float voltage = 0.0;
};

struct __attribute__((packed)) communicationExternalStruct {
  long diffTime;
  uint8_t state;
  flightDataAccelerometerValues acceleration;
  flightDataAtmosphereValues atmosphere;
  flightDataGPSValues gps;
  flightDataGyroscopeValues gyroscope;
  communicationMonitorDataStruct monitor;
};

struct __attribute__((packed)) communicationInternalStruct {
  long diffTime;
  uint8_t state;
  flightDataAccelerometerValues acceleration;
  flightDataAtmosphereValues atmosphere;
  flightDataGPSValues gps;
  flightDataGyroscopeValues gyroscope;
  communicationMonitorDataStruct monitor;
};

#endif