#ifndef _COMMUNICATION_MAVLINK_H
#define _COMMUNICATION_MAVLINK_H

#include <stdint.h>
#include <Arduino.h>
#include <limits.h>

// #define DEBUG

#include <communicationData.h>
#include <communicationRadio.h>
#include <sensorData.h>

#include "mavlink/rocket/mavlink.h"

// #define DEBUG_COMMUNICATION_MAVLINK
// #define DEBUG_COMMUNICATION_MAVLINK_SEND

#define COMMUNICATION_MAVLINK_MODE_NONE 0
#define COMMUNICATION_MAVLINK_MODE_ARMED 1

#define COMMUNICATION_MAVLINK_SYSTEM_ID_MCU 1
#define COMMUNICATION_MAVLINK_COMPONENT_ID_NONE 0

typedef void (*CommunicationMAVLinkHandlerFunctionPtr)(unsigned long timestamp, unsigned long deltaElapsed, const mavlink_message_t* message);
typedef void (*CommunicationMAVLinkHandlerCommandShortFunctionPtr)(const mavlink_command_short_t* message);

class CommunicationMAVLink {
  public:
    CommunicationMAVLink() {
    }

    byte setup(CommunicationRadio* radio);
    uint8_t getState();
    uint8_t getMode();
    void init(CommunicationMAVLinkHandlerCommandShortFunctionPtr func);
    int process(unsigned long timestamp, unsigned long delta);
    void read(CommunicationMAVLinkHandlerFunctionPtr func, unsigned long timestamp, unsigned long delta);
    void sendHeartbeat(uint8_t type, uint8_t state, uint8_t mode);
    void sendHeartbeatActive(uint8_t mode);
    void sendHeartbeatStandby();
    void sendGPSFiltered(uint64_t time_usec, int32_t lat, int32_t lon, int32_t alt, int32_t alt_ellipsoid);
    void sendGPSRaw(uint64_t time_usec, int32_t lat, int32_t lon, int32_t alt, int32_t alt_ellipsoid, uint16_t eph, uint16_t epv, uint16_t vel, uint16_t cog, uint8_t satellites_visible, uint8_t fix_type);
    void sendIMU(uint64_t time_usec, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag);
    void sendSensors(uint64_t time_usec, sensorValuesStruct sensorData);
    void sendSensorsBarometerAltitude(uint64_t time_usec, sensorValuesStruct sensorData);

  protected:
    void _handleCommandShort(const mavlink_message_t* message);
    void _handleHeartbeat(const mavlink_message_t* message);
    void _write(mavlink_message_t* message);

    CommunicationRadio* _radio;
    CommunicationMAVLinkHandlerCommandShortFunctionPtr _handlerCommandShort;
    int _bufferIndex = 0;
    uint8_t _bufferSerialInbound[MAVLINK_MAX_PACKET_LEN];

    uint8_t _mode;
    uint8_t _state;
};

#endif