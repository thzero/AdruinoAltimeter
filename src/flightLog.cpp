#include "flightLog.h"

flightLog::flightLog() {
  reset();
}

void flightLog::init(unsigned long timestamp) {
  // Initialize the flight...
  aborted = false;
  recording = true;

  airborne = true;
  touchdown = false;

  _instance->init(timestamp);
}

void flightLog::reset() {
  // Reset the flight...
  aborted = false;
  recording = false;

  airborne = false;
  touchdown = false;

  if (_instance != nullptr)
    _instance->reset();
}

byte flightLog::setup(flightLoggerBase* instance, deviceCommands* deviceCommands) {
  Serial.println(F("\nSetup flight logger..."));

  _instance = instance;
  if (_instance == nullptr)
    return 2;
  if (!_instance->initFileSystem()) {
    Serial.println(F("Failed to initialize flight logger"));
    return 2;
  }

  if (deviceCommands != nullptr) {
    // TODO: setup flight log commands...
    //   Serial.println(F("h;\thelp menu"));
    //   Serial.println(F("a;\toutput to serial all flight logs"));
    //   Serial.println(F("ae;\texpanded output to serial all flight logs"));
    //   Serial.println(F("e;\terase all recorded flights"));
    // #ifdef DEV
    //   Serial.println(F("i;\tI2C scanner"));
    // #endif
    //   Serial.println(F("l;\toutput to serial a list of all flight logs"));
    // #ifdef DEV
    //   Serial.println(F("lj;\toutput to serial a list of all flight logs - json"));
    // #endif
    //   Serial.println(F("n;\toutput to serial the number of recorded flight logs"));
    //   Serial.println(F("r<#>;\toutput to serial data for flight log #"));
    //   Serial.println(F("re<#>;\texpanded output to serial data for flight log #"));
    //   // Serial.println(F("z;\ttoggle flight telemetry"));
    //   Serial.println(F("x;\tdelete last recorded flight log"));
    //   Serial.println(F("z;\treindex recorded flight log index"));


      // output to serial all flight logs
      // if (command == 'a') {
      //   handleFightsOutputSerial(commandBuffer);
      //   return;
      // }
      // erase all recorded flight logs
      // if (command == 'e') {
      //   _flightLog._instance->eraseFlights();
      //   return;
      // }
      // // output to seriali a list of all flight logs
      // if (command == 'l') {
      //   handleFlightsListing(commandBuffer);
      //   return;
      // }
      // // output to serial the number of recorded flight logs
      // if (command == 'n') {
      //   handleFlightsNumberNax(commandBuffer);
      //   return;
      // }
      // if (command == 'p') {
      //   handlesPreferenceOutput(commandBuffer);
      //   return;
      // }
      // // output to serial data for the specified flight log
      // if (command == 'r') {
      //   handleFlightOutputSerial(commandBuffer);
      //   return;
      // }
      // // toggle flight log telemetry
      // if (command == 't') {
      //   // not implemented
      //   return;
      // }
      // // delete last recorded flight log
      // if (command == 'x') {
      //   _flightLog._instance->eraseLast();
      //   return;
      // }
      // // reindex recorded flight log index
      // if (command == 'z') {
      //   _flightLog._instance->reindexFlights();
      //   return;
      // }


      // _deviceCommands.initCommand('d', _diagnosticsDisplay, true, "d", "display the diagnostics");
      // _deviceCommands.initCommand('j', _diagnosticsToggle, true, "j", "toggle the diagnostics");
      // _deviceCommands.initCommand('$', rtcTimestampCommand, true, "$<unsigned long>", "set the time");
      // _deviceCommands.initCommand('@', calibrationSensorsResetCommand, true, "@", "recalibrate the gyro");
    }

  Serial.println(F("...flight logger successful."));

  return 0;
}