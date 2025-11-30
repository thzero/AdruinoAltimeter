#ifndef _FLIGHT_LOG_H
#define _FLIGHT_LOG_H

#include <commands.h>

#include "flightData.h"
#include "flightLoggerBase.h"

class flightLog {
  public:
    flightLog();
    void init(unsigned long timestamp);
    flightLoggerBase* instance();
    void reset();
    byte setup(flightLoggerBase* instance, deviceCommands* deviceCommands);
    
    bool airborne = false;
    bool aborted;
    float altitudeInitial;
    flightDataTraceStruct current;
    flightDataTraceStruct2 current2;
    float humidityInitial;
    // Number of measures to do so that we are sure that apogee has been reached
    unsigned int measures = 5;
    float pressureInitial;
    bool recording;
    float temperatureInitial;
    bool touchdown = false;

  protected:
    flightLoggerBase* _instance;
};

extern flightLog _flightLog;

#endif