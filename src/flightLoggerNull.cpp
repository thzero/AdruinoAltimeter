#include <ArduinoJson.h>
#include <time.h>

#include <debug.h>
#include "flightLoggerNull.h"
#include <utilitiesTime.h>

flightLoggerNull::flightLoggerNull() {
  _flightDataTrace = nullptr;
  _flightDataTraceIndex = 0;
}

bool flightLoggerNull::eraseFlights() {
  return true;
}

bool flightLoggerNull::eraseLast() {
  return true;
}

bool flightLoggerNull::exists(int flightNbr) {
  return true;
}

bool flightLoggerNull::initFileSystem() {
  return true;
}

bool flightLoggerNull::listAsJson(JsonArray flightLogs) {
  return true;
}

bool flightLoggerNull::readFile(int flightNbr) {
  return true;
}

bool flightLoggerNull::readFileAsJson(int flightNbr, JsonObject object) {
  return true;
}

int flightLoggerNull::reindexFlights() {
  return true;
}

bool flightLoggerNull::writeFile(int flightNbr) {
  return true;
}

bool flightLoggerNull::writeFlightCurrent() {
  return writeFile(geFlightNbrsLast() + 1);
}