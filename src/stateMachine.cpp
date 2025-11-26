#include <Arduino.h>
#if defined(ESP32)
#endif

#include <debug.h>
#include "settings.h"
#include "simulation.h"
#include "stateMachine.h"

stateMachine::stateMachine() {
  _stateMachineSettings.altitudeLiftoff = ALTITUDE_LIFTOFF;
  _stateMachineSettings.sampleRates.airborneAscent = SAMPLE_RATE_AIRBORNE_ASCENT;
  _stateMachineSettings.sampleRates.airborneDescent = SAMPLE_RATE_AIRBORNE_DESCENT;
  _stateMachineSettings.sampleRates.ground = SAMPLE_RATE_GROUND;
  _stateMachineSettings.sampleRates.aborted = SAMPLE_MEASURES_ABORTED;
  _stateMachineSettings.sampleRates.landed = SAMPLE_RATE_LANDED;
}

int stateMachine::altitudeLiftoff() {
  return _altitudeLiftoff;
}

void stateMachine::loop(unsigned long timestamp, unsigned long delta) {
  // Simple state machine for the flight...

  // Serial.println(F("state..."));
  // Serial.println(_loopState);
  // Ground state
  if (_loopState == FLIGHT_STATE_ABORTED) {
    // Serial.println(F("state...ABORTED"));
    // Run the aborted state algorithms
    loopStateABORTED(timestamp, delta);
    return;
  }
  if (_loopState == FLIGHT_STATE_AIRBORNE_ASCENT) {
    // Serial.println(F("state...AIRBORNE_ASCENT"));
    // Run the airborne ascent state algorithms
    loopStateAIRBORNE_ASCENT(timestamp, delta);
    return;
  }
  if (_loopState == FLIGHT_STATE_AIRBORNE_DESCENT) {
    // Serial.println(F("state...AIRBORNE_DESCENT"));
    // Run the airborne descent state algorithms
    loopStateAIRBORNE_DESCENT(timestamp, delta);
    return;
  }
  if (_loopState == FLIGHT_STATE_GROUND) {
    // Serial.println(F("state...GROUND"));
    // Run the ground state algorithms
    loopStateGROUND(timestamp, delta);
    return;
  }
  if (_loopState == FLIGHT_STATE_LANDED) {
    // Serial.println(F("state...LANDED"));
    // Run the landed state algorithms
    loopStateLANDED(timestamp, delta);
    return;
  }
}

void stateMachine::loopStateABORTED(unsigned long timestamp, unsigned long deltaElapsed) {
  if (_loopStateFunc != nullptr)
    _loopStateFunc(_loopState, timestamp, deltaElapsed);

  // Determine the aborted loop time delay based on sampling rate.
  unsigned long delta = _throttleAborted.determine('a', deltaElapsed, _stateMachineSettings.sampleRates.aborted);
  if (delta == 0)
    return;
  
  if (_loopStateThrottledFunc != nullptr)
    _loopStateThrottledFunc(_loopState, timestamp, deltaElapsed);

  // Functionality that happen on the tick goes here:

  // TODO: When do we want to move back from aborted to ground state?
  // // Transition to the GROUND stage.
  // if (_countdownAborted > _stateMachineSettings.sampleMeasures.aborted) {
  //   loopStateABORTEDToGROUND(timestamp, deltaElapsed);
  //   return;
  // }

  // _countdownAborted++;
  // debug(F("countdownAborted"), _countdownAborted); // TODO
}

void stateMachine::loopStateABORTEDToGROUND(unsigned long timestamp, unsigned long deltaElapsed) {
  debug();
  debug();
  debug();
  debug();
  debug(F("...ABORTED to GROUND!!!!"));
  debug(F("...ABORTED to GROUND!!!!"));
  debug(F("...ABORTED to GROUND!!!!"));
  debug();
  debug();
  debug();
  debug();

  if (_loopStateChangedFunc != nullptr)
    _loopStateChangedFunc(FLIGHT_STATE_GROUND, _loopState, timestamp, deltaElapsed);

  _loopState = FLIGHT_STATE_GROUND;
}

void stateMachine::loopStateAIRBORNEToABORTED(unsigned long timestamp, unsigned long deltaElapsed, const __FlashStringHelper *message1, const __FlashStringHelper *message2) {
  // Something went wrong and aborting...

  _flightLog->aborted = true;
  _flightLog->airborne = false;
  _flightLog->recording = false;
  _flightLog->touchdown = false;

#if defined(DEV) && defined(DEV_SIM)
  if (_simulation.isRunning()) 
    _simulation.stop();
#endif

  debug();
  debug();
  debug();
  debug();
  debug(F("...ABORTED!!!!"));
  debug(F("...ABORTED!!!!"));
  Serial.println(reinterpret_cast<const char *>(message1));
  Serial.println(reinterpret_cast<const char *>(message2));
  debug(F("...ABORTED!!!!"));
  debug();
  debug();
  debug();
  debug();

  _countdownAborted = 0;

  if (_loopStateChangedFunc != nullptr)
    _loopStateChangedFunc(FLIGHT_STATE_ABORTED, _loopState, timestamp, deltaElapsed);
  
  _loopState = FLIGHT_STATE_ABORTED;
}

