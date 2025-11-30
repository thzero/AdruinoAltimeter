#include <Arduino.h>
#include <ArduinoJson.h>

#include <debug.h>
#include <utilities.h>

#include "simulation.h"

// https://rocketmime.com/rockets/rckt_sim.html#Drag

struct simulationConfigStruct simulationConfigDefault;

simulation::simulation() {
}

bool simulation::isRunning() {
  return _running;
}

void simulation::evaluateTimestep(unsigned long deltaT, float drag, float Mr, float Ft) {
  // TODO: Introduce some  point - recommendation seems to be to use Simplex noise from FastLED
  // Leap-frog Euler method -- interleave calculation of DeltaX, DeltaV
  // Serial.print(F("G: "));
  // Serial.printf("%f\n", GravConstant);
  // Serial.print(F("Mr: "));
  // Serial.println(Mr);
  // Serial.print(F("_altitudeCurrent: "));
  // Serial.println(_altitudeCurrent);

  // Compute the total force
  // float F = (-1 * GravConstant) * EarthRadius * Mr / pow(_altitudeCurrent, 2);  // this is tyring to get change gravity based on radius from center of earth
  // Fd = .5 V^2 drag, drag = (rho Cd A)
  float dragSign = (_velocity < 0) ? 1.0 : -1.0;
  // Serial.print(F("dragSign: "));
  // Serial.println(dragSign);
  _forceDrag = 0.5 * pow(_velocity, 2) * drag * dragSign;
  // Serial.print(F("_forceDrag: "));
  // Serial.println(_forceDrag);

  // F = Ft-Fd-M*g is the sum of thrust, drag, and weight
  // float F = Ft - Fd - (Mr * GravConstant);
  _forceGravity = (Mr * GravConstant);
  // Serial.print(F("_forceGravity: "));
  // Serial.println(_forceGravity);

  _forceTotal = Ft + _forceDrag - _forceGravity;
  // Serial.print(F("_forceGravity: "));
  // Serial.println(_forceGravity);

  float deltaF = deltaT / 1000.0 / 1000.0;
  // Serial.print(F("deltaF: "));
  // Serial.println(deltaF);

  if (_status == simulationStatusLanded) {
    _acceleration = 0;
    _velocity = 0;
    return;
  }

  // Apply acceleration
  _acceleration = _forceTotal / Mr;
    // Serial.print(F("_acceleration: "));
    // Serial.println(_acceleration);

  // _velocity += deltaT * acceleration;
  _velocity += deltaF * _acceleration;
    // Serial.print(F("_velocity: "));
    // Serial.println(_velocity);

  // Move the position
  _altitudeCurrent += deltaF * _velocity;
    // Serial.print(F("_altitudeCurrent: "));
    // Serial.println(_altitudeCurrent);
}

