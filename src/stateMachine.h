#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

#include <buttonHandlerBase.h>
#include <flightLog.h>
#include <loopThrottle.h>
#include "sensors.h"

#define PREFERENCE_KEY_ALTITUDE_AIRBORNE_ASCENT "smSRAA"
#define PREFERENCE_KEY_ALTITUDE_AIRBORNE_DESCENT "smSRAD"
#define PREFERENCE_KEY_ALTITUDE_GROUND "smSRG"
#define PREFERENCE_KEY_ALTITUDE_LIFTOFF "smAL"
#define PREFERENCE_KEY_LAUNCH_DETECT "smLD"

enum loopStates {
  STATEMACHINE_ABORTED = 100,
  STATEMACHINE_AIRBORNE_ASCENT = 101,
  STATEMACHINE_AIRBORNE_DESCENT = 1022,
  STATEMACHINE_GROUND = 103,
  STATEMACHINE_LANDED = 104
};

typedef void (*StateMachineStateFunctionPtr)(loopStates state, unsigned long timestamp, unsigned long deltaElapsed);
typedef void (*StateMachineStateChangedFunctionPtr)(loopStates state, loopStates stateFrom, unsigned long timestamp, unsigned long deltaElapsed);
typedef void (*StateMachineStateThottledFunctionPtr)(loopStates state, unsigned long timestamp, unsigned long deltaElapsed);
typedef void (*StateMachineLedBlinkFunctionPtr)(unsigned long delta, int state);

struct stateMachineDefaultsStruct {
    int altitudeLiftoff = 20;
    int sampleRateAirborneAscent = 50;
    int sampleRateAirborneDescent = 2;
    int sampleRateAborted = 5;
    int sampleRateGround = 50;
    int sampleRateLanded = 5;
    int sampleMeasuresAborted = 20;
    int sampleMeasuresApogee = 5;
    int sampleMeasuresLanded = 10;
    // Assumed environmental values
    float altitudeBarometer = 1650.3;  // meters ... map readings + barometer position
    int timeoutRecording = 300 * 10000;
    int timeOutTimeToApogee = 20000;
};

class stateMachine {
  public:
    stateMachine();
    void loop(unsigned long timestamp, unsigned long delta);
    void reset();
    void save(int launchDetect, int sampleRateAirborneAscent, int sampleRateAirborneDecent, int sampleRateGround);
    byte setup(flightLog* flightLog, sensors* sensors, StateMachineStateFunctionPtr stateFunc, StateMachineStateThottledFunctionPtr stateThrottledFunc, StateMachineStateChangedFunctionPtr stateChangedFunc);
    loopStates state();

    int launchDetect();
    void preferencesOutput();
    int sampleRateAirborneAscent();
    int sampleRateAirborneDescent();
    int sampleRateGround();

    int launchDetectValues[10] = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };
    int sampleRateAirborneAscentValues[4] = { 15, 20, 25, 30 };
    int sampleRateAirborneDecentValues[8] = { 1, 2, 3, 4, 5, 6, 8, 10 };
    int sampleRateGroundValues[8] = { 5, 10, 15, 20, 25, 30, 35, 40 };
    
  private:
    void loopStateABORTED(unsigned long timestamp, unsigned long deltaElapsed);
    void loopStateABORTEDToGROUND(unsigned long timestamp, unsigned long deltaElapsed);
    void loopStateAIRBORNEToABORTED(unsigned long timestamp, unsigned long deltaElapsed, char message1[], char message2[]);
    float loopStateAIRBORNE(unsigned long currentTimestamp, long diffTime);
    void loopStateAIRBORNE_ASCENT(unsigned long timestamp, unsigned long deltaElapsedElapsed);
    void loopStateAIRBORNE_ASCENTToAIRBORNE_DESCENT(unsigned long timestamp, unsigned long deltaElapsed);
    void loopStateAIRBORNE_DESCENT(unsigned long timestamp, unsigned long deltaElapsedElapsed);
    void loopStateAIRBORNE_DESCENTToLANDED(unsigned long timestamp, unsigned long deltaElapsed);
    void loopStateLANDED(unsigned long timestamp, unsigned long deltaElapsedElapsed);
    void loopStateLANDEDToGROUND(unsigned long timestamp, unsigned long deltaElapsed);
    void loopStateToGROUND(unsigned long timestamp, unsigned long deltaElapsed);
    void loopStateGROUND(unsigned long timestamp, unsigned long deltaElapsedElapsed);
    void loopStateGROUNDToAIRBORNE_ASCENT(unsigned long timestamp, unsigned long deltaElapsed);
    int _checkValues(int values[], int value, int defaultValue, int size);
    void _displaySettings();

    int _altitudeLiftoff = 20;
    int _altitudeGround = 0;
    int _countdownAborted = 0;
    int _countdownLanded = 0;
    flightLog* _flightLog;
    loopStates _loopState = STATEMACHINE_GROUND;
    StateMachineStateFunctionPtr _loopStatedFunc;
    StateMachineStateChangedFunctionPtr _loopStateChangedFunc;
    StateMachineStateThottledFunctionPtr _loopStateThrottledFunc;
    loopThrottle _throttleAborted;
    loopThrottle _throttleAirborneAscent;
    loopThrottle _throttleAirborneDescent;
    loopThrottle _throttleLanded;
    loopThrottle _throttleGround;
    int _sampleRateAirborneAscent;
    int _sampleRateAirborneDescent;
    int _sampleRateGround;
    sensors* _sensors;
};

extern stateMachineDefaultsStruct stateMachineDefaults;
extern stateMachine _stateMachine;

#endif