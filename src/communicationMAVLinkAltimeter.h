#ifndef _COMMUNICATION_MAVLINK_ALTIMETER_H
#define _COMMUNICATION_MAVLINK_ALTIMETER_H

#include <stdint.h>
#include <Arduino.h>

// #define DEBUG

#include <communicationMavlink.h>
#include <sensorData.h>

typedef void (*CommunicationMAVLinkHandlerCommandShortFunctionPtr)(const mavlink_command_short_t* message);

class CommunicationMAVLinkAltimeter: public CommunicationMAVLink {
  public:
    CommunicationMAVLinkAltimeter() {
    }
    
    void init(CommunicationMAVLinkHandlerCommandShortFunctionPtr func);
    void init(CommunicationMAVLinkHandlerCommandIntFunctionPtr funcInt, CommunicationMAVLinkHandlerCommandShortFunctionPtr funcShort);

    void sendGPSFiltered(uint64_t time_usec, int32_t lat, int32_t lon, int32_t alt, int32_t alt_ellipsoid);
    void sendGPSRaw(uint64_t time_usec, int32_t lat, int32_t lon, int32_t alt, int32_t alt_ellipsoid, uint16_t eph, uint16_t epv, uint16_t vel, uint16_t cog, uint8_t satellites_visible, uint8_t fix_type);
    void sendIMU(uint64_t time_usec, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag);
    void sendSensors(uint64_t time_usec, sensorValuesStruct sensorData);
    void sendSensorsBarometerAltitude(uint64_t time_usec, sensorValuesStruct sensorData);

  protected:
    bool _handleMessage(const mavlink_message_t* message) override;
    void _handleCommandShort(const mavlink_message_t* message);
    CommunicationMAVLinkHandlerCommandShortFunctionPtr _handlerCommandShort;
};

#endif