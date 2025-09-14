#ifndef _FLIGHT_LOG_H
#define _FLIGHT_LOG_H

#include <commands.h>
#include "flightData.h"
#include "flightLoggerNull.h"

template<typename T> class flightLog {
  public:
    // flightLog();
    void init(unsigned long timestamp);
    void reset();
    void setup(deviceCommands* commands);
    
    bool airborne = false;
    bool aborted;
    float altitudeInitial;
    float humidityInitial;
     T instance;
    // Number of measures to do so that we are sure that apogee has been reached
    unsigned long measures = 5;
    float pressureInitial;
    bool recording;
    float temperatureInitial;
    bool touchdown = false;
};

#endif