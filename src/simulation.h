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
  double mass = 1.76;          // kg // from OR 3" rocket
  double motorFuelBurnRate = 0.176;  // kg/s // from OR 3" rocket
  double motorFuelBurnRateMicro = 0.000000176;  // kg/s // from OR 3" rocket
  double motorFuelBurnTime = 1.6;    // kg/s // from OR 3" rocket
  double motorFuelMass = 0.316;      // kg // from OR 3" rocket
  double motorThrust = 2485.796;     // m/s // from OR 3" rocket
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
    int8_t setup(JsonDocument settings);
    void simulationTask();
    void simulationTaskEnd();
    void simulationTaskStart();
    void simulationTaskWrapper();
    void start(int requestedNumber, long altitudeInitial, long altitudeFinal);
    void stop();
    accelerometerValues valueAcceleration();
    double valueAltitude();

  private:
    double AirDensity = 1.292;        // kg/m^3
    double AirDensityScale = 5600.0;  // m -- height at which density is halved
    double EarthMass = 5.97e24;       // kg
    double EarthRadius = 6.3e6;       // m
    double GravConstant = 9.8;          // m/s^2
    int SettleFinal = 15;
    int SettleStart = 15;

    double _altitude;
    double _acceleration;
    bool _airborneApogee = false;
    double _altitudeApogee;
    double _altitudeApogeeMeasures;
    double _altitudeEnding;
    double _altitudeFlightLast;
    double _altitudeInitial;
    double _altitudeStarting;
    unsigned long _burnoutTime; // microseconds
    simulationConfigStruct _config;
    JsonDocument _configs;
    unsigned long _elapsedTime;
    double _forceDrag;
    double _forceGravity;
    double _forceTotal;
    double _motorThrust;  // N
    bool _running = false;
    simulationStatus _status;
    int _settleFinal;
    double _velocity;

    unsigned long _start = 0;
    int _count = 0;
    int _countHeader = 0;
    int _settle = 0;
    
    double _maxAltitude;
    double _maxVelocity;
    unsigned long _simulationTimestamp; // microseconds
    loopThrottle _simulationThrottle;

    void evaluateTimestep(unsigned long deltaT, double drag, double Mr, double Ft);
    void outputPrint(unsigned long delta, double mass, double thrust, double altitude, double airDensity, double drag, bool burnout, double apogeeDelta);
    void outputPrintHeader();
    void loopStep(unsigned long deltaT, bool output, bool outputHeader);
};

extern simulation _simulation;
extern simulationConfigStruct simulationConfigDefault;

extern int8_t setupSimulation(JsonDocument settings);

#endif