#include <Arduino.h>
#if defined(ESP32)
// #include <Preferences.h>
#endif

// #include <button.h>
#include <debug.h>
// #include <neoPixel.h>
// #include <network.h>
// #include <sensor.h>
// #ifdef DEV_SIM
// #include "simulation.h"
// #endif
#include "settings.h"
#include "stateMachine.h"
// #include <time.h>
// #include <tft.h>
// #include <utilities.h>

stateMachine::stateMachine() {
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
  // Determine the aborted loop time delay based on sampling rate.
  unsigned long delta = _throttleAborted.determine('a', deltaElapsed, _stateMachineSettings.sampleRates.aborted);
  if (delta == 0)
    return;

  // Functionality that happen on the tick goes here:

  // _neoPixelBlinker.blink(0xFF0000);

  // Transition to the GROUND stage.
  if (_countdownAborted > _stateMachineSettings.sampleMeasures.aborted) {
    loopStateABORTEDToGROUND(timestamp, deltaElapsed);
    return;
  }

  _countdownAborted++;
  debug(F("countdownAborted"), _countdownAborted); // TODO
}

void stateMachine::loopStateABORTEDToGROUND(unsigned long timestamp, unsigned long deltaElapsed) {
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F("...ABORTED to GROUND!!!!"));
  debug(F("...ABORTED to GROUND!!!!"));
  debug(F("...ABORTED to GROUND!!!!"));
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F(""));

  if (_loopStateChangedFunc != nullptr)
    _loopStateChangedFunc(FLIGHT_STATE_GROUND, _loopState, timestamp, deltaElapsed);

  _loopState = FLIGHT_STATE_GROUND;
  loopStateToGROUND(timestamp, deltaElapsed);
}

void stateMachine::loopStateAIRBORNEToABORTED(unsigned long timestamp, unsigned long deltaElapsed, char message1[], char message2[]) {
  // Something went wrong and aborting...

  // _flightLogger.aborted = true;
  // _flightLogger.airborne = false;
  // _flightLogger.recording = false;
  // _flightLogger.touchdown = false;

// #ifdef DEV_SIM
//   if (_simulation.isRunning()) 
//     _simulation.stop();
// #endif

  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F("...ABORTED!!!!"));
  debug(F("...ABORTED!!!!"));
  Serial.println(message1);
  Serial.println(message2);
  debug(F("...ABORTED!!!!"));
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F(""));

  _countdownAborted = 0;

  if (_loopStateChangedFunc != nullptr)
    _loopStateChangedFunc(FLIGHT_STATE_ABORTED, _loopState, timestamp, deltaElapsed);
  
  _loopState = FLIGHT_STATE_ABORTED;
}

float stateMachine::loopStateAIRBORNE(unsigned long currentTimestamp, long diffTime) {
//   atmosphereValues atmosphere = readSensorAtmosphere();
//   float altitude = readSensorAltitude(atmosphere);
//   float altitudeDelta = altitude - _flightLogger.instance.getData().altitudeLast;
//   _flightLogger.instance.setAltitudeCurrent(altitude);
// #ifdef DEBUG_ALTIMETER
//   debug(F("loopStateAIRBORNE...altitude"), altitude);
//   debug(F("loopStateAIRBORNE...altitudeDelta"), altitudeDelta);
//   debug(F("loopStateAIRBORNE...altitudeCurrent"), _flightLogger.instance.getData().altitudeCurrent);
// #endif
//   _flightLogger.instance.setTimestampCurrent(currentTimestamp);

//   // Log the flight altitude...
//   _flightLogger.instance.setTraceCurrentTime(diffTime);
//   _flightLogger.instance.setTraceCurrentAltitude(_flightLogger.instance.getData().altitudeCurrent);

//   // Log the flight temperature and pressure...
//   atmosphereValues atmosphereValuesO = readSensorAtmosphere();
//   _flightLogger.instance.setTraceCurrentHumidity(atmosphereValuesO.temperature);
//   _flightLogger.instance.setTraceCurrentTemperature(atmosphereValuesO.temperature);
//   _flightLogger.instance.setTraceCurrentPressure(atmosphereValuesO.pressure);

//   // Log the flight x, y, and z accelerations...
  
//   accelerometerValues accelerometerValuesO = readSensorAccelerometer();
//   _flightLogger.instance.setTraceCurrentAccelX(accelerometerValuesO.x);
//   _flightLogger.instance.setTraceCurrentAccelY(accelerometerValuesO.y);
//   _flightLogger.instance.setTraceCurrentAccelZ(accelerometerValuesO.z);
  
//   gyroscopeValues gyroscopeValuesO = readSensorGyroscope();
//   _flightLogger.instance.setTraceCurrentGyroX(gyroscopeValuesO.x);
//   _flightLogger.instance.setTraceCurrentGyroY(gyroscopeValuesO.y);
//   _flightLogger.instance.setTraceCurrentGyroZ(gyroscopeValuesO.z);

//   // Add to the set data to the flight.
//   _flightLogger.instance.copyTraceCurrentToArray();

//   _flightLogger.instance.setAltitudeLast(altitude);
//   _flightLogger.instance.setTimestampPrevious(currentTimestamp);

//   // sendTelemetry(timestamp - _flightLogger.instance.getData().timestampInitial , atmosphere, accelerometer, gryoscope, altitude, diffTime);

//   drawTftFlightAirborne(currentTimestamp, diffTime);

  // return altitudeDelta;
  return 0;
}

