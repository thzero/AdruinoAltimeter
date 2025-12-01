#ifndef _SENSORS_H
#define _SENSORS_H

#include <sensorBase.h>
#include <sensorsBase.h>

extern void setupSensorsCompleted();
extern sensorsSetupResults setupSensorsStart();

class sensors: public sensorsBase {
  public:
    sensorsSetupResults setup(sensorBarometer* atmosphereSensor, sensorIMU* imuSensor, sensorGPS* gps, uint8_t calibrationBarometerId = 0, uint8_t calibrationBarometerStatusId = 0, uint8_t calibrationIMUId = 0, uint8_t calibrationIMUStatusId = 0) override;
    void calibrationResetCommand(uint8_t* commandBuffer, uint16_t commandBufferLength) override;
    void readAccelerometer(sensorValuesStruct* data) override;
    void readAtmosphere(sensorValuesStruct* data) override;
    void readAtmosphere(sensorValuesStruct* data, unsigned long current, unsigned long delta) override;
    void readGps(sensorValuesStruct* data) override;
    void readGyroscope(sensorValuesStruct* data) override;
    void readImu(sensorValuesStruct* data, unsigned long current, unsigned long delta) override;
    void readMagnetometer(sensorValuesStruct* data) override;
};

extern sensors _sensors;
extern void calibrationResetCommand(uint8_t* commandBuffer, uint16_t commandBufferLength);

#endif