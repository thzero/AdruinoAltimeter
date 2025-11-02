#include <Arduino.h>

#include "communicationMAVLink.h"

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

uint8_t CommunicationMAVLink::getSystemId() {
    return _networkId;
}

void CommunicationMAVLink::init(CommunicationMAVLinkHandlerCommandIntFunctionPtr func) {
    _handlerCommandInt = func;
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
    Serial.print(F("CommunicationMAVLink::read "));
    Serial.println(_radio->available());

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
            Serial.print(F("mavlink!!!! "));
            Serial.println(readVal);
        
        if (mavlink_parse_char(MAVLINK_COMM_0, readVal, &message, &status)) {
            Serial.print(F("mavlink!!!! "));
            Serial.println(_bufferIndex);
            for (int i = 0; i < _bufferIndex; i++)
                Serial.printf("%d ", _bufferSerialInbound[i]);
            Serial.println();
            memset(_bufferSerialInbound, 0, MAVLINK_MAX_PACKET_LEN);
            _bufferIndex = 0;

            Serial.print(F("mavlink!!!! "));
            Serial.println(message.msgid);

            if (message.msgid == MAVLINK_MSG_ID_HEARTBEAT)
                _handleHeartbeat(&message);

            if (message.msgid == MAVLINK_MSG_ID_COMMAND_INT)
                _handleCommandInt(&message);

            bool handled = _handleMessage(&message);
            if (handled)
                return;

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

#ifdef DEBUG_COMMUNICATION_MAVLINK
    Serial.println(F("communication-mavlink-heartbeat..."));
#endif

    mavlink_message_t message;
    mavlink_msg_heartbeat_pack(getSystemId(), COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message, 
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

void CommunicationMAVLink::setNetworkId(uint8_t id) {
    _networkId = id;
}

bool CommunicationMAVLink::_handleMessage(const mavlink_message_t* message) {
    return false;
}

void CommunicationMAVLink::_handleCommandInt(const mavlink_message_t* message) {
    mavlink_command_int_t msgInt;
    mavlink_msg_command_int_decode(message, &msgInt);

    Serial.println(F("communication-mavlink-command-int-received..."));
    Serial.print(F("communication-mavlink-command-int-received..._handlerCommandInt: "));
    Serial.println((_handlerCommandInt != nullptr));

    Serial.print(F("mavlink!!!! command "));
    Serial.println(msgInt.command);

    mavlink_message_t message_ack;
    mavlink_msg_command_ack_pack(getSystemId(), COMMUNICATION_MAVLINK_COMPONENT_ID_NONE, &message_ack, 
        msgInt.command, 1, 1, 0, msgInt.target_system, msgInt.target_component);

    _write(&message_ack);
  
    if (_handlerCommandInt != nullptr)
        _handlerCommandInt(&msgInt);
}

void CommunicationMAVLink::_handleHeartbeat(const mavlink_message_t* message) {
    mavlink_heartbeat_t hb;
    mavlink_msg_heartbeat_decode(message, &hb);

#ifdef DEBUG_COMMUNICATION_MAVLINK
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

#if defined(DEBUG_COMMUNICATION_MAVLINK) && defined(DEBUG_COMMUNICATION_MAVLINK_SEND)
    // Serial.print(F("communication-mavlink-send: buffer length: "));
    // Serial.println(length);
    // Serial.println(F("communication-mavlink-send: message bytes to send: "));
    // for (size_t i = 0; i < length; i++)
    //     Serial.printf(F("%d "), buffer[i]);
    // Serial.println();
#endif
        
    _radio->writeBytes(buffer, length);
}
