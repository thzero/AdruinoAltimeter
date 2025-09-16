#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

#include <flightLog.h>
#include <loopThrottle.h>
#include "sensors.h"

#define PREFERENCE_KEY_ALTITUDE_AIRBORNE_ASCENT "smSRAA"
#define PREFERENCE_KEY_ALTITUDE_AIRBORNE_DESCENT "smSRAD"
#define PREFERENCE_KEY_ALTITUDE_GROUND "smSRG"
#define PREFERENCE_KEY_ALTITUDE_LIFTOFF "smAL"
#define PREFERENCE_KEY_LAUNCH_DETECT "smLD"

enum loopStates {
  ABORTED = 100,
  AIRBORNE_ASCENT = 101,
  AIRBORNE_DESCENT = 1022,
  GROUND = 103,
  LANDED = 104
};

struct loopStateMachine {
  enum loopStates current = GROUND;
};

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

typedef void (*StateMachineLedBlinkFunctionPtr)(int delta, int state);

class stateMachine {
  public:
    stateMachine();
    void loop(unsigned long timestamp, int delta);
    void reset();
    void save(int launchDetect, int sampleRateAirborneAscent, int sampleRateAirborneDecent, int sampleRateGround);
    byte setup(flightLog* flightLog, sensors* sensors, deviceCommands* deviceCommands, StateMachineLedBlinkFunctionPtr ledBlinkFunc);

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
    void loopStateABORTED(unsigned long timestamp, int deltaElapsed);
    void loopStateABORTEDToGROUND(unsigned long timestamp);
    void loopStateAIRBORNEToABORTED(char message1[], char message2[]);
    float loopStateAIRBORNE(unsigned long currentTimestamp, long diffTime);
    void loopStateAIRBORNE_ASCENT(unsigned long timestamp, int deltaElapsedElapsed);
    void loopStateAIRBORNE_ASCENTToAIRBORNE_DESCENT();
    void loopStateAIRBORNE_DESCENT(unsigned long timestamp, int deltaElapsedElapsed);
    void loopStateAIRBORNE_DESCENTToLANDED();
    void loopStateLANDED(unsigned long timestamp, int deltaElapsedElapsed);
    void loopStateLANDEDToGROUND();
    void loopStateToGROUND();
    void loopStateGROUND(unsigned long timestamp, int deltaElapsedElapsed);
    void loopStateGROUNDToAIRBORNE_ASCENT(unsigned long timestamp);
    int _checkValues(int values[], int value, int defaultValue, int size);
    void _displaySettings();

    int _altitudeLiftoff = 20;
    int _altitudeGround = 0;
    int _countdownAborted = 0;
    int _countdownLanded = 0;
    deviceCommands* _deviceCommands;
    flightLog* _flightLog;
    StateMachineLedBlinkFunctionPtr _ledBlinkFunc;
    loopStateMachine _loopState;
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