#ifndef _STATE_MACHINE_MAIN_H
#define _STATE_MACHINE_MAIN_H

#include <ArduinoJson.h>

#include <buttonHandlerBase.h>
#include <flightData.h>
#include <flightLog.h>
#include <loopThrottle.h>
#include "sensors.h"
#include "settings.h"

#define ALTITUDE_LIFTOFF 20

#define PREFERENCE_KEY_ALTITUDE_AIRBORNE_ASCENT "smSRAA"
#define PREFERENCE_KEY_ALTITUDE_AIRBORNE_DESCENT "smSRAD"
#define PREFERENCE_KEY_ALTITUDE_GROUND "smSRG"
#define PREFERENCE_KEY_ALTITUDE_LIFTOFF "smAL"
#define PREFERENCE_KEY_LAUNCH_DETECT "smLD"

// Sample rate is in milliseconds
// Based on Eggtimer Quantum documentation
// https://eggtimerrocketry.com/wp-content/uploads/2024/02/Eggtimer-Quantum-1_09G.pdf, page 25
#define SAMPLE_RATE_ABORTED 2
#define SAMPLE_RATE_AIRBORNE_ASCENT 50
#define SAMPLE_RATE_AIRBORNE_DESCENT 5
#define SAMPLE_RATE_GROUND 50
#define SAMPLE_RATE_LANDED 5
#define SAMPLE_RATE_SENSORS 50
#define SAMPLE_MEASURES_ABORTED 20
#define SAMPLE_MEASURES_APOGEE 5
#define SAMPLE_MEASURES_LANDED 10

struct stateMachineSettingsSampleMeasuresStruct {
    int aborted = SAMPLE_MEASURES_ABORTED;
    int apogee = SAMPLE_MEASURES_APOGEE;
    int landed = SAMPLE_MEASURES_LANDED;
};

struct stateMachineSettingsSampleRatesStruct {
    int airborneAscent = SAMPLE_RATE_AIRBORNE_ASCENT;
    int airborneDescent = SAMPLE_RATE_AIRBORNE_DESCENT;
    int aborted = 5;
    int ground = SAMPLE_RATE_GROUND;
    int landed = SAMPLE_RATE_LANDED;
};

struct stateMachineSettingsStruct {
    int altitudeLiftoff = ALTITUDE_LIFTOFF;
    settingsSampleMeasuresStruct sampleMeasures;
    settingsSampleRatesStruct sampleRates;
    // Assumed environmental values
    float altitudeBarometer = 1650.3;  // meters ... map readings + barometer position
    int timeoutRecording = 300 * 10000;
    int timeOutTimeToApogee = 20000;
};

typedef void (*StateMachineStateFunctionPtr)(flightStates state, unsigned long timestamp, unsigned long deltaElapsed);
typedef void (*StateMachineStateChangedFunctionPtr)(flightStates state, flightStates stateFrom, unsigned long timestamp, unsigned long deltaElapsed);
typedef void (*StateMachineStateThottledFunctionPtr)(flightStates state, unsigned long timestamp, unsigned long deltaElapsed);
typedef void (*StateMachinePreferenceLoadFunctionPtr)(stateMachineSettingsStruct& settings);
typedef void (*StateMachinePreferenceSaveFunctionPtr)(stateMachineSettingsStruct& settings);

class stateMachine {
  public:
    stateMachine();
    void loop(unsigned long timestamp, unsigned long delta);
    void reset();
    void save(int altitudeLiftoff, int sampleRateAirborneAscent, int sampleRateAirborneDecent, int sampleRateGround);
    byte setup(flightLog* flightLog, sensors* sensors, StateMachineStateFunctionPtr stateFunc = nullptr, StateMachineStateThottledFunctionPtr stateThrottledFunc = nullptr, StateMachineStateChangedFunctionPtr stateChangedFunc = nullptr, StateMachinePreferenceLoadFunctionPtr stateLoadFunc = nullptr, StateMachinePreferenceSaveFunctionPtr stateSaveFunc = nullptr);
    flightStates state();
    char * stateName();

    int altitudeLiftoff();
    void preferencesOutput();
    int sampleRateAirborneAscent();
    int sampleRateAirborneDescent();
    int sampleRateGround();

    int altitudeLiftoffValues[10] = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };
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

    int _altitudeLiftoff = 0;
    int _altitudeGround = 0;
    int _countdownAborted = 0;
    int _countdownLanded = 0;
    flightLog* _flightLog;
    flightStates _loopState = FLIGHT_STATE_GROUND;
    StateMachineStateFunctionPtr _loopStateFunc;
    StateMachineStateChangedFunctionPtr _loopStateChangedFunc;
    StateMachineStateThottledFunctionPtr _loopStateThrottledFunc;
    StateMachinePreferenceLoadFunctionPtr _settingsLoadFunc;
    StateMachinePreferenceSaveFunctionPtr _settingsSaveFunc;
    loopThrottle _throttleAborted;
    loopThrottle _throttleAirborneAscent;
    loopThrottle _throttleAirborneDescent;
    loopThrottle _throttleLanded;
    loopThrottle _throttleGround;
    int _sampleRateAirborneAscent;
    int _sampleRateAirborneDescent;
    int _sampleRateGround;
    sensors* _sensors;
    stateMachineSettingsStruct _stateMachineSettings;
};

extern stateMachine _stateMachine;

#endif