void simulation::loopStep(unsigned long deltaT, bool output, bool outputHeader) {
  // Altitude is the flight altitude minus starting altitude.
  // float altitudeFlight = _altitudeCurrent - _altitudeInitial;
  float altitudeFlight = _altitudeCurrent;
  float airDensity = AirDensity * pow(0.5, altitudeFlight / AirDensityScale);

  float mass = _config.mass;
  float thrust = 0;
  bool burnout = (_elapsedTime >= _burnoutTime);
  if (!burnout) {
    mass = _config.mass + _config.motorFuelMass - _config.motorFuelBurnRateMicro * _elapsedTime;
    thrust = _motorThrust; // N  /// TODO: use a thrust curve?
  }

  // Fd = .5 V^2 rho Cd A (only rho Cd A implemented here)
  // rho = air density
  // Cd = drag coefficient
  // A = Frontal Area
  float drag = airDensity * _config.frontalArea * _config.cd;
  if (_airborneApogee)
    // calculate parachute drag...
    drag = airDensity * _config.parachuteArea * _config.parachuteCd;

  evaluateTimestep(deltaT, drag, mass, thrust);

  // if (output) {
    if (outputHeader)
      outputPrintHeader();
    outputPrint(deltaT, mass, thrust, altitudeFlight, airDensity, drag, burnout, 0);
  // }

  // probably should be a state machine...
  if (_status == simulationStatusGround) {
    if (altitudeFlight > 0)
      _status = simulationStatusAirborneAscent;
  }
  else if (_status == simulationStatusAirborneAscent) {
    float altitudeFlightDelta = altitudeFlight - _altitudeFlightLast;
    // Detect apogee by taking X number of measures as long as the current is less
    // than the last recorded altitude.
#ifdef DEBUG_SIM
    Serial.print(F("loopStep...altitudeFlight: "));
    Serial.print(altitudeFlight);
    Serial.print(F(", altitudeLast: "));
    Serial.print(_altitudeFlightLast);
    Serial.print(F(", altitudeFlightDelta: "));
    Serial.println(altitudeFlightDelta);
#endif

    // check to see if we've hit apogee...
    if (altitudeFlightDelta < 0) {
      _altitudeApogeeMeasures = _altitudeApogeeMeasures - 1;
      if (_altitudeApogeeMeasures == 0) {
#ifdef DEBUG_SIM
        Serial.println(F("loopStep...detected apogee"));
#endif
        // Detected apogee.
        _altitudeApogee = altitudeFlight;
        _airborneApogee = true;
        _status = simulationStatusAirborneDescent;
      }
    } 
    else {
      if (_altitudeApogeeMeasures < SAMPLE_MEASURES_APOGEE) {
#ifdef DEBUG_SIM
        Serial.println(F("loopStep...measures - reset"));
#endif
        // If the curent is greater than the last, then reset as it was potentially a false positive.
        _altitudeFlightLast = altitudeFlight;
        _altitudeApogeeMeasures = SAMPLE_MEASURES_APOGEE;
      }
    }
  }
  else if (_status == simulationStatusAirborneDescent) {
    // if airborne, its passed apogee, and the velocity is equal to zero or less than zero...
#ifdef DEBUG_SIM
    Serial.print(F("loopStep...altitudeFlight: "));
    Serial.print(altitudeFlight);
#endif
    if (altitudeFlight <= 0) {
      // then we've landeded...
      _acceleration = 0;
      _velocity = 0;

      outputPrint(deltaT, mass, 0, altitudeFlight, airDensity, 0, true, 0);

  #ifdef DEBUG_SIM
      Serial.println(F("sim - LANDED"));
      Serial.print(F("sim -  Max. Height: "));
      Serial.println(_maxAltitude);
      Serial.print(F("sim -  Max. Velocity: "));
      Serial.println(_maxVelocity);
      Serial.print(F("sim -  Settle Final: "));
      Serial.print(_settleFinal);
      Serial.print(F(" < "));
      Serial.println(SettleFinal);
  #endif

      if (_settleFinal < SettleFinal) {
        _settleFinal++;
        return;
      }

      _status = simulationStatusLanded;
      stop();
      return;
    }
  }

  _altitudeFlightLast = altitudeFlight;
  if (altitudeFlight > _maxAltitude)
    _maxAltitude = altitudeFlight;
  if (_velocity > _maxVelocity)
    _maxVelocity = _velocity;

  _elapsedTime += deltaT;
}

