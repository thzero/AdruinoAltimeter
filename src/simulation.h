#ifndef _SIMULATION_H
#define _SIMULATION_H

#include <ArduinoJson.h>

#include <loopThrottle.h>
#include <sensorData.h>
#include "stateMachine.h"

#define SAMPLE_SIMULATION 1

#define DEBUG_SIM_CONFIG

struct simulationConfigStruct {
  float cd = 0.87;     // from OR 3" rocket
  float diameterIn = 5.5;
  float diameterMM = 0;
  float diameter = 0; // m  
  float frontalArea = 4.56e-3;      // m^20.0762 // from OR 3" rocket
  float mass = 1.76;          // kg // from OR 3" rocket
  float motorFuelBurnRate = 0.176;  // kg/s // from OR 3" rocket
  float motorFuelBurnRateMicro = 0.000000176;  // kg/s // from OR 3" rocket
  float motorFuelBurnTime = 1.6;    // kg/s // from OR 3" rocket
  float motorFuelMass = 0.316;      // kg // from OR 3" rocket
  float motorThrust = 2485.796;     // m/s // from OR 3" rocket
  float parachuteArea = 0;
  float parachuteDiameterIn = 5.5;
  float parachuteDiameterMM = 0;
  float parachuteDiameter = 0; // m
  float parachuteCd = 2.2;
  int sampleRate = 100;
};
typedef enum {
	simulationStatusAirborneAscent,
	simulationStatusAirborneDescent,
  simulationStatusGround,
  simulationStatusLanded
} simulationStatus;

// Very simple, and not very realistic, simulation only on the X and Y axis.
class simulation {
  public:
    simulation();
    bool isRunning();
    void outputSerialList();
    accelerometerValues readAcceleration();
    float readAltitude();
    atmosphereValues readAtmosphere();
    gyroscopeValues readGyroscope();
    magnetometerValues readMagnetometer();
    int8_t setup(JsonDocument settings);
    void simulationTask();
    void simulationTaskEnd();
    void simulationTaskStart();
#if defined(EPS32)
    void simulationTaskWrapper();
#endif
    void start(int requestedNumber, float altitudeInitial, float altitudeFinal);
    void stop();

  private:
    float AirDensity = 1.292;        // kg/m^3
    float AirDensityScale = 5600.0;  // m -- height at which density is halved
    float EarthMass = 5.97e24;       // kg
    float EarthRadius = 6.3e6;       // m
    float GravConstant = 9.8;          // m/s^2
    int SettleFinal = 15;
    int SettleStart = 15;

    float _acceleration;
    bool _airborneApogee = false;
    float _altitudeApogee;
    float _altitudeApogeeMeasures;
    float _altitudeCurrent;
    float _altitudeEnding;
    float _altitudeFlightLast;
    float _altitudeInitial;
    unsigned long _burnoutTime; // microseconds
    simulationConfigStruct _config;
    JsonDocument _configs;
    unsigned long _elapsedTime;
    float _forceDrag;
    float _forceGravity;
    float _forceTotal;
    float _motorThrust;  // N
    bool _running = false;
    simulationStatus _status;
    int _settleFinal;
    float _velocity;

    unsigned long _start = 0;
    int _count = 0;
    int _countHeader = 0;
    int _settle = 0;
    
    float _maxAltitude;
    float _maxVelocity;
    unsigned long _simulationTimestamp; // microseconds
    loopThrottle _simulationThrottle;

    void evaluateTimestep(unsigned long deltaT, float drag, float Mr, float Ft);
    void outputPrint(unsigned long delta, float mass, float thrust, float altitude, float airDensity, float drag, bool burnout, float apogeeDelta);
    void outputPrintHeader();
    void loopStep(unsigned long deltaT, bool output, bool outputHeader);
};

extern simulation _simulation;
extern simulationConfigStruct simulationConfigDefault;

extern int8_t setupSimulation(JsonDocument settings);

#endif