void stateMachine::loopStateAIRBORNE_ASCENT(unsigned long timestamp, unsigned long deltaElapsed) {
//   unsigned long delta = _throttleAirborneAscent.determine(deltaElapsed, _sampleRateAirborneAscent);
//   if (delta == 0)
//     return;

//   // Functionality that happen on the tick goes here:

//   _neoPixelBlinker.blink(0x00FF00);

//   long currentTimestamp = timestamp - _flightLogger.instance.getData().timestampLaunch;
// #ifdef DEBUG_ALTIMETER
//   debug(F("loopStateAIRBORNE_ASCENT...timestamp"), timestamp);
//   debug(F("loopStateAIRBORNE_ASCENT...currentTimestamp"), currentTimestamp);
// #endif

//   // Determine different in time between the last step...
//   long diffTime = currentTimestamp - _flightLogger.instance.getData().timestampPrevious;

//   float altitudeDelta = loopStateAIRBORNE(currentTimestamp, diffTime);

//   // Detect apogee by taking X number of measures as long as the current is less
//   // than the last recorded altitude.
// #ifdef DEBUG_ALTIMETER
//   debug(F("loopStateAIRBORNE_ASCENT...altitudeLast"), _flightLogger.instance.getData().altitudeLast);
//   debug(F("loopStateAIRBORNE_ASCENT...altitudeDelta"), altitudeDelta);
// #endif
//   if (altitudeDelta < 0) {
//     if (_flightLogger.measures == _stateMachineSettings.sampleMeasures.apogee) {
//       _flightLogger.instance.setAltitudeApogeeFirstMeasure(_flightLogger.instance.getData().altitudeLast);
//       _flightLogger.instance.setTimestampApogeeFirstMeasure(currentTimestamp);
//     }
//     _flightLogger.measures = _flightLogger.measures - 1;
// #ifdef DEBUG_ALTIMETER
//     debug(F("loopStateAIRBORNE_ASCENT...measures"), _flightLogger.measures);
// #endif
//     if (_flightLogger.measures == 0) {
//       // Detected apogee.
//       loopStateAIRBORNE_ASCENTToAIRBORNE_DESCENT(timestamp, deltaElapsed);
//       return;
//     }
//   } 
//   else {
//     if (_flightLogger.measures < _stateMachineSettings.sampleMeasures.apogee) {
// #ifdef DEBUG_ALTIMETER
//       debug(F("loopStateAIRBORNE_ASCENT...measures"), F("reset"));
// #endif
//       // If the current is greater than the last, then reset as it was potentially
//       // a false positive.
//       _flightLogger.instance.setAltitudeApogeeFirstMeasure(0);
//       _flightLogger.instance.setTimestampApogeeFirstMeasure(0);
//       _flightLogger.instance.setAltitudeLast(_flightLogger.instance.getData().altitudeCurrent);
//       _flightLogger.measures = _stateMachineSettings.sampleMeasures.apogee;
//     }
//   }

//   // Check for timeouts...
//   bool timestampApogeeCheck = currentTimestamp > _stateMachineSettings.timeOutTimeToApogee;
// #ifdef DEBUG_ALTIMETER
//   debug(F("loopStateAIRBORNE_ASCENT...timeOutTimeToApogee"), _stateMachineSettings.timeOutTimeToApogee);
//   debug(F("loopStateAIRBORNE_ASCENT...currentTimestamp"), currentTimestamp);
//   debug(F("loopStateAIRBORNE_ASCENT...timestampApogeeCheck"), timestampApogeeCheck);
// #endif
//   if (timestampApogeeCheck) {
//     // Something went wrong and apogee was never found, so abort!
//     loopStateAIRBORNEToABORTED(timestamp, deltaElapsed, "Time to apogee threshold exceeded!", "AIRBORNE_ASCENT aborted, returning to GROUND!!!!");
//     return;
//   }

//   bool timeoutRecordingCheck = currentTimestamp > _stateMachineSettings.timeoutRecording;
// #ifdef DEBUG_ALTIMETER
//   debug(F("loopStateAIRBORNE_ASCENT...timestampLaunch"), _flightLogger.instance.getData().timestampLaunch);
//   debug(F("loopStateAIRBORNE_ASCENT...timeoutRecording"), _stateMachineSettings.timeoutRecording);
//   debug(F("loopStateAIRBORNE_ASCENT...currentTimestamp"), currentTimestamp);
//   debug(F("loopStateAIRBORNE_ASCENT...timeoutRecordingCheck"), timeoutRecordingCheck);
// #endif
//   if (timeoutRecordingCheck) {
//     // Something went wrong., so abort!
//     loopStateAIRBORNEToABORTED(timestamp, deltaElapsed, "Time to apogee threshold exceeded!", "AIRBORNE_ASCENT aborted, returning to GROUND!!!!");
//     return;
//   }
}

