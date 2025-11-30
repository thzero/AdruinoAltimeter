#ifndef _SENSORS_H
#define _SENSORS_H

#include <sensorsBase.h>

sensorValuesStruct sensorsBase::initialize(float verticalTolerance) {
  sensorValuesStruct data = _atmosphereSensor->initialize();
  sensorValuesStruct data2 = _imuSensor->initialize();
  _imuSensor->setVerticalTolerance(verticalTolerance);
  data.acceleration = data2.acceleration;
  data.gyroscope = data2.gyroscope;
  return data;
}

int8_t sensorsBase::initOverride(SensorOverrideFunctionPtr atmosphereFuncOverride, SensorOverrideFunctionPtr imuFuncOverride) {
  _atmosphereSensor->initOverride(atmosphereFuncOverride);
  _imuSensor->initOverride(imuFuncOverride);
  return 0;
}

void sensorsBase::integrateVelocity(sensorValuesStruct* data, unsigned long current, unsigned long delta) {
  if (data == nullptr)
    return;

  float ax_bias = 0, ay_bias = 0, az_bias = 0;
  float accelX_filtered = 0, accelY_filtered = 0, accelZ_filtered = 0;
  float velocityX = 0, velocityY = 0, velocityZ = 0;

   // Accelerometer readings in m/s^2, remove gravity and apply bias correction
  float accelX = data->acceleration.x - ax_bias;
  float accelY = data->acceleration.y - ay_bias;
  float accelZ = data->acceleration.z - 9.81 - az_bias; // remove gravity

  // Low-pass filtering
  accelX_filtered = alpha * accelX + (1 - alpha) * accelX_filtered;
  accelY_filtered = alpha * accelY + (1 - alpha) * accelY_filtered;
  accelZ_filtered = alpha * accelZ + (1 - alpha) * accelZ_filtered;

  // Velocity integration (v = v + a*delta)
  velocityX += accelX_filtered * delta;
  velocityY += accelY_filtered * delta;
  velocityZ += accelZ_filtered * delta;

  // Print filtered acceleration and calculated velocity
  // Serial.print("Accel (m/s^2): X="); Serial.print(accelX_filtered);
  // Serial.print(" Y="); Serial.print(accelY_filtered);
  // Serial.print(" Z="); Serial.println(accelZ_filtered);

  // Serial.print("Velocity (m/s): X="); Serial.print(velocityX);
  // Serial.print(" Y="); Serial.print(velocityY);
  // Serial.print(" Z="); Serial.println(velocityZ);

  data->velocity.x = velocityX;
  data->velocity.y = velocityY;
  data->velocity.z = velocityZ;
}

void sensorsBase::read(sensorValuesStruct* data, unsigned long current, unsigned long delta) {
  if (data == nullptr)
    return;

  readAtmosphere(data, current, delta);
  // readAccelerometer(data);
  // readGyroscope(data);
  readImu(data, current, delta);

  integrateVelocity(data, current, delta);
}

float sensorsBase::readAltitude() {
  return _atmosphereSensor->readAltitude();
}

float sensorsBase::readAltitude(atmosphereValues values) {
  return _atmosphereSensor->readAltitude(values);
}

void sensorsBase::sleep() {
  if (_initialized)
    return;

  Serial.println(F("Sleep sensors..."));

  _atmosphereSensor->sleep();
  _imuSensor->sleep();

  Serial.println(F("...sensors sleep successful."));
}

void sensorsBase::setupCompleted() {
  _initialized = true;
}

#endif