void stateMachine::loopStateAIRBORNE_ASCENT(unsigned long timestamp, unsigned long deltaElapsed) {
  if (_loopStateFunc != nullptr)
    _loopStateFunc(_loopState, timestamp, deltaElapsed);

  unsigned long delta = _throttleAirborneAscent.determine('a', deltaElapsed, _sampleRateAirborneAscent);
  if (delta == 0)
    return;
  
  if (_loopStateThrottledFunc != nullptr)
    _loopStateThrottledFunc(_loopState, timestamp, deltaElapsed);

  _accumulator++;

//   // Functionality that happen on the tick goes here:

  // Determine different in time between the last step...
  unsigned long currentTimestamp = timestamp - _flightLog->instance()->getData().timestampLaunch;
  unsigned long diffTime = currentTimestamp - _flightLog->instance()->getData().timestampPrevious;
#ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
  debug(F("loopStateAIRBORNE_ASCENT...timestamp"), timestamp);
  debug(F("loopStateAIRBORNE_ASCENT...currentTimestamp"), currentTimestamp);
  debug(F("loopStateAIRBORNE_ASCENT...diffTime"), diffTime);
// }
#endif
  
  atmosphereValues atmosphereValuesO = readSensorAtmosphere();
  float altitude = atmosphereValuesO.altitude;
  _flightLog->instance()->setAltitudeCurrent(altitude);
  float altitudeDelta = altitude - _flightLog->instance()->getData().altitudeLast;

#ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
#if defined(DEV) && defined(DEV_SIM)
  debug(F("loopStateAIRBORNE_ASCENT..._simulation.isRunning"), _simulation.isRunning());
#endif
  debug(F("loopStateAIRBORNE_ASCENT...altitude"), altitude);
  debug(F("loopStateAIRBORNE_ASCENT...currentTimestamp"), currentTimestamp);
  debug(F("loopStateAIRBORNE_ASCENT...diffTime"), diffTime);
// }
#endif

  _updateTrace(currentTimestamp, diffTime, atmosphereValuesO, altitudeDelta);

  // Detect apogee by taking X number of measures as long as the current is less
  // than the last recorded altitude.
#ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
  debug();
  debug();
  debug();
  debug(F("loopStateAIRBORNE_ASCENT...altitudeLast"), _flightLog->instance()->getData().altitudeLast);
  debug(F("loopStateAIRBORNE_ASCENT...altitudeDelta"), altitudeDelta);
  debug();
  debug();
  debug();
  debug(F("loopStateAIRBORNE_ASCENT...sampleMeasures.apogee"), _stateMachineSettings.sampleMeasures.apogee);
  debug(F("loopStateAIRBORNE_ASCENT...sampleMeasures.apogee"), _stateMachineSettings.sampleMeasures.apogee);
  debug(F("loopStateAIRBORNE_ASCENT...sampleMeasures.apogee"), _stateMachineSettings.sampleMeasures.apogee);
  debug(F("loopStateAIRBORNE_ASCENT...sampleMeasures.apogee"), _stateMachineSettings.sampleMeasures.apogee);
  debug(F("loopStateAIRBORNE_ASCENT...sampleMeasures.apogee"), _stateMachineSettings.sampleMeasures.apogee);
  debug(F("loopStateAIRBORNE_ASCENT...sampleMeasures.apogee"), _stateMachineSettings.sampleMeasures.apogee);
  debug(F("loopStateAIRBORNE_ASCENT...sampleMeasures.apogee"), _stateMachineSettings.sampleMeasures.apogee);
  debug(F("loopStateAIRBORNE_ASCENT...sampleMeasures.apogee"), _stateMachineSettings.sampleMeasures.apogee);
  debug(F("loopStateAIRBORNE_ASCENT...sampleMeasures.apogee"), _stateMachineSettings.sampleMeasures.apogee);
  debug();
  debug();
  debug();
// }
#endif
  if (altitudeDelta < 0) {
#ifdef DEBUG_ALTIMETER
    debug();
    debug();
    debug();
    debug(F("loopStateAIRBORNE_ASCENT...measures1"), _flightLog->measures);
    debug(F("loopStateAIRBORNE_ASCENT...sampleMeasures.apogee"), _stateMachineSettings.sampleMeasures.apogee);
    debug(F("loopStateAIRBORNE_ASCENT...FirstMeasure?"), (_flightLog->measures == _stateMachineSettings.sampleMeasures.apogee));
    debug();
    debug();
    debug();
#endif
    if (_flightLog->measures == _stateMachineSettings.sampleMeasures.apogee) {
      debug();
      debug();
      debug();
      debug(F("loopStateAIRBORNE_ASCENT...altitudeLast"), _flightLog->instance()->getData().altitudeLast);
      debug();
      debug();
      debug();
      _flightLog->instance()->setAltitudeApogeeFirstMeasure(_flightLog->instance()->getData().altitudeLast);
      debug();
      debug();
      debug();
      debug(F("loopStateAIRBORNE_ASCENT...altitudeApogeeFirstMeasure"), _flightLog->instance()->getData().altitudeApogeeFirstMeasure);
      debug();
      debug();
      debug();
      _flightLog->instance()->setTimestampApogeeFirstMeasure(currentTimestamp);
    }
#ifdef DEBUG_ALTIMETER
    debug();
    debug();
    debug();
    debug(F("loopStateAIRBORNE_ASCENT...measures2"), _flightLog->measures);
    debug();
    debug();
    debug();
#endif
    _flightLog->measures = _flightLog->measures - 1;
    if (_flightLog->measures == 0) {
      // Detected apogee.
      loopStateAIRBORNE_ASCENTToAIRBORNE_DESCENT(timestamp, deltaElapsed);
      return;
    }
  } 
  else {
    if (_flightLog->measures < _stateMachineSettings.sampleMeasures.apogee) {
#ifdef DEBUG_ALTIMETER
      debug();
      debug();
      debug();
      debug(F("loopStateAIRBORNE_ASCENT...measures"), F("reset"));
      debug();
      debug();
      debug();
#endif
      // If the current is greater than the last, then reset as it was potentially
      // a false positive.
      _flightLog->instance()->setAltitudeApogeeFirstMeasure(0);
      _flightLog->instance()->setTimestampApogeeFirstMeasure(0);
      _flightLog->instance()->setAltitudeLast(_flightLog->instance()->getData().altitudeCurrent);
      _flightLog->measures = _stateMachineSettings.sampleMeasures.apogee;
    }
  }

  // Check for timeouts...
  bool timestampApogeeCheck = currentTimestamp > _stateMachineSettings.timeOutTimeToApogee;
#ifdef DEBUG_ALTIMETER
  debug(F("loopStateAIRBORNE_ASCENT...timeOutTimeToApogee"), _stateMachineSettings.timeOutTimeToApogee);
  debug(F("loopStateAIRBORNE_ASCENT...currentTimestamp"), currentTimestamp);
  debug(F("loopStateAIRBORNE_ASCENT...timestampApogeeCheck"), timestampApogeeCheck);
#endif
  if (timestampApogeeCheck) {
    // Something went wrong and apogee was never found, so abort!
    loopStateAIRBORNEToABORTED(timestamp, deltaElapsed, F("Time to apogee threshold exceeded!"), F("AIRBORNE_ASCENT aborted, returning to GROUND!!!!"));
    return;
  }

  bool timeoutRecordingCheck = currentTimestamp > _stateMachineSettings.timeoutRecording;
#ifdef DEBUG_ALTIMETER
  debug(F("loopStateAIRBORNE_ASCENT...timestampLaunch"), _flightLog->instance()->getData().timestampLaunch);
  debug(F("loopStateAIRBORNE_ASCENT...timeoutRecording"), _stateMachineSettings.timeoutRecording);
  debug(F("loopStateAIRBORNE_ASCENT...currentTimestamp"), currentTimestamp);
  debug(F("loopStateAIRBORNE_ASCENT...timeoutRecordingCheck"), timeoutRecordingCheck);
#endif
  if (timeoutRecordingCheck) {
    // Something went wrong., so abort!
    loopStateAIRBORNEToABORTED(timestamp, deltaElapsed, F("Time to apogee threshold exceeded!"), F("AIRBORNE_ASCENT aborted, returning to GROUND!!!!"));
    return;
  }
}