void stateMachine::loopStateAIRBORNE_ASCENTToAIRBORNE_DESCENT(unsigned long timestamp, unsigned long deltaElapsed) {
  // _flightLogger.instance.setAltitudeApogee(_flightLogger.instance.getData().altitudeApogeeFirstMeasure);
  // _flightLogger.instance.setTimestampApogee(_flightLogger.instance.getData().timestampApogeeFirstMeasure);

  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F("...DESCENT!!!!"));
  debug(F("...DESCENT!!!!"));
  debug(F("...DESCENT!!!!"));
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F(""));

  if (_loopStateChangedFunc != nullptr)
    _loopStateChangedFunc(FLIGHT_STATE_AIRBORNE_DESCENT, _loopState, timestamp, deltaElapsed);

  _loopState = FLIGHT_STATE_AIRBORNE_DESCENT;
}

void stateMachine::loopStateAIRBORNE_DESCENT(unsigned long timestamp, unsigned long deltaElapsed) {
//   int delta = _throttleAirborneDescent.determine(deltaElapsed, _sampleRateAirborneDescent);
//   if (delta == 0)
//     return;

//   // Functionality that happen on the tick goes here:

//   _neoPixelBlinker.blink(0x0000FF);

//   long currentTimestamp = millis() - _flightLogger.instance.getData().timestampLaunch;

//   // Determine different in time between the last step...
//   long diffTime = currentTimestamp - _flightLogger.instance.getData().timestampPrevious;

//   float altitudeDelta = loopStateAIRBORNE(currentTimestamp, diffTime);

//   bool timeoutRecordingCheck = ((timestamp - _flightLogger.instance.getData().timestampLaunch) > _stateMachineSettings.timeoutRecording);
// #ifdef DEBUG_ALTIMETER
//   debug(F("loopStateAIRBORNE_DESCENT...timestamp"), timestamp);
//   debug(F("loopStateAIRBORNE_DESCENT...timestampLaunch"), _flightLogger.instance.getData().timestampLaunch);
//   debug(F("loopStateAIRBORNE_DESCENT...timeoutRecordingCheck"), timeoutRecordingCheck);
// #endif

//   if (timeoutRecordingCheck) {
//     // Something went wrong and the recordingt timeout was hit, so abort!
//     loopStateAIRBORNEToABORTED(timestamp, deltaElapsed, "Exceeded recording timeout!", "AIRBORNE_DESCENT aborted, returning to GROUND!!!!");
//     return;
//   }

//   float altitudeCurrent = _flightLogger.instance.getData().altitudeCurrent;
//   float altitudeLandingTarget = _flightLogger.altitudeInitial + _altitudeGround;
//   bool altitudeCheck = altitudeCurrent < altitudeLandingTarget;
// #ifdef DEBUG_ALTIMETER
//   debug(F("loopStateAIRBORNE_DESCENT...altitudeCurrent"), altitudeCurrent);
//   debug(F("loopStateAIRBORNE_DESCENT...altitudeGround"), _altitudeGround);
//   debug(F("loopStateAIRBORNE_DESCENT...altitudeLandingTarget"), altitudeLandingTarget);
//   debug(F("loopStateAIRBORNE_DESCENT...altitudeCheck"), altitudeCheck);
// #endif
//   if (altitudeCheck) {
//   _flightLogger.instance.setAltitudeTouchdown(_flightLogger.instance.getData().altitudeLast);
//   _flightLogger.instance.setTimestampTouchdown(_flightLogger.instance.getData().timestampPrevious);
//     // Passed the descent touchdown altitude check, so the flight log is ended and return to GROUND
//     loopStateAIRBORNE_DESCENTToLANDED(timestamp, deltaElapsed);
//     return;
//   }
}

