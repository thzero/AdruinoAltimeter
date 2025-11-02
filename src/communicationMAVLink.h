#ifndef _COMMUNICATION_MAVLINK_H
#define _COMMUNICATION_MAVLINK_H

#include <stdint.h>
#include <Arduino.h>
#include <limits.h>

// #define DEBUG

#include <communicationData.h>
#include <communicationRadio.h>

#include "mavlink/rocket/mavlink.h"

// #define DEBUG_COMMUNICATION_MAVLINK
// #define DEBUG_COMMUNICATION_MAVLINK_SEND

#define COMMUNICATION_MAVLINK_MODE_NONE 0
#define COMMUNICATION_MAVLINK_MODE_ARMED 1

#define COMMUNICATION_MAVLINK_SYSTEM_ID_MCU 255
#define COMMUNICATION_MAVLINK_COMPONENT_ID_NONE 0

typedef void (*CommunicationMAVLinkHandlerFunctionPtr)(unsigned long timestamp, unsigned long deltaElapsed, const mavlink_message_t* message);
typedef void (*CommunicationMAVLinkHandlerCommandIntFunctionPtr)(const mavlink_command_int_t* message);

class CommunicationMAVLink {
  public:
    CommunicationMAVLink() {
    }

    byte setup(CommunicationRadio* radio);
    uint8_t getMode();
    uint8_t getState();
    uint8_t getSystemId();
    void init(CommunicationMAVLinkHandlerCommandIntFunctionPtr func);
    int process(unsigned long timestamp, unsigned long delta);
    void read(CommunicationMAVLinkHandlerFunctionPtr func, unsigned long timestamp, unsigned long delta);
    void sendHeartbeat(uint8_t type, uint8_t state, uint8_t mode);
    void sendHeartbeatActive(uint8_t mode);
    void sendHeartbeatStandby();
    void setNetworkId(uint8_t id);

  protected:
    void _handleCommandInt(const mavlink_message_t* message);
    virtual bool _handleMessage(const mavlink_message_t* message);
    void _handleHeartbeat(const mavlink_message_t* message);
    void _write(mavlink_message_t* message);

    CommunicationRadio* _radio;
    CommunicationMAVLinkHandlerCommandIntFunctionPtr _handlerCommandInt;
    int _bufferIndex = 0;
    uint8_t _bufferSerialInbound[MAVLINK_MAX_PACKET_LEN];

    uint8_t _networkId = COMMUNICATION_MAVLINK_SYSTEM_ID_MCU;
    uint8_t _mode;
    uint8_t _state;
};

#endif