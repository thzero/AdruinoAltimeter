#ifndef _STATE_MACHINE_SYNC_H
#define _STATE_MACHINE_SYNC_H

#include <ArduinoJson.h>

#include "flightData.h"
#include "stateMachineConstants.h"

typedef void (*StateMachineStateFunctionPtr)(flightStates state, unsigned long timestamp, unsigned long deltaElapsed);
typedef void (*StateMachineStateChangedFunctionPtr)(flightStates state, flightStates stateFrom, unsigned long timestamp, unsigned long deltaElapsed);

class stateMachineSync {
  public:
    stateMachineSync();
    void loop(unsigned long timestamp, unsigned long delta);
    void setState(flightStates state, unsigned long timestamp, unsigned long deltaElapsed);
    byte setup(StateMachineStateFunctionPtr stateFunc = nullptr, StateMachineStateChangedFunctionPtr stateChangedFunc = nullptr);
    flightStates state();
    const char * stateName();

    int altitudeOffsetLiftoff();
    int sampleRateAirborneAscent();
    int sampleRateAirborneDescent();
    int sampleRateGround();
    void setAltitudeOffsetLiftoff(int altitudeOffsetLiftoff);
    void setSampleRateAirborneAscent(int altitudeAirborneDescent);
    void setSampleRateAirborneDescent(int altitudeAirborneDescent);
    void setSampleRateGround(int altitudeGround);

    int altitudeOffsetLiftoffValues[12] = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60 };
    int sampleRateAirborneAscentValues[10] = { 15, 20, 25, 30, 35, 40, 45, 50, 55, 60 };
    int sampleRateAirborneDecentValues[12] = { 1, 2, 3, 4, 5, 6, 8, 10, 15, 20, 25, 30 };
    int sampleRateGroundValues[12] = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60 };
    
  private:
    int _altitudeOffsetLiftoff = 0;
    int _altitudeGround = 0;
    flightStates _loopState = FLIGHT_STATE_GROUND;
    StateMachineStateFunctionPtr _loopStatedFunc;
    StateMachineStateChangedFunctionPtr _loopStateChangedFunc;
    int _sampleRateAirborneAscent;
    int _sampleRateAirborneDescent;
    int _sampleRateGround;
};

extern stateMachineSync _stateMachineSync;

#endif