void stateMachine::loopStateAIRBORNE_ASCENTToAIRBORNE_DESCENT(unsigned long timestamp, unsigned long deltaElapsed) {
  _flightLog->instance()->setAltitudeApogee(_flightLog->instance()->getData().altitudeApogeeFirstMeasure);
  _flightLog->instance()->setTimestampApogee(_flightLog->instance()->getData().timestampApogeeFirstMeasure);

  debug();
  debug();
  debug();
  debug();
  debug(F("...DESCENT!!!!"));
  debug(F("...DESCENT!!!!"));
  debug();
  debug();
  debug();
  debug(F("loopStateAIRBORNE_ASCENTToAIRBORNE_DESCENT...altitudeApogeeFirstMeasure"), _flightLog->instance()->getData().altitudeApogeeFirstMeasure);
  debug(F("loopStateAIRBORNE_ASCENTToAIRBORNE_DESCENT...altitudeApogeeFirstMeasure"), _flightLog->instance()->getData().altitudeApogee);
  debug();
  debug();
  debug();
  debug(F("...DESCENT!!!!"));
  debug(F("...DESCENT!!!!"));
  debug();
  debug();
  debug();
  debug();

  if (_loopStateChangedFunc != nullptr)
    _loopStateChangedFunc(FLIGHT_STATE_AIRBORNE_DESCENT, _loopState, timestamp, deltaElapsed);

  _loopState = FLIGHT_STATE_AIRBORNE_DESCENT;
}

void stateMachine::loopStateAIRBORNE_DESCENT(unsigned long timestamp, unsigned long deltaElapsed) {
  if (_loopStateFunc != nullptr)
    _loopStateFunc(_loopState, timestamp, deltaElapsed);

  int delta = _throttleAirborneDescent.determine('d', deltaElapsed, _sampleRateAirborneDescent);
  if (delta == 0)
    return;
  
  if (_loopStateThrottledFunc != nullptr)
    _loopStateThrottledFunc(_loopState, timestamp, deltaElapsed);

  _accumulator++;

//   // Functionality that happen on the tick goes here:

  // Determine different in time between the last step...
  long currentTimestamp = timestamp - _flightLog->instance()->getData().timestampLaunch;
  long diffTime = currentTimestamp - _flightLog->instance()->getData().timestampPrevious;
#ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
  debug(F("loopStateAIRBORNE_DESCENT...timestamp"), timestamp);
  debug(F("loopStateAIRBORNE_DESCENT...currentTimestamp"), currentTimestamp);
  debug(F("loopStateAIRBORNE_DESCENT...diffTime"), diffTime);
// }
#endif
  
  atmosphereValues atmosphereValuesO = readSensorAtmosphere();
  float altitude = atmosphereValuesO.altitude;
  _flightLog->instance()->setAltitudeCurrent(altitude);
  float altitudeDelta = altitude - _flightLog->instance()->getData().altitudeLast;

#ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
#if defined(DEV) && defined(DEV_SIM)
  debug(F("loopStateAIRBORNE_DESCENT..._simulation.isRunning"), _simulation.isRunning());
#endif
  debug(F("loopStateAIRBORNE_DESCENT...altitude"), altitude);
  debug(F("loopStateAIRBORNE_DESCENT...altitudeDelta"), altitudeDelta);
  debug(F("loopStateAIRBORNE_DESCENT...currentTimestamp"), currentTimestamp);
  debug(F("loopStateAIRBORNE_DESCENT...diffTime"), diffTime);
// }
#endif

  _updateTrace(currentTimestamp, diffTime, atmosphereValuesO, altitudeDelta);

  bool timeoutRecordingCheck = ((timestamp - _flightLog->instance()->getData().timestampLaunch) > _stateMachineSettings.timeoutRecording);
#ifdef DEBUG_ALTIMETER
  debug(F("loopStateAIRBORNE_DESCENT...timestamp"), timestamp);
  debug(F("loopStateAIRBORNE_DESCENT...timestampLaunch"), _flightLog->instance()->getData().timestampLaunch);
  debug(F("loopStateAIRBORNE_DESCENT...timeoutRecordingCheck"), timeoutRecordingCheck);
#endif

  if (timeoutRecordingCheck) {
    // Something went wrong and the recordingt timeout was hit, so abort!
    loopStateAIRBORNEToABORTED(timestamp, deltaElapsed, F("Exceeded recording timeout!"), F("AIRBORNE_DESCENT aborted, returning to GROUND!!!!"));
    return;
  }

  float altitudeCurrent = _flightLog->instance()->getData().altitudeCurrent;
  float altitudeLandingTarget = _flightLog->altitudeInitial + _altitudeGround;
  bool altitudeCheck = altitudeCurrent < altitudeLandingTarget;
#ifdef DEBUG_ALTIMETER
  debug(F("loopStateAIRBORNE_DESCENT...altitudeCurrent"), altitudeCurrent);
  debug(F("loopStateAIRBORNE_DESCENT...altitudeGround"), _altitudeGround);
  debug(F("loopStateAIRBORNE_DESCENT...altitudeLandingTarget"), altitudeLandingTarget);
  debug(F("loopStateAIRBORNE_DESCENT...altitudeCheck"), altitudeCheck);
#endif
  if (altitudeCheck) {
    _flightLog->instance()->setAltitudeTouchdown(_flightLog->instance()->getData().altitudeLast);
    _flightLog->instance()->setTimestampTouchdown(_flightLog->instance()->getData().timestampPrevious);
    // Passed the descent touchdown altitude check, so the flight log is ended and return to GROUND
    loopStateAIRBORNE_DESCENTToLANDED(timestamp, deltaElapsed);
    return;
  }
}

