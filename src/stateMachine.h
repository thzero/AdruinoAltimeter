#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

#include <buttonHandlerBase.h>
#include <loopThrottle.h>

#include "flightData.h"
#include "flightLog.h"
#include "sensors.h"
#include "settings.h"
#include "stateMachineConstants.h"

#define DEV
#define DEV_SIM
// #define DEBUG_ALTIMETER

#define PREFERENCE_KEY_ALTITUDE_AIRBORNE_ASCENT "smSRAA"
#define PREFERENCE_KEY_ALTITUDE_AIRBORNE_DESCENT "smSRAD"
#define PREFERENCE_KEY_ALTITUDE_GROUND "smSRG"
#define PREFERENCE_KEY_ALTITUDE_LAUNCH_DETECT_OFFSET "smAL"
#define PREFERENCE_KEY_LAUNCH_DETECT "smLD"

typedef void (*StateMachineStateFunctionPtr)(flightStates state, unsigned long timestamp, unsigned long deltaElapsed);
typedef void (*StateMachineStateChangedFunctionPtr)(flightStates state, flightStates stateFrom, unsigned long timestamp, unsigned long deltaElapsed);
typedef void (*StateMachineStateThottledFunctionPtr)(flightStates state, unsigned long timestamp, unsigned long deltaElapsed);
typedef void (*StateMachinePreferenceLoadFunctionPtr)(settingStateMachineStruct& settings);
typedef void (*StateMachinePreferenceSaveFunctionPtr)(settingStateMachineStruct& settings);

class stateMachine {
  public:
    stateMachine();
    int altitudeOffsetGround();
    int altitudeLaunchDetectOffset();
    int altitudeInitial();
    void initializeSensors();
    void loop(unsigned long timestamp, unsigned long delta);
    void preferencesOutput();
    accelerometerValues readSensorAccelerometer();
    float readSensorAltitude();
    atmosphereValues readSensorAtmosphere();
    gyroscopeValues readSensorGyroscope();
    magnetometerValues readSensorMagnetometer();
    void reset();
    void returnToGround();
    int sampleRateAirborneAscent();
    int sampleRateAirborneDescent();
    int sampleRateGround();
    void save(int altitudeLaunchDetectOffset, int sampleRateAirborneAscent, int sampleRateAirborneDecent, int sampleRateGround);
    byte setup(flightLog* flightLog, sensors* sensors, StateMachineStateFunctionPtr stateFunc = nullptr, StateMachineStateThottledFunctionPtr stateThrottledFunc = nullptr, StateMachineStateChangedFunctionPtr stateChangedFunc = nullptr, StateMachinePreferenceLoadFunctionPtr stateLoadFunc = nullptr, StateMachinePreferenceSaveFunctionPtr stateSaveFunc = nullptr);
    flightStates state();
    const char * stateName();
    void updateTrace(unsigned long currentTimestamp, long diffTime);
    void updateTrace(unsigned long currentTimestamp, long diffTime, atmosphereValues atmosphereValuesO, float altitudeDelta);

    sensorValuesStruct sensorData;

    int altitudeLaunchDetectOffsetValues[10] = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };
    int sampleRateAirborneAscentValues[4] = { 15, 20, 25, 30 };
    int sampleRateAirborneDecentValues[8] = { 1, 2, 3, 4, 5, 6, 8, 10 };
    int sampleRateGroundValues[8] = { 5, 10, 15, 20, 25, 30, 35, 40 };
    
  private:
    void loopStateABORTED(unsigned long timestamp, unsigned long deltaElapsed);
    void loopStateABORTEDToGROUND(unsigned long timestamp, unsigned long deltaElapsed);
    void loopStateAIRBORNEToABORTED(unsigned long timestamp, unsigned long deltaElapsed, const __FlashStringHelper *message1, const __FlashStringHelper *message2);
    float loopStateAIRBORNE(unsigned long currentTimestamp, long diffTime);
    void loopStateAIRBORNE_ASCENT(unsigned long timestamp, unsigned long deltaElapsedElapsed);
    void loopStateAIRBORNE_ASCENTToAIRBORNE_DESCENT(unsigned long timestamp, unsigned long deltaElapsed);
    void loopStateAIRBORNE_DESCENT(unsigned long timestamp, unsigned long deltaElapsedElapsed);
    void loopStateAIRBORNE_DESCENTToLANDED(unsigned long timestamp, unsigned long deltaElapsed);
    void loopStateLANDED(unsigned long timestamp, unsigned long deltaElapsedElapsed);
    void loopStateLANDEDToGROUND(unsigned long timestamp, unsigned long deltaElapsed);
    void loopStateGROUND(unsigned long timestamp, unsigned long deltaElapsedElapsed);
    void loopStateGROUNDToAIRBORNE_ASCENT(unsigned long timestamp, unsigned long deltaElapsed);
    int _checkValues(int values[], int value, int defaultValue, int size);
    void _displaySettings();

    int _altitudeLaunchDetectOffset = 0;
    int _altitudeOffsetGround = 0;
    unsigned int _countdownAborted = 0;
    unsigned int _countdownLanded = 0;
    flightLog* _flightLog;
    flightStates _loopState = FLIGHT_STATE_GROUND;
    StateMachineStateFunctionPtr _loopStateFunc;
    StateMachineStateChangedFunctionPtr _loopStateChangedFunc;
    StateMachineStateThottledFunctionPtr _loopStateThrottledFunc;
    unsigned long _sampleRateAirborneAscent;
    unsigned long _sampleRateAirborneDescent;
    unsigned long _sampleRateGround;
    sensors* _sensors;
    StateMachinePreferenceLoadFunctionPtr _settingsLoadFunc;
    StateMachinePreferenceSaveFunctionPtr _settingsSaveFunc;
    settingStateMachineStruct _stateMachineSettings;
    loopThrottle _throttleAborted;
    loopThrottle _throttleAirborneAscent;
    loopThrottle _throttleAirborneDescent;
    loopThrottle _throttleLanded;
    loopThrottle _throttleGround;
    int _accumulator = 0;
};

extern stateMachine _stateMachine;

#endif