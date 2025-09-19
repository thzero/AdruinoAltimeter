#ifndef _SENSOR_H
#define _SENSOR_H

#include "sensorBase.h"
#include "sensorData.h"
// #include <sensorBMP280.h>
#include <sensorBME280.h>
#include <sensorMPU6050.h>

extern byte setupSensors();
extern void setupSensorsCompleted();

class sensors {
  public:
    sensorValuesStruct initialize();
    float readAltitude();
    float readAltitude(atmosphereValues values);
    atmosphereValues readAtmosphere();
    accelerometerValues readAccelerometer();
    gyroscopeValues readGyroscope();
    void sleep();
    byte setup(sensorBase* atmosphereSensor, sensorBase* imuSensor);
    void setupCompleted();
    void calibrationResetCommand(uint8_t commandBuffer[], int commandBufferLength);
  private:
    sensorBase* _atmosphereSensor;
    // sensorIMU _imuSensor;
    sensorBase* _imuSensor;
    bool _initialized;
};

extern sensors _sensors;
extern void calibrationResetCommand(uint8_t commandBuffer[], int commandBufferLength);

#endif