void simulation::outputPrint(unsigned long delta, float mass, float thrust, float altitude, float airDensity, float drag, bool burnout, float apogeeDelta) {
  Serial.print("sim -  _elapsedTime: ");
  Serial.println(_elapsedTime);
  Serial.print("sim -  altitude: ");
  Serial.println(altitude);
  Serial.print("sim -  thrust: ");
  Serial.println(thrust);

  // char temp[50];
  // char formatFloat[5] = "%.4f";
  // char formatInt[16] = "%d";
  // Serial.print(F("sim -  "));

  // sprintf(temp, formatInt, _elapsedTime);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 16));

  // sprintf(temp, formatInt, delta);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 11));

  // const char* resultsB = burnout ? "true" : "false";
  // Serial.print(resultsB);
  // Serial.print(stringPad(resultsB, 10));

  // sprintf(temp, formatInt, _burnoutTime);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 11));

  // const char* resultsA = _status == simulationStatusAirborneAscent ? "Ascent" : _status == simulationStatusAirborneDescent ? "Descent" : _status == simulationStatusLanded ? "Landed" : "Ground";
  // Serial.print(resultsA);
  // Serial.print(stringPad(resultsA, 10));

  // sprintf(temp, formatFloat, _config.mass);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 11));

  // sprintf(temp, formatFloat, _config.mass + _config.motorFuelMass);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 10));

  // sprintf(temp, formatFloat, mass);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 12));

  // sprintf(temp, formatFloat, thrust);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 13));

  // sprintf(temp, formatFloat, _forceDrag);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 13));

  // sprintf(temp, formatFloat, _forceGravity);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 13));

  // sprintf(temp, formatFloat, _forceTotal);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 13));

  // sprintf(temp, formatFloat, _acceleration); // Acceleration
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 15));

  // sprintf(temp, formatFloat, _velocity); // Velocity
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 14));

  // sprintf(temp, formatFloat, altitude);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 14));

  // sprintf(temp, formatFloat, _altitudeInitial);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 14));

  // sprintf(temp, formatFloat, airDensity);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 14));

  // sprintf(temp, formatFloat, drag);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 10));

  // sprintf(temp, formatFloat, _config.frontalArea);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 16));

  // sprintf(temp, formatFloat, _config.cd);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 10));

  // sprintf(temp, formatFloat, _config.parachuteArea);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 16));

  // sprintf(temp, formatFloat, _config.parachuteCd);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 10));

  // sprintf(temp, "%.2f", _altitudeApogeeMeasures);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 11));

  // sprintf(temp, formatFloat, apogeeDelta);
  // Serial.print(temp);
  // Serial.print(stringPad(temp, 14));

  // Serial.println(_airborneApogee ? "true" : "false");
}

void simulation::outputPrintHeader() {
  // Serial.println(F("sim -                           Burnout                     Mass                          Force                                                                      Altitude                                        Rocket                  Parachute               Apogee"));
  // Serial.println(F("sim -  Time           Delta     Burnout  Time      Status   Rocket    Total    Current    Thrust      Drag        Gravity     Total       Acceleration  Velocity     Flight       Initial      Air Density  Drag     Cross Section  Cd       Cross Section  Cd       Measures  Delta        Apogee"));
  // Serial.println(F("sim -                           ----------------            ----------------------------  -----------------------------------------------                            -------------------------                       ----------------------- ----------------------- -----------------------------"));
}

void simulation::outputSerialList() {
  Serial.println(F("\nOutput serial list of sim configs."));

//   JsonDocument doc;
//   deserializeJson(doc, "[]");
  JsonArray configs = _configs.to<JsonArray>();
//   _fileSystem.instance.loadConfigSim(configs);
#if defined(DEBUG_SIM_CONFIG)
  serializeJson(configs, Serial);
#endif
  if (!configs || configs.size() <= 0) {
    Serial.println(F("\tFailed to load configuration."));
    return;
  }
#if defined(DEBUG_SIM_CONFIG)
  Serial.println(F("\nOutput serial list of sim configs loaded."));
  serializeJson(configs, Serial);
  Serial.println();
#endif

  char temp[20];
  char formatFloat[5] = "%.4f";
  Serial.println(F("Number Name                  RocketMassOz  MotorFuelBurnTimeS  MotorFuelMassEmptyOz  MotorFuelMassLaunchOz  MotorThrustN  DiameterMM  DragCoefficient"));
  for (JsonObject obj : configs) {
    int tempN = obj["number"];
    Serial.print(tempN);
    Serial.print(stringPad(tempN, 9));

    String name = obj["name"];
    Serial.print(name.c_str());
    Serial.print(stringPad(name.c_str(), 23));

    float value = obj["RocketMassOz"];
    sprintf(temp, formatFloat, value);
    Serial.print(temp);
    Serial.print(stringPad(temp, 15));

    value = obj["MotorFuelBurnTimeS"];
    sprintf(temp, formatFloat, value);
    Serial.print(temp);
    Serial.print(stringPad(temp, 21));

    value = obj["MotorFuelMassEmptyOz"];
    sprintf(temp, formatFloat, value);
    Serial.print(temp);
    Serial.print(stringPad(temp, 23));

    value = obj["MotorFuelMassLaunchOz"];
    sprintf(temp, formatFloat, value);
    Serial.print(temp);
    Serial.print(stringPad(temp, 24));

    value = obj["MotorThrustN"];
    sprintf(temp, formatFloat, value);
    Serial.print(temp);
    Serial.print(stringPad(temp, 15));

    value = obj["DiameterMM"];
    sprintf(temp, formatFloat, value);
    Serial.print(temp);
    Serial.print(stringPad(temp, 13));

    value = obj["DragCoefficient"];
    sprintf(temp, formatFloat, value);
    Serial.println(temp);
  }

  Serial.println(F("...completed"));
}