void stateMachine::loopStateAIRBORNE_DESCENTToLANDED(unsigned long timestamp, unsigned long deltaElapsed) {
  // Complete the flight
  Serial.println(F("Flight has ended!!!"));

  // _flightLogger.airborne = false;
  // _flightLogger.recording = false;

  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F("...LANDED!!!!"));
  debug(F("...LANDED!!!!"));
  debug(F("...LANDED!!!!"));
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F(""));

  if (_loopStateChangedFunc != nullptr)
    _loopStateChangedFunc(FLIGHT_STATE_LANDED, _loopState, timestamp, deltaElapsed);

  _loopState = FLIGHT_STATE_LANDED;
}

void stateMachine::loopStateLANDED(unsigned long timestamp, unsigned long deltaElapsed) {
//   // Determine the ground loop time delay based on sampling rate.
//   unsigned long delta = _throttleLanded.determine(deltaElapsed, _stateMachineSettings.sampleRates.landed);
//   if (delta == 0)
//     return;

//   // Functionality that happen on the tick goes here:

//   _neoPixelBlinker.blink(0xFF00FF);

//   // debug(F("loopStateLANDED...timestamp"), timestamp);

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
// #ifdef DEV_SIM
//   if (_simulation.isRunning()) 
//     _simulation.stop();
// #endif

  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F("...GROUNDED!!!!"));
  debug(F("...GROUNDED!!!!"));
  debug(F("...GROUNDED!!!!"));
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F(""));

  if (_loopStateChangedFunc != nullptr)
    _loopStateChangedFunc(FLIGHT_STATE_GROUND, _loopState, timestamp, deltaElapsed);

  _loopState = FLIGHT_STATE_GROUND;
  _countdownAborted = 0;
  _countdownLanded = 0;

// #ifdef DEBUG
//   Serial.println(F("\nWriting output..."));
// #endif
//   _flightLogger.instance.writeFlightCurrent();
// #ifdef DEBUG
//   Serial.println(F("...writing output.\n"));
// #endif

//   Serial.println(F("Serial Output"));
//   _flightLogger.instance.outputSerial();
//   Serial.print(F("\nExpanded Serial Output\n\n"));
//   _flightLogger.instance.outputSerialExpanded();
//   Serial.print(F("\n"));

  loopStateToGROUND(timestamp, deltaElapsed);
}

void stateMachine::loopStateToGROUND(unsigned long timestamp, unsigned long deltaElapsed) {
  // To avoid battery drain, etc. user should choose to turn on networking...
  // networkStart();

  // drawTftReset();
  // drawTftSplash();
}

