#include <Arduino.h>

#include "communicationMAVLink.h"
#include <sensorUtilities.h>

byte CommunicationMAVLink::setup(CommunicationRadio* radio) {
    if (radio == nullptr)
        return 1;

    _radio = radio;

    return 0;
}

uint8_t CommunicationMAVLink::getMode() {
    return _mode;
}

uint8_t CommunicationMAVLink::getState() {
    return _state;
}

int CommunicationMAVLink::process(unsigned long timestamp, unsigned long delta) {
  return 1;
}

void CommunicationMAVLink::read(CommunicationMAVLinkHandlerFunctionPtr func, unsigned long timestamp, unsigned long delta) {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

    if (_radio->available() == 0)
        return;

    if (_bufferIndex > MAVLINK_MAX_PACKET_LEN) {
        Serial.print(F("Failed, buffer exceeded length of "));
        Serial.println(MAVLINK_MAX_PACKET_LEN);
        memset(_bufferSerialInbound, 0, MAVLINK_MAX_PACKET_LEN);
        _bufferIndex = 0;
        return;
    }

    mavlink_message_t message;
    mavlink_status_t status;
    while (_radio->available() > 0) {
        if (_bufferIndex > MAVLINK_MAX_PACKET_LEN) {
            Serial.print(F("Failed, buffer exceeded length of "));
            Serial.println(MAVLINK_MAX_PACKET_LEN);
            memset(_bufferSerialInbound, 0, MAVLINK_MAX_PACKET_LEN);
            _bufferIndex = 0;
            return;
        }
        
        int readVal = _radio->read(); // Read the incoming byte
        _bufferSerialInbound[_bufferIndex++] = readVal;
        
        if (mavlink_parse_char(MAVLINK_COMM_0, readVal, &message, &status)) {
            Serial.print(F("mavlink!!!! "));
            Serial.println(_bufferIndex);
            for (int i = 0; i < _bufferIndex; i++)
                Serial.printf("%d ", _bufferSerialInbound[i]);
            Serial.println();
            memset(_bufferSerialInbound, 0, MAVLINK_MAX_PACKET_LEN);
            _bufferIndex = 0;

            if (message.msgid == MAVLINK_MSG_ID_HEARTBEAT)
                _handleHeartbeat(&message);

            if (func != nullptr)
                func(timestamp, delta, &message);

            return;
        }
    }

    return;
}

void CommunicationMAVLink::sendHeartbeat(uint8_t type, uint8_t state, uint8_t mode) {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

#ifdef DEBUG_COMMUNICATION
    Serial.println(F("communication-mavlink-heartbeat..."));
#endif

    mavlink_message_t message;
    mavlink_msg_heartbeat_pack(COMMUNICATION_MAVLINK_SYSTEM_ID_MCU, COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, 
        type, MAV_AUTOPILOT_INVALID, MAV_MODE_FLAG_CUSTOM_MODE_ENABLED, mode, state);

    _write(&message);
}

void CommunicationMAVLink::sendHeartbeatActive(uint8_t mode) {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

    sendHeartbeat(MAV_TYPE_ROCKET, MAV_STATE_ACTIVE, mode);
}

void CommunicationMAVLink::sendHeartbeatStandby() {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

    sendHeartbeat(MAV_TYPE_ROCKET, MAV_STATE_STANDBY, 0);
}

void CommunicationMAVLink::sendGPSFiltered(uint64_t time_usec, int32_t lat, int32_t lon, int32_t alt, int32_t alt_ellipsoid) {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

#ifdef DEBUG_COMMUNICATION
    Serial.println(F("communication-mavlink-gpsf..."));
#endif

    mavlink_message_t message;
    mavlink_msg_global_position_int_pack(COMMUNICATION_MAVLINK_SYSTEM_ID_MCU, COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, time_usec, lat, lon, alt, alt_ellipsoid, 0, 0, 0, 0);

    _write(&message);
}

void CommunicationMAVLink::sendGPSRaw(uint64_t time_usec, int32_t lat, int32_t lon, int32_t alt, int32_t alt_ellipsoid, uint16_t eph, uint16_t epv, uint16_t vel, uint16_t cog, uint8_t satellites_visible, uint8_t fix_type) {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

#ifdef DEBUG_COMMUNICATION
    Serial.println(F("communication-mavlink-gpsr..."));
#endif

    mavlink_message_t message;
    mavlink_msg_gps_raw_int_pack(COMMUNICATION_MAVLINK_SYSTEM_ID_MCU, COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, time_usec, fix_type, lat, lon, alt, eph, epv, UINT16_MAX, cog, satellites_visible, alt_ellipsoid, 0, 0, 0, 0, 0);
    // mavlink_msg_test_pack(COMMUNICATION_MAVLINK_SYSTEM_ID_MCU, COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, time_usec, fix_type, lat, lon, alt, eph, epv, UINT16_MAX, cog, satellites_visible, alt_ellipsoid, 0, 0, 0, 0, 0);

    _write(&message);
}

