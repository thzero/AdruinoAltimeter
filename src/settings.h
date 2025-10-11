#ifndef _SEttINGS_H
#define _SEttINGS_H

struct __attribute__((packed)) settingsSampleMeasuresStruct {
    int aborted;
    int apogee;
    int landed;
};

struct __attribute__((packed)) settingsSampleRatesStruct {
    int airborneAscent;
    int airborneDescent;
    int aborted;
    int ground;
    int landed;
};

struct __attribute__((packed)) settingsStruct {
    int altitudeLiftoff;
    settingsSampleMeasuresStruct sampleMeasures;
    settingsSampleRatesStruct sampleRates;
};

#endif