accelerometerValues simulation::readAcceleration() {
  accelerometerValues values;
  if (!_running)
    return values;

  values.x = 0;
  values.y = 0;
  values.z = _acceleration;

  return values;
}

float simulation::readAltitude() {
  if (!_running)
    return 0;

#if defined(DEBUG_SIM) || defined(DEBUG_SIM_OUTPUT)
  debug("simulation.altitude", _altitude);
#endif
  return _altitudeCurrent;
}

atmosphereValues simulation::readAtmosphere() {
  atmosphereValues values;
  if (!_running)
    return values;

  values.altitude = _altitudeCurrent;
  values.humidity = 0;
  values.pressure = 0;
  values.temperature = 0;

  return values;
}

gyroscopeValues simulation::readGyroscope() {
  gyroscopeValues values;
  if (!_running)
    return values;

  values.x = 0;
  values.y = 0;
  values.z = 0;

  return values;
}

magnetometerValues simulation::readMagnetometer() {
  magnetometerValues values;
  if (!_running)
    return values;

  values.x = 0;
  values.y = 0;
  values.z = 0;

  return values;
}

void simulation::simulationTask() {
  if (!_running)
    return;

  bool output = false;
  bool outputHeader = false;

  unsigned long currentTimestamp = micros();
  // debug(F("Simulation currentTimestamp..."), currentTimestamp);
  // debug(F("Simulation _simulationTimestamp...", _simulationTimestamp);
  unsigned long deltaElapsed = currentTimestamp - _simulationTimestamp;
  // debug(F("Simulation deltaElapsed..."), deltaElapsed);

  unsigned long delta = _simulationThrottle.determine('s', deltaElapsed, _config.sampleRate);
  // debug(F("Simulation delta..."), delta);
  if (delta != 0) {
    // let the loop settle before starting to simulate...
    if (_settle < SettleStart) {
      // debug(F("Simulation settle..."), _settle);
      _settle++;
      return;
    }

    //if (count % 25 == 0) {
    if (_count % 1 == 0) {
      _count = 0;
      output = true;
      if (_countHeader % 10 == 0) {
        _countHeader = 0;
        _countHeader++;
        outputHeader = true;
      }
      _countHeader++;
    }
    _count++;

    // debug(F("Simulation, delta"), delta);
    loopStep(delta, output, outputHeader);
  }

  _simulationTimestamp = currentTimestamp;
}

void simulation::simulationTaskEnd() {
  unsigned long stop = micros();
  unsigned long runtime = stop - _start;
  Serial.print(F("sim -\tStart="));
  Serial.println(_start);
  Serial.print(F("sim -\tStop="));
  Serial.println(stop);
  Serial.print(F("sim -\tRuntime (us)="));
  Serial.println(runtime);
  Serial.print(F("sim -\tRuntime (ms)="));
  Serial.println(runtime / 1000);
  Serial.print(F("sim -\tRuntime (s)="));
  Serial.println(runtime / 1000 / 1000);
}

void simulation::simulationTaskStart() {
  Serial.println(F("Simulation task..."));
  Serial.print(F("sim -  Sample Rate="));
  Serial.println(_config.sampleRate);

  _start = _simulationTimestamp = micros();
}

#if defined(EPS32)
void simulation::simulationTaskWrapper() {
  Serial.println(F("Simulation task..."));
  Serial.print(F("sim -  Sample Rate="));
  Serial.println(_config.sampleRate);

  simulationTaskStart();
  while(_running)
    simulationTask();
  simulationTaskEnd();
}
#endif

