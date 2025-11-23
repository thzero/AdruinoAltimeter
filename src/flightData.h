#ifndef _FLIGHT_DATA_H
#define _FLIGHT_DATA_H

#include <stdint.h>

enum flightStates {
  FLIGHT_STATE_ABORTED = 100,
  FLIGHT_STATE_AIRBORNE_ASCENT = 101,
  FLIGHT_STATE_AIRBORNE_DESCENT = 1022,
  FLIGHT_STATE_GROUND = 103,
  FLIGHT_STATE_LANDED = 104
};

struct flightDataStruct {
  float altitudeApogee;
  float altitudeApogeeFirstMeasure;
  float altitudeCurrent;
  float altitudeInitial;
  float altitudeLast;
  float altitudeLaunch;
  float altitudeTouchdown;
  unsigned long epochS = 0;
  unsigned long timestampApogee = 0;
  unsigned long timestampApogeeFirstMeasure = 0;
  unsigned long timestampCurrent = 0;
  unsigned long timestampLaunch = 0;
  unsigned long timestampPrevious = 0;
  unsigned long timestampTouchdown = 0;
};

struct flightDataTraceStruct {
  float accelX;
  float accelY;
  float accelZ;
  float altitude;
  long diffTime;
  float gyroX;
  float gyroY;
  float gyroZ;
  float magnetometerX;
  float magnetometerY;
  float magnetometerZ;
  float humidity;
  float pressure;
  float temperature;
  float velocity;
};

struct __attribute__((packed)) flightDataAccelerometerValues {
  float x;
  float y;
  float z;
};

struct __attribute__((packed)) flightDataAtmosphereValues {
  float altitude;
  float altitudeInitial;
  float humidity;
  float humidityInitial;
  float pressure;
  float pressureInitial;
  float temperature;
  float temperatureInitial;
};

struct __attribute__((packed)) flightDataGPSValues {
  float altitude;
  float altitudeFiltered;
  bool altitudeValid;
  float altitudeMSL;
  float altitudeMSLFiltered;
  bool altitudeMSLValid;
  float altitudeGeoidSep;
  float altitudeGeoidSepFiltered;
  bool altitudeGeoidSepValid;
  int8_t fix;
  bool fixValid;
  int32_t fixAge;
  int32_t fixAgeFiltered;
  bool fixAgeValid;
  int8_t fixType;
  bool fixTypeValid;
  float hdop;
  float hdopFiltered;
  bool hdopValid;
  float latitude;
  float latitudeFiltered;
  bool latitudeValid;
  float longitude;
  float longitudeFiltered;
  bool longitudeValid;
  float pdop;
  float pdopFiltered;
  bool pdopValid;
  uint16_t satellites;
  uint16_t satellitesFiltered;
  bool satellitesValid;
  float vdop;
  float vdopFiltered;
  bool vdopValid;
};

struct __attribute__((packed)) flightDataGyroscopeValues {
  float x;
  float y;
  float z;
};

struct __attribute__((packed)) flightDataMagnetometerValues {
  float x;
  float y;
  float z;
};

struct __attribute__((packed)) flightDataVelocityValues {
  float x;
  float y;
  float z;
};

struct __attribute__((packed)) flightDataTraceStruct2 {
  long diffTime;
  uint8_t state;
  flightDataAccelerometerValues acceleration;
  flightDataAtmosphereValues atmosphere;
  flightDataGPSValues gps;
  flightDataGyroscopeValues gyroscope;
  flightDataMagnetometerValues magnetometer;
  flightDataVelocityValues velocity;
};

struct flightMinAndMaxStruct {
  long duration;
  float accelXMax;
  float accelXMin;
  float accelYMin;
  float accelYMax;
  float accelZMin;
  float accelZMax;
  float altitudeMax;
  float altitudeMin;
  float humidityMax;
  float humidityMin;
  float pressureMax;
  float pressureMin;
  float temperatureMax;
  float temperatureMin;
  float velocityMax;
  float velocityMin;
};

struct flightDataNumberStruct {
    int * numbers;
    int size;
};

#endif