void stateMachine::loopStateAIRBORNE_DESCENTToLANDED(unsigned long timestamp, unsigned long deltaElapsed) {
  // Complete the flight
  Serial.println(F("Flight has ended!!!"));

#if defined(DEV) && defined(DEV_SIM)
  if (_simulation.isRunning()) 
    _simulation.stop();
#endif

  _flightLog->aborted = false;
  _flightLog->airborne = false;
  _flightLog->recording = false;
  _flightLog->touchdown = true;

  debug();
  debug();
  debug();
  debug();
  debug(F("...LANDED!!!!"));
  debug(F("...LANDED!!!!"));
  debug(F("...LANDED!!!!"));
  debug();
  debug();
  debug();
  debug();

// #ifdef DEBUG
//   Serial.println(F("\nWriting output..."));
// #endif
//   _flightLog->instance()->writeFlightCurrent();
// #ifdef DEBUG
//   Serial.println(F("...writing output.\n"));
// #endif

  if (_loopStateChangedFunc != nullptr)
    _loopStateChangedFunc(FLIGHT_STATE_LANDED, _loopState, timestamp, deltaElapsed);

  _loopState = FLIGHT_STATE_LANDED;
}

void stateMachine::loopStateLANDED(unsigned long timestamp, unsigned long deltaElapsed) {
  if (_loopStateFunc != nullptr)
    _loopStateFunc(_loopState, timestamp, deltaElapsed);

  // Determine the ground loop time delay based on sampling rate.
  unsigned long delta = _throttleLanded.determine('l', deltaElapsed, _stateMachineSettings.sampleRates.landed);
  if (delta == 0)
    return;
  
  if (_loopStateThrottledFunc != nullptr)
    _loopStateThrottledFunc(_loopState, timestamp, deltaElapsed);

  // Functionality that happen on the tick goes here:

  // debug(F("loopStateLANDED...timestamp"), timestamp);

  // TODO: When do we want to move back from landed to ground state?
// #ifdef DEBUG_ALTIMETER
//     debug(F("countdownLanded"), _countdownLanded);
//     debug(F("sampleMeasuresLanded"), _stateMachineSettings.sampleMeasures.landed);
// #endif
//   // Transition to the AIRBORNE_ASCENT ascent stage.
//   if (_countdownLanded >= _stateMachineSettings.sampleMeasures.landed) {
//     loopStateLANDEDToGROUND(timestamp, deltaElapsed);
//     return;
//   }

//   _countdownLanded++;
}

void stateMachine::loopStateLANDEDToGROUND(unsigned long timestamp, unsigned long deltaElapsed) {
  debug();
  debug();
  debug();
  debug();
  debug(F("...GROUNDED!!!!"));
  debug(F("...GROUNDED!!!!"));
  debug(F("...GROUNDED!!!!"));
  debug();
  debug();
  debug();
  debug();

  if (_loopStateChangedFunc != nullptr)
    _loopStateChangedFunc(FLIGHT_STATE_GROUND, _loopState, timestamp, deltaElapsed);

  _loopState = FLIGHT_STATE_GROUND;
  _countdownLanded = 0;

//   Serial.println(F("Serial Output"));
//   _flightLog->instance()->outputSerial();
//   Serial.print(F("\nExpanded Serial Output\n\n"));
//   _flightLog->instance()->outputSerialExpanded();
//   Serial.print(F("\n"));
}

void stateMachine::loopStateGROUND(unsigned long timestamp, unsigned long deltaElapsed) {
  // Serial.printf(F("...loopStateGROUND... %d\n"), deltaElapsed);

  if (_loopStateFunc != nullptr)
    _loopStateFunc(_loopState, timestamp, deltaElapsed);

  // Determine the ground loop time delay based on sampling rate.
  unsigned long delta = _throttleGround.determine('g', deltaElapsed, _sampleRateGround);
  if (delta == 0)
    return;

  _accumulator++;

#ifdef DEBUG_ALTIMETER
  debug(F("loopStateGROUND..._sampleRateGround"), _sampleRateGround);
  debug(F("loopStateGROUND...delta"), delta);
#endif
  
  if (_loopStateThrottledFunc != nullptr)
    _loopStateThrottledFunc(_loopState, timestamp, deltaElapsed);

  // Get the current altitude and determine the delta from initial.
  float altitude = readSensorAltitude();
  float altitudeLaunchApogeeTarget = _flightLog->altitudeInitial + _altitudeLiftoff;
#ifdef DEBUG_ALTIMETER
//   debug(F("stateGROUND...processing, delta"), delta);
//   debug(F("stateGROUND...processing, deltaElapsed"), deltaElapsed);
// if (_accumulator % 100000 == 0) {
#if defined(DEV) && defined(DEV_SIM)
  debug(F("loopStateGROUND..._simulation.isRunning"), _simulation.isRunning());
#endif
  debug(F("loopStateGROUND...altitude"), altitude);
  debug(F("loopStateGROUND...altitudeInitial"), _flightLog->altitudeInitial);
  debug(F("loopStateGROUND...altitudeLiftoffCutoff"), _altitudeLiftoff);
  debug(F("loopStateGROUND...altitudeLaunchApogeeTarget"), altitudeLaunchApogeeTarget);
  debug(F("loopStateGROUND...altitudeLiftoff?"), (altitude > altitudeLaunchApogeeTarget));
// }
#endif

  // Check for whether we've left the ground
  if (altitude > altitudeLaunchApogeeTarget) {
#ifdef DEBUG_ALTIMETER
    debug();
    debug();
    debug();
    debug();
    debug();
    debug();
    debug(F("loopStateGROUND...processing, launch detected"), 0);
    debug(F("loopStateGROUND...altitude"), altitude);
    debug(F("loopStateGROUND...altitudeLaunchApogeeTarget"), altitudeLaunchApogeeTarget);
    debug(F("loopStateGROUND...altitudeInitial"), _flightLog->altitudeInitial);
    debug();
    debug();
    debug();
    debug();
    debug();
#endif
    // Transition to the AIRBORNE_ASCENT ascent stage.
    loopStateGROUNDToAIRBORNE_ASCENT(timestamp, deltaElapsed);
    return;
  }
}

