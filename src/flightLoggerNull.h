#ifndef _FLIGHT_LOGGER_LFS_H
#define _FLIGHT_LOGGER_LFS_H

#include <ArduinoJson.h>

#include "flightData.h"
#include "flightLog.h"
#include "flightLoggerBase.h"

#define FORMAT_LITTLEFS_IF_FAILED true

class flightLoggerNull : public flightLoggerBase {
  public:
    flightLoggerNull();
    bool eraseFlights() override;
    bool eraseLast() override;
    bool exists(int flightNbr) override;
    bool initFileSystem();
    bool listAsJson(JsonArray flightLogs) override;
    bool readFile(int flightNbr) override;
    bool readFileAsJson(int flightNbr, JsonObject object) override;
    int reindexFlights() override;
    bool writeFile(int flightNbr) override;
    bool writeFlightCurrent() override;
};

extern byte setupFlightLog(deviceCommands* commands);

#endif