int8_t simulation::setup(JsonDocument configs) {
  Serial.println(F("Setup simulation...."));
  _configs = configs;
  Serial.println(F("... setup simulation configs..."));
  serializeJson(_configs, Serial);
  Serial.println();
  Serial.println(F("... setup simulation completed."));
  Serial.println();
  return 0;
}

void simulation::start(int requestedNumber, float altitudeInitial, float altitudeFinal) {
  Serial.println();
  Serial.println(F("Simulation Started"));

  if (_running) {
    Serial.println(F("\tAlready running."));
    return;
  }
  
//   JsonDocument doc;
  Serial.println(F("...Simulation config..."));
  JsonArray configs = _configs.as<JsonArray>();
//   _fileSystem.instance.loadConfigSim(configs);
#if defined(DEBUG_SIM_CONFIG)
  Serial.println(F("...Simulation config as array..."));
  serializeJson(configs, Serial);
  Serial.println();
#endif
  if (configs.size() <= 0) {
    Serial.println(F("\n\tFailed to load configuration."));
    return;
  }
  Serial.println(F("\tSuccessfully loaded configurations."));

  JsonObject config;
  for (JsonObject obj : configs) {
    int temp = obj["number"];
    if (temp == requestedNumber) {
      config = obj;
      break;
    }
  }
  if (!config) {
    Serial.print(F("\tFailed to find config for requested simulation #"));
    Serial.print(requestedNumber);
    Serial.println(F("."));
    return;
  }
#if defined(DEBUG_SIM_CONFIG)
  serializeJson(config, Serial);
  Serial.println();
#endif

  struct simulationConfigStruct startConfig;
  // startConfig.diameterIn = config["diameterIn"]; // in
  // startConfig.diameterMM = config["diameterMM"]; // mm
  // if (startConfig.diameterIn > 0)
  //   startConfig.diameter = startConfig.diameterIn * 0.0254;
  // else if (startConfig.diameterMM > 0)
  //   startConfig.diameter = startConfig.diameterMM / 1000;
  // startConfig.cd = config["cd"];
  // // A = 1/4 pi * D^2
  // startConfig.frontalArea = 0.25 * M_PI * pow(startConfig.diameter, 2);
  // startConfig.mass = ((float)config["massOz"]) / 35.274; // kg
  // startConfig.motorFuelBurnTime = config["motorFuelBurnTimeS"]; // s
  // startConfig.motorFuelBurnRate = startConfig.motorFuelMass / startConfig.motorFuelBurnTime;
  // startConfig.MotorThrust = config["motorThrustN"]; // N
  // startConfig.parachuteDiameterIn = config["parachuteDiameterIn"]; // in
  // startConfig.parachuteDiameterMM = config["parachuteDiameterMM"]; // mm
  // startConfig.parachuteDiameter = 0; // m
  // if (startConfig.parachuteDiameterIn > 0)
  //   startConfig.parachuteDiameter = startConfig.parachuteDiameterIn * 0.0254;
  // else if (startConfig.parachuteDiameterMM > 0)
  //   startConfig.parachuteDiameter = startConfig.parachuteDiameterMM / 1000;
  // startConfig.parachuteCd = config["parachuteCd"];
  // // A = 1/4 pi * D^2
  // startConfig.parachuteArea = 0.25 * M_PI * pow(startConfig.parachuteDiameter, 2);

  startConfig.motorThrust = 161; // N
  startConfig.diameterIn = 5.5; // in
  startConfig.diameterMM = 0; // mm
  if (startConfig.diameterIn > 0)
    startConfig.diameter = startConfig.diameterIn * 0.0254;
  else if (startConfig.diameterMM > 0)
    startConfig.diameter = startConfig.diameterMM / 1000;
  // A = 1/4 pi * D^2
  startConfig.frontalArea = 0.25 * M_PI * pow(startConfig.diameter, 2);
  startConfig.cd = 0.75;
  startConfig.mass = 2.014; // kg
  startConfig.motorFuelBurnTime = 2.21; // s
  startConfig.motorFuelMass = 0.19; // kg
  startConfig.motorFuelBurnRate = startConfig.motorFuelMass / startConfig.motorFuelBurnTime; // kg/s
  startConfig.motorFuelBurnRateMicro = startConfig.motorFuelBurnRate / 1000 / 1000; // convert to microseconds
  startConfig.parachuteDiameter = 0; // m
  if (startConfig.parachuteDiameterIn > 0)
    startConfig.parachuteDiameter = startConfig.parachuteDiameterIn * 0.0254;
  else if (startConfig.parachuteDiameterMM > 0)
    startConfig.parachuteDiameter = startConfig.parachuteDiameterMM / 1000;
  // A = 1/4 pi * D^2
  startConfig.parachuteArea = 0.25 * M_PI * pow(startConfig.parachuteDiameter, 2);

  _config = startConfig;
  
  Serial.println();
  Serial.print("DiameterIn: ");
  Serial.println(startConfig.diameterIn, 5);
  Serial.print("DiameterMM: ");
  Serial.println(startConfig.diameterMM, 5);
  Serial.print("Diameter: ");
  Serial.println(startConfig.diameter, 5);
  Serial.print("DragCoefficient: ");
  Serial.println(startConfig.cd, 5);
  Serial.print("FrontalArea: ");
  Serial.println(startConfig.frontalArea, 5);
  Serial.print("Mass: ");
  Serial.println(startConfig.mass, 5);
  Serial.print("MotorFuelBurnTime: ");
  Serial.println(startConfig.motorFuelBurnTime, 5);
  Serial.print("MotorFuelMass: ");
  Serial.println(startConfig.motorFuelMass, 5);
  Serial.print("MotorFuelBurnRate: ");
  Serial.println(startConfig.motorFuelBurnRate, 5);
  Serial.print("MotorThrust: ");
  Serial.println(startConfig.motorThrust, 5);
  Serial.print("ParachuteDiameterIn: ");
  Serial.println(startConfig.parachuteDiameterIn, 5);
  Serial.print("ParachuteDiameterMM: ");
  Serial.println(startConfig.parachuteDiameterMM, 5);
  Serial.print("ParachuteDiameter: ");
  Serial.println(startConfig.parachuteDiameter, 5);
  Serial.print("ParachuteCd: ");
  Serial.println(startConfig.parachuteCd, 5);
  Serial.println();

  _status = simulationStatusGround;
  _acceleration = 0.0; // acceleration
  _airborneApogee = false;
  _altitudeApogee = -1;
  _altitudeApogeeMeasures = SAMPLE_MEASURES_APOGEE;
  _altitudeCurrent = altitudeInitial; // initial position
  _altitudeEnding = altitudeFinal;
  _altitudeInitial = altitudeInitial;
  _altitudeFlightLast = 0;
  _burnoutTime = _config.motorFuelBurnTime * 1000 * 1000;
  _count = 0;
  _countHeader = 0;
  _elapsedTime = 0;
  _maxAltitude = 0;
  _maxVelocity = 0;
  _motorThrust = _config.motorThrust; // N
  _settle = 0;
  _settleFinal = 0;
  _velocity = 0.0; // velocity

  Serial.print("altitudeInitial: ");
  Serial.println(altitudeInitial, 5);
  Serial.print("_altitudeCurrent: ");
  Serial.println(_altitudeCurrent, 5);
  Serial.print("_altitudeInitial: ");
  Serial.println(_altitudeInitial, 5);
  Serial.print("_altitudeEnding: ");
  Serial.println(_altitudeEnding, 5);
  Serial.println();
  
  _running = true;

  simulationTaskStart();

  // Serial.println(F("sim -\tTime\tDelta\tThrust\tMass\tVelocity\tStarting Altitude\tPosition\tAltitude\tAirborne"));
}

void simulation::stop() {
  if (_running) {
    Serial.println(F("Simulation\tStopped."));
    Serial.println();
    _running = false;

    simulationTaskEnd();
    return;
  }
  Serial.println(F("Simulation\tNo simulation was running."));
  Serial.println();
}

simulation _simulation;

int8_t setupSimulation(JsonDocument configs) {
  serializeJson(configs, Serial);
  Serial.println();
    return _simulation.setup(configs);
}