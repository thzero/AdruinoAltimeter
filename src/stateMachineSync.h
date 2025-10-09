#ifndef _STATE_MACHINE_SYNC_H
#define _STATE_MACHINE_SYNC_H

#include <ArduinoJson.h>

#include "flightData.h"

typedef void (*StateMachineStateFunctionPtr)(flightStates state, unsigned long timestamp, unsigned long deltaElapsed);
typedef void (*StateMachineStateChangedFunctionPtr)(flightStates state, flightStates stateFrom, unsigned long timestamp, unsigned long deltaElapsed);

class stateMachineSync {
  public:
    stateMachineSync();
    void loop(unsigned long timestamp, unsigned long delta);
    void setState(flightStates state, unsigned long timestamp, unsigned long deltaElapsed);
    byte setup(StateMachineStateFunctionPtr stateFunc = nullptr, StateMachineStateChangedFunctionPtr stateChangedFunc = nullptr);
    flightStates state();
    char * stateName();

    int altitudeLiftoff();
    int sampleRateAirborneAscent();
    int sampleRateAirborneDescent();
    int sampleRateGround();
    void setAltitudeLiftoff(int altitudeLiftoff);
    void setSampleRateAirborneAscent(int altitudeAirborneDescent);
    void setSampleRateAirborneDescent(int altitudeAirborneDescent);
    void setSampleRateGround(int altitudeGround);
    
  private:
    int _altitudeLiftoff = 0;
    int _altitudeGround = 0;
    flightStates _loopState = FLIGHT_STATE_GROUND;
    StateMachineStateFunctionPtr _loopStatedFunc;
    StateMachineStateChangedFunctionPtr _loopStateChangedFunc;
    int _sampleRateAirborneAscent;
    int _sampleRateAirborneDescent;
    int _sampleRateGround;
};

extern stateMachineSync _stateMachine;

#endif