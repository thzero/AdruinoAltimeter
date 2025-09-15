#ifndef _FLIGHT_LOG_H
#define _FLIGHT_LOG_H

#include <commands.h>
#include "flightData.h"
#include "flightLoggerBase.h"

class flightLog {
  public:
    flightLog();
    void init(unsigned long timestamp);
    void reset();
    byte setup(deviceCommands* commands, flightLoggerBase* instance);
    
    bool airborne = false;
    bool aborted;
    float altitudeInitial;
    float humidityInitial;
    // Number of measures to do so that we are sure that apogee has been reached
    unsigned long measures = 5;
    float pressureInitial;
    bool recording;
    float temperatureInitial;
    bool touchdown = false;

  protected:
    flightLoggerBase* _instance;
};

#endif