void stateMachine::loopStateGROUNDToAIRBORNE_ASCENT(unsigned long timestamp, unsigned long deltaElapsed) {
  debug();
  debug();
  debug();
  debug();
  debug(F("...AIRBORNE!!!!"));
  debug(F("...AIRBORNE!!!!"));
  debug(F("...AIRBORNE!!!!"));
  debug();
  debug();
  debug();
  debug();

  // Re-initialize the flight...
  _flightLog->init(timestamp);
  _updateTrace(timestamp, 0);

  if (_loopStateChangedFunc != nullptr)
    _loopStateChangedFunc(FLIGHT_STATE_AIRBORNE_ASCENT, _loopState, timestamp, deltaElapsed);

  _loopState = FLIGHT_STATE_AIRBORNE_ASCENT;
}

void stateMachine::preferencesOutput() {
#if defined(ESP32)
  // Preferences preferences;
  // preferences.begin(PREFERENCE_KEY, false);
  // int altitudeLiftoff = preferences.getInt(PREFERENCE_KEY_LAUNCH_DETECT, _stateMachineSettings.altitudeLiftoff);
  // int sampleRateAirborneAscent = preferences.getInt(PREFERENCE_KEY_ALTITUDE_AIRBORNE_ASCENT, _stateMachineSettings.sampleRates.aAirborneAscent);
  // int sampleRateAirborneDescent = preferences.getInt(PREFERENCE_KEY_ALTITUDE_AIRBORNE_DESCENT, _stateMachineSettings.sampleRates.airborneDescent);
  // int sampleRateGround = preferences.getInt(PREFERENCE_KEY_ALTITUDE_GROUND, _stateMachineSettings.sampleRates.ground);
  // preferences.end();
  
  // char intFormat[3] = "%i";
  // char preferencesOutput[80] = "";
  // char temp[9] = "";
  // strcat(preferencesOutput, "$stateMachineSettings.altitudeLiftoff,");
  // sprintf(temp, intFormat, altitudeLiftoff);
  // strcat(preferencesOutput, temp);
  // strcat(preferencesOutput, ";\n");

  // preferencesOutput[0] = '\0';
  // strcat(preferencesOutput, "$ALTITUDE_AIRBORNE_ASCENT,");
  // sprintf(temp, intFormat, sampleRateAirborneAscent);
  // strcat(preferencesOutput, temp);
  // strcat(preferencesOutput, ";\n");

  // preferencesOutput[0] = '\0';
  // strcat(preferencesOutput, "$ALTITUDE_AIRBORNE_DESCENT,");
  // sprintf(temp, "%,", sampleRateAirborneDescent);
  // strcat(preferencesOutput, temp);
  // strcat(preferencesOutput, ";\n");
  
  // preferencesOutput[0] = '\0';
  // strcat(preferencesOutput, "$ALTITUDE_GROUND,");
  // sprintf(temp, intFormat, sampleRateGround);
  // strcat(preferencesOutput, temp);
  // strcat(preferencesOutput, ";\n");

  // Serial.print(preferencesOutput);
#endif
}

accelerometerValues stateMachine::readSensorAccelerometer() {
#if defined(DEV) && defined(DEV_SIM)
// #ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
//   Serial.println(F("readSensorAccelerometer...dev...checking if simulation is running"));
// }
// #endif
  if (_simulation.isRunning()) {
    accelerometerValues values;
    values.x = 0;
    values.y = 0;
    values.z = 0;
// #ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
//     Serial.println(F("readSensorAccelerometer...dev...reading acceleration from sim..."));
// }
// #endif
    return values;
  }
#endif

// #ifdef DEBUG_ALTIMETER
//   Serial.println(F("readSensorAccelerometer...reading acceleration from sensors...")); 
// #endif
  return sensorData.acceleration;
}

float stateMachine::readSensorAltitude() {
#if defined(DEV) && defined(DEV_SIM)
#ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
  Serial.println(F("readSensorAltitude...dev...checking if simulation is running"));
// }
#endif
  if (_simulation.isRunning()) {
    float altitude = _simulation.valueAltitude();
#ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
    Serial.print(F("readSensorAltitude...dev...reading altitude from sim..."));
    Serial.println(altitude);
// }
#endif
    return altitude;
  }
#endif

// #ifdef DEBUG_ALTIMETER
//   Serial.println(F("readSensorAltitude...reading altitude from sensors...")); 
// #endif
  return sensorData.atmosphere.altitude;
}

atmosphereValues stateMachine::readSensorAtmosphere() {
#if defined(DEV) && defined(DEV_SIM)
#ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
//   Serial.println(F("readSensorAtmosphere...dev...checking if simulation is running"));
// }
#endif
  if (_simulation.isRunning()) {
    atmosphereValues values;
    values.altitude = _simulation.valueAltitude();
    values.humidity = 0;
    values.pressure = 0;
    values.temperature = 0;
#ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
    // Serial.println(F("readSensorAtmosphere...dev...reading atmosphere from sim..."));
// }
#endif
    return values;
  }
#endif

// #ifdef DEBUG_ALTIMETER
//   Serial.println(F("readSensorAtmosphere...reading atmosphere from sensors...")); 
// #endif
  return sensorData.atmosphere;
}