void CommunicationMAVLink::sendIMU(uint64_t time_usec, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag) {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

#ifdef DEBUG_COMMUNICATION
    Serial.println(F("communication-mavlink-imu..."));
#endif

    mavlink_message_t message;
    mavlink_msg_raw_imu_pack(COMMUNICATION_MAVLINK_SYSTEM_ID_MCU, COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, time_usec, xacc, yacc, zacc, xgyro, ygyro, zgyro, xmag, ymag, zmag, 0, 0);
    
    _write(&message);
}

void CommunicationMAVLink::sendSensors(uint64_t time_usec, sensorValuesStruct sensorData) {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

#ifdef DEBUG_COMMUNICATION
    Serial.println(F("communication-mavlink-sensor..."));
#endif

    mavlink_message_t message;
    mavlink_msg_combined_sensors_pack(COMMUNICATION_MAVLINK_SYSTEM_ID_MCU, COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, time_usec, 
        convertAcc(sensorData.acceleration.x), convertAcc(sensorData.acceleration.y), convertAcc(sensorData.acceleration.z), 
        convertGyro(sensorData.gyroscope.x), convertGyro(sensorData.gyroscope.y), convertGyro(sensorData.gyroscope.z), 
        convertMagnetometer(sensorData.magnetometer.x), convertMagnetometer(sensorData.magnetometer.y), convertMagnetometer(sensorData.magnetometer.z), 
        convertAtmosphere(sensorData.atmosphere.humidity), convertAtmosphere(sensorData.atmosphere.pressure), convertAtmosphere(sensorData.atmosphere.temperature), 
        convertAltitude(sensorData.atmosphere.altitude), 
        0, 0, 0);
    
    _write(&message);
}

void CommunicationMAVLink::sendSensorsBarometerAltitude(uint64_t time_usec, sensorValuesStruct sensorData) {
    if (_radio == nullptr) {
        Serial.println("Error: no radio.");
        return;
    }

#ifdef DEBUG_COMMUNICATION
    Serial.println(F("communication-mavlink-sensor-barometer..."));
#endif

    mavlink_message_t message;
    mavlink_msg_barometer_altitude_pack(COMMUNICATION_MAVLINK_SYSTEM_ID_MCU, COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, time_usec, 
        convertAtmosphere(sensorData.atmosphere.humidity), convertAtmosphere(sensorData.atmosphere.pressure), convertAtmosphere(sensorData.atmosphere.temperature),
        convertAltitude(sensorData.atmosphere.altitude)
    );
    
    _write(&message);
}

void CommunicationMAVLink::_handleHeartbeat(const mavlink_message_t* message) {
    mavlink_heartbeat_t hb;
    mavlink_msg_heartbeat_decode(message, &hb);

#ifdef DEBUG_COMMUNICATION
    Serial.println(F("communication-mavlink-heartbeat-received..."));
    Serial.print(F("MAV_STATE_STANDBY: ")); Serial.println(MAV_STATE_STANDBY);
    Serial.print(F("MAV_STATE_ACTIVE: ")); Serial.println(MAV_STATE_ACTIVE);
    Serial.print(F("State: ")); Serial.println(hb.system_status); // why state is status?! dunno
    Serial.print(F("MAV_MODE_FLAG_CUSTOM_MODE_ENABLED: ")); Serial.println(MAV_MODE_FLAG_CUSTOM_MODE_ENABLED);
    Serial.print(F("Base Mode: ")); Serial.println(hb.base_mode);
    Serial.print(F("Custom Mode: ")); Serial.println(hb.custom_mode); Serial.println(" ");
#endif
    _state = hb.system_status;
    _mode = hb.custom_mode;

    Serial.println(F("communication-mavlink-heartbeat-received: "));
    switch (hb.custom_mode) {
        case COMMUNICATION_MAVLINK_MODE_NONE:
            Serial.println(F("None"));
            break;
        default:
            Serial.println(F("Mode not known"));
            break;
    }
}

void CommunicationMAVLink::_write(mavlink_message_t* message) {
    if (_radio == nullptr) {
        Serial.println(F("Error: no radio."));
        return;
    }

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t length = mavlink_msg_to_send_buffer(buffer, message);

#if defined(DEBUG_COMMUNICATION) && defined(DEBUG_COMMUNICATION_SEND)
    // Serial.print(F("communication-mavlink-send: buffer length: "));
    // Serial.println(length);
    // Serial.println(F("communication-mavlink-send: message bytes to send: "));
    // for (size_t i = 0; i < length; i++)
    //     Serial.printf(F("%d "), buffer[i]);
    // Serial.println();
#endif
        
    _radio->writeBytes(buffer, length);
}
