#include <Arduino.h>

#include "communicationMAVLinkAltimeter.h"
#include <sensorUtilities.h>

void CommunicationMAVLinkAltimeter::init(CommunicationMAVLinkHandlerCommandShortFunctionPtr func) {
    _handlerCommandShort = func;
}

void CommunicationMAVLinkAltimeter::init(CommunicationMAVLinkHandlerCommandIntFunctionPtr funcInt, CommunicationMAVLinkHandlerCommandShortFunctionPtr funcShort) {
    CommunicationMAVLink::init(funcInt);
    _handlerCommandShort = funcShort;
}

void CommunicationMAVLinkAltimeter::sendGPSFiltered(uint64_t time_usec, int32_t lat, int32_t lon, int32_t alt, int32_t alt_ellipsoid) {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

#ifdef DEBUG_COMMUNICATION_MAVLINK
    Serial.println(F("communication-mavlink-gpsf..."));
#endif

    mavlink_message_t message;
    mavlink_msg_global_position_int_pack(getSystemId(), COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, time_usec, lat, lon, alt, alt_ellipsoid, 0, 0, 0, 0);

    _write(&message);
}

void CommunicationMAVLinkAltimeter::sendGPSRaw(uint64_t time_usec, int32_t lat, int32_t lon, int32_t alt, int32_t alt_ellipsoid, uint16_t eph, uint16_t epv, uint16_t vel, uint16_t cog, uint8_t satellites_visible, uint8_t fix_type) {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

#ifdef DEBUG_COMMUNICATION_MAVLINK
    Serial.println(F("communication-mavlink-gpsr..."));
#endif

    mavlink_message_t message;
    mavlink_msg_gps_raw_int_pack(getSystemId(), COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, time_usec, fix_type, lat, lon, alt, eph, epv, UINT16_MAX, cog, satellites_visible, alt_ellipsoid, 0, 0, 0, 0, 0);
    // mavlink_msg_test_pack(getSystemId(), COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, time_usec, fix_type, lat, lon, alt, eph, epv, UINT16_MAX, cog, satellites_visible, alt_ellipsoid, 0, 0, 0, 0, 0);

    _write(&message);
}

void CommunicationMAVLinkAltimeter::sendIMU(uint64_t time_usec, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag) {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

#ifdef DEBUG_COMMUNICATION_MAVLINK
    Serial.println(F("communication-mavlink-imu..."));
#endif

    mavlink_message_t message;
    mavlink_msg_raw_imu_pack(getSystemId(), COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, time_usec, xacc, yacc, zacc, xgyro, ygyro, zgyro, xmag, ymag, zmag, 0, 0);
    
    _write(&message);
}

void CommunicationMAVLinkAltimeter::sendSensors(uint64_t time_usec, sensorValuesStruct sensorData) {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

#ifdef DEBUG_COMMUNICATION_MAVLINK
    Serial.println(F("communication-mavlink-sensor..."));
#endif

    mavlink_message_t message;
    mavlink_msg_combined_sensors_pack(getSystemId(), COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, time_usec, 
        convertAcc(sensorData.acceleration.x), convertAcc(sensorData.acceleration.y), convertAcc(sensorData.acceleration.z), 
        convertGyro(sensorData.gyroscope.x), convertGyro(sensorData.gyroscope.y), convertGyro(sensorData.gyroscope.z), 
        convertMagnetometer(sensorData.magnetometer.x), convertMagnetometer(sensorData.magnetometer.y), convertMagnetometer(sensorData.magnetometer.z), 
        convertAtmosphere(sensorData.atmosphere.humidity), convertAtmosphere(sensorData.atmosphere.pressure), convertAtmosphere(sensorData.atmosphere.temperature), 
        convertAltitude(sensorData.atmosphere.altitude), 
        0, 0, 0);
    
    _write(&message);
}

void CommunicationMAVLinkAltimeter::sendSensorsBarometerAltitude(uint64_t time_usec, sensorValuesStruct sensorData) {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

#ifdef DEBUG_COMMUNICATION_MAVLINK
    Serial.println(F("communication-mavlink-sensor-barometer..."));
#endif

    mavlink_message_t message;
    mavlink_msg_barometer_altitude_pack(getSystemId(), COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, time_usec, 
        convertAtmosphere(sensorData.atmosphere.humidity), convertAtmosphere(sensorData.atmosphere.pressure), convertAtmosphere(sensorData.atmosphere.temperature),
        convertAltitude(sensorData.atmosphere.altitude)
    );
    
    _write(&message);
}

bool CommunicationMAVLinkAltimeter::_handleMessage(const mavlink_message_t* message) {
    if (message == nullptr)
        return false;

    if (message->msgid == MAVLINK_MSG_ID_COMMAND_INT) {
        _handleCommandShort(message);
        return true;
    }

    return false;
}

void CommunicationMAVLinkAltimeter::_handleCommandShort(const mavlink_message_t* message) {
    mavlink_command_short_t msgshort;
    mavlink_msg_command_short_decode(message, &msgshort);

    Serial.println(F("communication-mavlink-command-short-received..."));
    Serial.print(F("communication-mavlink-command-short-received..._handlerCommandShort: "));
    Serial.println((_handlerCommandShort != nullptr));

        Serial.print(F("mavlink!!!! command "));
        Serial.println(msgshort.command);
        Serial.println(msgshort.param1);
        Serial.println(msgshort.param2);
        Serial.println(msgshort.param3);

    mavlink_message_t message_ack;
    mavlink_msg_command_ack_pack(getSystemId(), COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message_ack, 
        msgshort.command, 1, 1, 0, msgshort.target_system, msgshort.target_component);

    _write(&message_ack);
  
    if (_handlerCommandShort != nullptr)
        _handlerCommandShort(&msgshort);
}