gyroscopeValues stateMachine::readSensorGyroscope() {
#if defined(DEV) && defined(DEV_SIM)
#ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
//   Serial.println(F("readSensorGyroscope...dev...checking if simulation is running"));
// }
#endif
  if (_simulation.isRunning()) {
    gyroscopeValues values;
    values.x = 0;
    values.y = 0;
    values.z = 0;
#ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
//     Serial.println(F("readSensorGyroscope...dev...reading gyroscope from sim..."));
// }
#endif
    return values;
  }
#endif

// #ifdef DEBUG_ALTIMETER
//   Serial.println(F("readSensorGyroscope...reading gyroscope from sensors...")); 
// #endif
  return sensorData.gyroscope;
}

magnetometerValues stateMachine::readSensorMagnetometer() {
#if defined(DEV) && defined(DEV_SIM)
#ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
//   Serial.println(F("readSensorMagnetometer...dev...checking if simulation is running"));
// }
#endif
  if (_simulation.isRunning()) {
    magnetometerValues values;
    values.x = 0;
    values.y = 0;
    values.z = 0;
#ifdef DEBUG_ALTIMETER
// if (_accumulator % 100000 == 0) {
//     Serial.println(F("readSensorMagnetometer...dev...reading magnetometer from sim..."));
// }
#endif
    return values;
  }
#endif

// #ifdef DEBUG_ALTIMETER
//   Serial.println(F("readSensorMagnetometer...reading magnetometer from sensors...")); 
// #endif
  return sensorData.magnetometer;
}

void stateMachine::reset() {
  Serial.println(F("Reset state machine..."));

  _altitudeLiftoff = _stateMachineSettings.altitudeLiftoff;
  _sampleRateAirborneAscent = _stateMachineSettings.sampleRates.airborneAscent;
  _sampleRateAirborneDescent = _stateMachineSettings.sampleRates.airborneDescent;
  _sampleRateGround = _stateMachineSettings.sampleRates.ground;
  
  save(_altitudeLiftoff, _sampleRateAirborneAscent, _sampleRateAirborneDescent, _sampleRateGround);

  Serial.println(F("...state machine reset successful."));
}

void stateMachine::returnToGround() {
  if (_loopState == FLIGHT_STATE_ABORTED)
    loopStateABORTEDToGROUND(0, 0);
  else if (_loopState == FLIGHT_STATE_LANDED)
    loopStateLANDEDToGROUND(0, 0);
}

int stateMachine::sampleRateAirborneAscent() {
  return _sampleRateAirborneAscent;
}
int stateMachine::sampleRateAirborneDescent() {
  return _sampleRateAirborneDescent;
}
int stateMachine::sampleRateGround() {
  return _sampleRateGround;
}

void stateMachine::save(int altitudeLiftoff, int sampleRateAirborneAscent, int sampleRateAirborneDecent, int sampleRateGround) {
  Serial.println(F("\tSave state machine..."));
  
#ifdef DEBUG
  Serial.println(F("\t\t...state machine... save requests"));
  Serial.print(F("\t\taltitudeLiftoff="));
  Serial.println(altitudeLiftoff);
  Serial.print(F("\t\tsampleRateAirborneAscent="));
  Serial.println(sampleRateAirborneAscent);
  Serial.print(F("\t\tsampleRateAirborneDecent="));
  Serial.println(sampleRateAirborneDecent);
  Serial.print(F("\t\tsampleRateGround="));
  Serial.println(sampleRateGround);

  Serial.println(F("\t\t...state machine... save current"));
  _displaySettings();
#endif

  debug();
  debug();
  debug();
  debug(F("save"), 0);
  debug(F("setup..._flightLog->measures"), _flightLog->measures);
  debug(F("setup..._stateMachineSettings.sampleMeasures.apogee?"), _stateMachineSettings.sampleMeasures.apogee);
  debug();
  debug();
  debug();

  _altitudeLiftoff = _checkValues(altitudeLiftoffValues, altitudeLiftoff, _stateMachineSettings.altitudeLiftoff, sizeof(altitudeLiftoffValues) / sizeof(altitudeLiftoffValues[0]));
  _sampleRateAirborneAscent = _checkValues(sampleRateAirborneAscentValues, sampleRateAirborneAscent, _stateMachineSettings.sampleRates.airborneAscent, sizeof(sampleRateAirborneAscentValues) / sizeof(sampleRateAirborneAscentValues[0]));
  _sampleRateAirborneDescent = _checkValues(sampleRateAirborneDecentValues, sampleRateAirborneDecent, _stateMachineSettings.sampleRates.airborneDescent, sizeof(sampleRateAirborneDecentValues) / sizeof(sampleRateAirborneDecentValues[0]));
  _sampleRateGround = _checkValues(sampleRateGroundValues, sampleRateGround, _stateMachineSettings.sampleRates.ground, sizeof(sampleRateGroundValues) / sizeof(sampleRateGroundValues[0]));

  debug();
  debug();
  debug();
  debug(F("save"), 1);
  debug(F("setup..._flightLog->measures"), _flightLog->measures);
  debug(F("setup..._stateMachineSettings.sampleMeasures.apogee?"), _stateMachineSettings.sampleMeasures.apogee);
  debug();
  debug();
  debug();
  
#ifdef DEBUG
  Serial.println(F("\t\t...state machine... save checked"));
  Serial.print(F("\t\t_altitudeLiftoff="));
  Serial.println(_altitudeLiftoff);
  Serial.print(F("\t\t_sampleRateAirborneAscent="));
  Serial.println(_sampleRateAirborneAscent);
  Serial.print(F("\t\t_sampleRateAirborneDescent="));
  Serial.println(_sampleRateAirborneDescent);
  Serial.print(F("\t\t_sampleRateGround="));
  Serial.println(_sampleRateGround);
  Serial.print(F("\t\t_sampleRateGround="));
  Serial.println(_sampleRateGround);
#endif

  debug();
  debug();
  debug();
  debug(F("save"), 2);
  debug(F("setup..._flightLog->measures"), _flightLog->measures);
  debug(F("setup..._stateMachineSettings.sampleMeasures.apogee?"), _stateMachineSettings.sampleMeasures.apogee);
  debug();
  debug();
  debug();

  if (_settingsSaveFunc != nullptr)
    _settingsSaveFunc(_stateMachineSettings);
#if defined(ESP32)
  // Preferences preferences;
  // preferences.begin(PREFERENCE_KEY, false);
  // preferences.putInt(PREFERENCE_KEY_LAUNCH_DETECT, _altitudeLiftoff);
  // preferences.putInt(PREFERENCE_KEY_ALTITUDE_AIRBORNE_ASCENT, _sampleRateAirborneAscent);
  // preferences.putInt(PREFERENCE_KEY_ALTITUDE_AIRBORNE_DESCENT, _sampleRateAirborneDescent);
  // preferences.putInt(PREFERENCE_KEY_ALTITUDE_GROUND, _sampleRateGround);
  // preferences.end();
#endif

  debug();
  debug();
  debug();
  debug(F("save"), 3);
  debug(F("setup..._flightLog->measures"), _flightLog->measures);
  debug(F("setup..._stateMachineSettings.sampleMeasures.apogee?"), _stateMachineSettings.sampleMeasures.apogee);
  debug();
  debug();
  debug();

  _altitudeGround = _altitudeLiftoff / 2;

#ifdef DEBUG
  Serial.println(F("\t\t...state machine... saved state"));
  _displaySettings();
  Serial.println();
#endif

  debug();
  debug();
  debug();
  debug(F("save"), 4);
  debug(F("setup..._flightLog->measures"), _flightLog->measures);
  debug(F("setup..._stateMachineSettings.sampleMeasures.apogee?"), _stateMachineSettings.sampleMeasures.apogee);
  debug();
  debug();
  debug();

  Serial.println(F("\t...state machine save successful."));
}

