#ifndef _SENSOR_H
#define _SENSOR_H

#include <sensorBase.h>
#include <sensorBarometer.h>
#include <sensorData.h>
#include <sensorGPS.h>
#include <sensorIMU.h>

struct sensorsSetupResults {
  byte atmosphere = 0;
  byte gps = 0;
  byte imu = 0;
  byte sensors = 0;
};

extern void setupSensorsCompleted();
extern sensorsSetupResults setupSensorsStart();

class sensors {
  public:
    sensorValuesStruct initialize();
    float readAltitude();
    float readAltitude(atmosphereValues values);
    void readAccelerometer(sensorValuesStruct* data);
    void readAtmosphere(sensorValuesStruct* data);
    void readGps(sensorValuesStruct* data);
    void readGyroscope(sensorValuesStruct* data);
    void sleep();
    sensorsSetupResults setup(sensorBarometer* atmosphereSensor, sensorIMU* imuSensor, sensorGPS* gps);
    void setupCompleted();
    void calibrationResetCommand(uint8_t* commandBuffer, uint16_t commandBufferLength);
  private:
    sensorBarometer* _atmosphereSensor;
    sensorGPS* _gps;
    sensorIMU* _imuSensor;
    bool _initialized;
};

extern sensors _sensors;
extern void calibrationResetCommand(uint8_t* commandBuffer, uint16_t commandBufferLength);

#endif