void stateMachine::loopStateGROUND(unsigned long timestamp, unsigned long deltaElapsed) {
  // Serial.printf(F("...loopStateGROUND... %d\n"), deltaElapsed);

  if (_loopStateFunc != nullptr)
    _loopStateFunc(_loopState, timestamp, deltaElapsed);

  // Determine the ground loop time delay based on sampling rate.
  unsigned long delta = _throttleGround.determine('g', deltaElapsed, _sampleRateGround);
  if (delta == 0)
    return;

  // debug(F("stateGROUND...timestamp"), timestamp);
  
  if (_loopStateThrottledFunc != nullptr)
    _loopStateThrottledFunc(_loopState, timestamp, deltaElapsed);

  // Get the current altitude and determine the delta from initial.
//   float altitude = readSensorAltitude();
//   float altitudeLaunchApogeeTarget = _flightLogger.altitudeInitial + _altitudeLiftoff;

// #ifdef DEBUG_ALTIMETER
//   // debug(F("stateGROUND...processing, delta"), delta);
//   // debug(F("stateGROUND...processing, deltaElapsed"), deltaElapsed);
//   debug(F("stateGROUND...altitude"), altitude);
//   debug(F("stateGROUND...altitudeInitial"), _flightLogger.altitudeInitial);
//   debug(F("stateGROUND...altitudeLiftoffCutoff"), _altitudeLiftoff);
//   debug(F("stateGROUND...altitudeLaunchApogeeTarget"), altitudeLaunchApogeeTarget);
//   debug(F("stateGROUND...altitudeLiftoff?"), (altitude > altitudeApogeeTarget));
// #endif

  // // Check for whether we've left the ground
  // if (altitude > altitudeLaunchApogeeTarget) {
  //   // Transition to the AIRBORNE_ASCENT ascent stage.
  //   loopStateGROUNDToAIRBORNE_ASCENT(timestamp, deltaElapsed);
  //   return;
  // }
}

void stateMachine::loopStateGROUNDToAIRBORNE_ASCENT(unsigned long timestamp, unsigned long deltaElapsed) {
  // Turn off networks, we don't need it in the air...
  // networkDisable();

  // _neoPixelBlinker.off();
  
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F("...AIRBORNE!!!!"));
  debug(F("...AIRBORNE!!!!"));
  debug(F("...AIRBORNE!!!!"));
  debug(F(""));
  debug(F(""));
  debug(F(""));
  debug(F(""));

  // Re-initialize the flight...
  // _flightLogger.init(timestamp);

  // drawTftReset();
  // drawTftFlightAirborneStart();

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

void stateMachine::reset() {
  Serial.println(F("Reset state machine..."));

  _altitudeLiftoff = _stateMachineSettings.altitudeLiftoff;
  _sampleRateAirborneAscent = _stateMachineSettings.sampleRates.airborneAscent;
  _sampleRateAirborneDescent = _stateMachineSettings.sampleRates.airborneDescent;
  _sampleRateGround = _stateMachineSettings.sampleRates.ground;
  
  save(_altitudeLiftoff, _sampleRateAirborneAscent, _sampleRateAirborneDescent, _sampleRateGround);

  Serial.println(F("...state machine reset successful."));
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

  _altitudeLiftoff = _checkValues(altitudeLiftoffValues, altitudeLiftoff, _stateMachineSettings.altitudeLiftoff, sizeof(altitudeLiftoffValues) / sizeof(altitudeLiftoffValues[0]));
  _sampleRateAirborneAscent = _checkValues(sampleRateAirborneAscentValues, sampleRateAirborneAscent, _stateMachineSettings.sampleRates.airborneAscent, sizeof(sampleRateAirborneAscentValues) / sizeof(sampleRateAirborneAscentValues[0]));
  _sampleRateAirborneDescent = _checkValues(sampleRateAirborneDecentValues, sampleRateAirborneDecent, _stateMachineSettings.sampleRates.airborneDescent, sizeof(sampleRateAirborneDecentValues) / sizeof(sampleRateAirborneDecentValues[0]));
  _sampleRateGround = _checkValues(sampleRateGroundValues, sampleRateGround, _stateMachineSettings.sampleRates.ground, sizeof(sampleRateGroundValues) / sizeof(sampleRateGroundValues[0]));
  
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
#endif

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

  _altitudeGround = _altitudeLiftoff / 2;

#ifdef DEBUG
  Serial.println(F("\t\t...state machine... saved state"));
  _displaySettings();
  Serial.println(F(""));
#endif

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

  _altitudeLiftoff = _stateMachineSettings.altitudeLiftoff;
  _sampleRateAirborneAscent = _stateMachineSettings.sampleRates.airborneAscent;
  _sampleRateAirborneDescent = _stateMachineSettings.sampleRates.airborneDescent;
  _sampleRateGround = _stateMachineSettings.sampleRates.ground;
  _displaySettings();

  _altitudeGround = _altitudeLiftoff / 2;

#ifdef DEBUG
  Serial.println(F("\t...state machine settings..."));
  _displaySettings();
  Serial.println(F(""));
#endif

  save(_altitudeLiftoff, _sampleRateAirborneAscent, _sampleRateAirborneDescent, _sampleRateGround);

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
}

stateMachine _stateMachine;