byte stateMachine::setup(flightLog* flightLog, sensors* sensors, StateMachineStateFunctionPtr stateFunc, StateMachineStateThottledFunctionPtr stateThrottledFunc, StateMachineStateChangedFunctionPtr stateChangedFunc, StateMachinePreferenceLoadFunctionPtr stateLoadFunc, StateMachinePreferenceSaveFunctionPtr stateSaveFunc) {
  Serial.println(F("Setup state machine..."));

  _flightLog = flightLog;
  if (_flightLog == nullptr)
    return 2;
    
  _sensors = sensors;
  _loopStateFunc = stateFunc;
  _loopStateChangedFunc = stateChangedFunc;
  _loopStateThrottledFunc = stateThrottledFunc;
  _settingsLoadFunc = stateLoadFunc;
  _settingsSaveFunc = stateSaveFunc;

  if (_settingsLoadFunc != nullptr)
    _settingsLoadFunc(_stateMachineSettings);
#if defined(ESP32)
  // Preferences preferences;
  // preferences.begin(PREFERENCE_KEY, false);
  // _altitudeLiftoff = preferences.getInt(PREFERENCE_KEY_LAUNCH_DETECT, stateMachineSettings.altitudeLiftoff);
  // if (_altitudeLiftoff <= 0) {
  //   _altitudeLiftoff = stateMachineSettings.altitudeLiftoff;
  //   preferences.putInt(PREFERENCE_KEY_LAUNCH_DETECT, _altitudeLiftoff);
  // }
  // _sampleRateAirborneAscent = preferences.getInt(PREFERENCE_KEY_ALTITUDE_AIRBORNE_ASCENT, stateMachineSettings.sampleRateAirborneAscent);
  // if (_sampleRateAirborneAscent <= 0) {
  //   _sampleRateAirborneAscent = stateMachineSettings.sampleRateAirborneAscent;
  //   preferences.putInt(PREFERENCE_KEY_ALTITUDE_AIRBORNE_ASCENT, _sampleRateAirborneAscent);
  // }
  // _sampleRateAirborneDescent = preferences.getInt(PREFERENCE_KEY_ALTITUDE_AIRBORNE_DESCENT, stateMachineSettings.sampleRateAirborneDescent);
  // if (_sampleRateAirborneDescent <= 0) {
  //   _sampleRateAirborneDescent = stateMachineSettings.sampleRateAirborneDescent;
  //   preferences.putInt(PREFERENCE_KEY_ALTITUDE_AIRBORNE_DESCENT, _sampleRateAirborneDescent);
  // }
  // _sampleRateGround = preferences.getInt(PREFERENCE_KEY_ALTITUDE_GROUND, stateMachineSettings.sampleRateGround);
  // if (_sampleRateGround <= 0) {
  //   _sampleRateGround = (int)PREFERENCE_KEY_ALTITUDE_GROUND;
  //   preferences.putInt(PREFERENCE_KEY_ALTITUDE_GROUND, _sampleRateGround);
  // }
  // preferences.end();
#endif

  if (_stateMachineSettings.altitudeLiftoff <= 0)
    _stateMachineSettings.altitudeLiftoff = ALTITUDE_LIFTOFF;
  if (_stateMachineSettings.sampleRates.airborneAscent <= 0)
    _stateMachineSettings.sampleRates.airborneAscent = SAMPLE_RATE_AIRBORNE_ASCENT;
  if (_stateMachineSettings.sampleRates.airborneDescent <= 0)
    _stateMachineSettings.sampleRates.airborneDescent = SAMPLE_RATE_AIRBORNE_DESCENT;
  if (_stateMachineSettings.sampleRates.ground <= 0)
    _stateMachineSettings.sampleRates.ground = SAMPLE_RATE_GROUND;

  // _stateMachineSettings.altitudeLiftoff = ALTITUDE_LIFTOFF;
  // _stateMachineSettings.sampleRates.aborted = SAMPLE_MEASURES_ABORTED;
  // _stateMachineSettings.sampleRates.landed = SAMPLE_RATE_LANDED;
  _stateMachineSettings.sampleMeasures.aborted = SAMPLE_MEASURES_ABORTED;
  _stateMachineSettings.sampleMeasures.apogee = SAMPLE_MEASURES_APOGEE;
  _stateMachineSettings.sampleMeasures.landed = SAMPLE_MEASURES_LANDED;
  debug();
  debug();
  debug();
  debug(F("setup..._stateMachineSettings.sampleMeasures.apogee?"), _stateMachineSettings.sampleMeasures.apogee);
  debug();
  debug();
  debug();

  _altitudeLiftoff = _stateMachineSettings.altitudeLiftoff;
  _sampleRateAirborneAscent = _stateMachineSettings.sampleRates.airborneAscent;
  _sampleRateAirborneDescent = _stateMachineSettings.sampleRates.airborneDescent;
  _sampleRateGround = _stateMachineSettings.sampleRates.ground;

  _flightLog->measures = _stateMachineSettings.sampleMeasures.apogee;
  debug();
  debug();
  debug();
  debug(F("setup..._flightLog->measures"), _flightLog->measures);
  debug();
  debug();
  debug();

  _altitudeGround = _altitudeLiftoff / 2;

  Serial.println(F("\t...state machine settings..."));
  _displaySettings();
  Serial.println();

  debug();
  debug();
  debug();
  debug(F("setup..._flightLog->measures"), _flightLog->measures);
  debug(F("setup..._stateMachineSettings.sampleMeasures.apogee?"), _stateMachineSettings.sampleMeasures.apogee);
  debug();
  debug();
  debug();

  save(_altitudeLiftoff, _sampleRateAirborneAscent, _sampleRateAirborneDescent, _sampleRateGround);

  debug();
  debug();
  debug();
  debug(F("setup..._flightLog->measures"), _flightLog->measures);
  debug(F("setup..._stateMachineSettings.sampleMeasures.apogee?"), _stateMachineSettings.sampleMeasures.apogee);
  debug();
  debug();
  debug();

  Serial.println(F("...state machine setup successful."));
  Serial.println();
  return 0;
}

