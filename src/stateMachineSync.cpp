#include <debug.h>
#include "stateMachineSync.h"

stateMachineSync::stateMachineSync() {
}

int stateMachineSync::altitudeLiftoff() {
  return _altitudeLiftoff;
}

void stateMachineSync::loop(unsigned long timestamp, unsigned long deltaElapsed) {
  if (_loopStatedFunc != nullptr)
    _loopStatedFunc(_loopState, timestamp, deltaElapsed);
}

int stateMachineSync::sampleRateAirborneAscent() {
  return _sampleRateAirborneAscent;
}
int stateMachineSync::sampleRateAirborneDescent() {
  return _sampleRateAirborneDescent;
}
int stateMachineSync::sampleRateGround() {
  return _sampleRateGround;
}

void stateMachineSync::setAltitudeLiftoff(int altitudeLiftoff) {
  _altitudeLiftoff = altitudeLiftoff;
}
void stateMachineSync::setSampleRateAirborneAscent(int altitudeAirborneDescent) {
  _sampleRateAirborneAscent = altitudeAirborneDescent;
}
void stateMachineSync::setSampleRateAirborneDescent(int altitudeAirborneDescent) {
  _sampleRateAirborneDescent = altitudeAirborneDescent;
}
void stateMachineSync::setSampleRateGround(int altitudeGround) {
  _sampleRateGround = altitudeGround;
}

void stateMachineSync::setState(flightStates state, unsigned long timestamp, unsigned long deltaElapsed) {
  if (state == _loopState)
    return;

  if (_loopStateChangedFunc != nullptr)
    _loopStateChangedFunc(state, _loopState, timestamp, deltaElapsed);

  _loopState = state;
}

byte stateMachineSync::setup(StateMachineStateFunctionPtr stateFunc, StateMachineStateChangedFunctionPtr stateChangedFunc) {
  Serial.println(F("Setup state machine..."));

  _loopStatedFunc = stateFunc;
  _loopStateChangedFunc = stateChangedFunc;

  Serial.println(F("...state machine setup successful."));
  Serial.println();
  return 0;
}

flightStates stateMachineSync::state() {
  return _loopState;
}

char* stateMachineSync::stateName() {
  char* name;
  name = "";
  if (_loopState == FLIGHT_STATE_ABORTED)
    name = "Aborted";
  else if (_loopState == FLIGHT_STATE_AIRBORNE_ASCENT)
    name = "Airborne Ascent";
  else if (_loopState == FLIGHT_STATE_AIRBORNE_DESCENT)
    name = "Airborne Descent";
  else if (_loopState == FLIGHT_STATE_GROUND)
    name = "Ground";
  else if (_loopState == FLIGHT_STATE_LANDED)
    name = "Landed";
  return name;
}

stateMachineSync _stateMachineSync;
