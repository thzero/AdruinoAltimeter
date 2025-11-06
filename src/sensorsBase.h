#ifndef _SENSORS_BASE_H
#define _SENSORS_BASE_H

#include <sensorBase.h>
#include <sensorBarometer.h>
#include <sensorData.h>
#include <sensorGPS.h>
#include <sensorIMU.h>

// Low-pass filter coefficient (alpha)
const float alpha = 0.1; // Smaller alpha = smoother, slower response

struct sensorsSetupResults {
  byte atmosphere = 0;
  byte gps = 0;
  byte imu = 0;
  byte sensors = 0;
};

class sensorsBase {
  public:
    virtual void calibrationResetCommand(uint8_t* commandBuffer, uint16_t commandBufferLength);
    sensorValuesStruct initialize();
    int8_t initOverride(SensorOverrideFunctionPtr funcOverride);
    virtual void integrateVelocity(sensorValuesStruct* data, unsigned long current, unsigned long delta);
    virtual float readAltitude();
    virtual float readAltitude(atmosphereValues values);
    virtual void readAccelerometer(sensorValuesStruct* data);
    virtual void readAtmosphere(sensorValuesStruct* data);
    virtual void readGps(sensorValuesStruct* data);
    virtual void readGyroscope(sensorValuesStruct* data);
    virtual void sleep();
    virtual sensorsSetupResults setup(sensorBarometer* atmosphereSensor, sensorIMU* imuSensor, sensorGPS* gps, uint8_t calibrationBarometerId = 0, uint8_t calibrationBarometerStatusId = 0, uint8_t calibrationIMUId = 0, uint8_t calibrationIMUStatusId = 0);
    virtual void setupCompleted();
  protected:
    sensorBarometer* _atmosphereSensor;
    sensorGPS* _gps;
    sensorIMU* _imuSensor;
    bool _initialized;
};

#endif