flightStates stateMachine::state() {
  return _loopState;
}

const char* stateMachine::stateName() {
  const char* name;
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

int stateMachine::_checkValues(int values[], int value, int defaultValue, int size) {
  if (value < 0)
    return defaultValue;

  for (int i = 0; i < size; i++) {
    if (value == values[i])
      return value;
  }
  
  return defaultValue;
}

void stateMachine::_displaySettings() {
  Serial.print(F("\taltitudeLiftoff="));
  Serial.print(_altitudeLiftoff);
  Serial.print(F(", default="));
  Serial.println(_stateMachineSettings.altitudeLiftoff);
  Serial.print(F("\taltitudeGround="));
  Serial.println(_altitudeGround);
  Serial.print(F("\tsampleRateAirborneAscent="));
  Serial.print(_sampleRateAirborneAscent);
  Serial.print(F(", default="));
  Serial.println(_stateMachineSettings.sampleRates.airborneAscent);
  Serial.print(F("\tsampleRateAirborneDescent="));
  Serial.print(_sampleRateAirborneDescent);
  Serial.print(F(", default="));
  Serial.println(_stateMachineSettings.sampleRates.airborneDescent);
  Serial.print(F("\tsampleRateGround="));
  Serial.print(_sampleRateGround);
  Serial.print(F(", default="));
  Serial.println(_stateMachineSettings.sampleRates.ground);
  Serial.print(F("\tsampleRateGround="));
  Serial.print(_sampleRateGround);
  Serial.print(F(", default="));
  Serial.println(_stateMachineSettings.sampleRates.ground);
}

void stateMachine::_updateTrace(unsigned long currentTimestamp, long diffTime) {
  atmosphereValues atmosphereValuesO = readSensorAtmosphere();
  float altitude = atmosphereValuesO.altitude;
  float altitudeDelta = altitude - _flightLog->instance()->getData().altitudeLast;
  _updateTrace(currentTimestamp, diffTime, atmosphereValuesO, altitudeDelta);
}

void stateMachine::_updateTrace(unsigned long currentTimestamp, long diffTime, atmosphereValues atmosphereValuesO, float altitudeDelta) {
  _flightLog->instance()->setAltitudeLast(_flightLog->instance()->getData().altitudeCurrent);
  _flightLog->instance()->setTimestampPrevious(_flightLog->instance()->getData().timestampCurrent);

  _flightLog->instance()->setTimestampCurrent(currentTimestamp);

  // Log the flight altitude...
  _flightLog->instance()->setTraceCurrentTime(diffTime);
  _flightLog->instance()->setTraceCurrentAltitude(atmosphereValuesO.altitude);

  // Log the flight temperature and pressure...
  _flightLog->instance()->setTraceCurrentHumidity(atmosphereValuesO.temperature);
  _flightLog->instance()->setTraceCurrentTemperature(atmosphereValuesO.temperature);
  _flightLog->instance()->setTraceCurrentPressure(atmosphereValuesO.pressure);

  // Log the flight x, y, and z accelerations...
  accelerometerValues accelerometerValuesO = readSensorAccelerometer();
  _flightLog->instance()->setTraceCurrentAccelX(accelerometerValuesO.x);
  _flightLog->instance()->setTraceCurrentAccelY(accelerometerValuesO.y);
  _flightLog->instance()->setTraceCurrentAccelZ(accelerometerValuesO.z);
  
  // Log the flight x, y, and z gyroscope...
  gyroscopeValues gyroscopeValuesO = readSensorGyroscope();
  _flightLog->instance()->setTraceCurrentGyroX(gyroscopeValuesO.x);
  _flightLog->instance()->setTraceCurrentGyroY(gyroscopeValuesO.y);
  _flightLog->instance()->setTraceCurrentGyroZ(gyroscopeValuesO.z);
  
  // Log the flight x, y, and z magnetometer...
  magnetometerValues magnetometerValues0 = readSensorMagnetometer();
  _flightLog->instance()->setTraceCurrentMagnetometerX(magnetometerValues0.x);
  _flightLog->instance()->setTraceCurrentMagnetometerY(magnetometerValues0.y);
  _flightLog->instance()->setTraceCurrentMagnetometerZ(magnetometerValues0.z);

  // Add to the set data to the flight.
  _flightLog->instance()->copyTraceCurrentToArray();
}

stateMachine _stateMachine;
