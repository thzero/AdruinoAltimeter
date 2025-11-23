#ifndef _STATE_MACHINE_CONSTANTS_H
#define _STATE_MACHINE_CONSTANTS_H

#define ALTITUDE_LIFTOFF 20

// Sample rate is in milliseconds
// Based on Eggtimer Quantum documentation
// https://eggtimerrocketry.com/wp-content/uploads/2024/02/Eggtimer-Quantum-1_09G.pdf, page 25
#define SAMPLE_RATE_ABORTED 2
// #define SAMPLE_RATE_AIRBORNE_ASCENT 50
#define SAMPLE_RATE_AIRBORNE_ASCENT 1000
// #define SAMPLE_RATE_AIRBORNE_DESCENT 5
#define SAMPLE_RATE_AIRBORNE_DESCENT 1000
// #define SAMPLE_RATE_GROUND 50
#define SAMPLE_RATE_GROUND 1000
// #define SAMPLE_RATE_LANDED 5
#define SAMPLE_RATE_LANDED 1000
#define SAMPLE_RATE_SENSORS 50
#define SAMPLE_MEASURES_ABORTED 20
#define SAMPLE_MEASURES_APOGEE 5
#define SAMPLE_MEASURES_LANDED 10

#endif