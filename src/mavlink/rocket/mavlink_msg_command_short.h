#pragma once
// MESSAGE COMMAND_SHORT PACKING

#define MAVLINK_MSG_ID_COMMAND_SHORT 15002


typedef struct __mavlink_command_short_t {
 int32_t param1; /*<  */
 float param2; /*<  */
 uint16_t command; /*<  The scheduled action for the mission item.*/
 uint8_t target_system; /*<  System ID*/
 uint8_t target_component; /*<  Component ID*/
 uint8_t confirmation; /*<  0: First transmission of this command. 1-255: Confirmation transmissions (e.g. for kill command)*/
 char param3[32]; /*<  */
} mavlink_command_short_t;

#define MAVLINK_MSG_ID_COMMAND_SHORT_LEN 45
#define MAVLINK_MSG_ID_COMMAND_SHORT_MIN_LEN 45
#define MAVLINK_MSG_ID_15002_LEN 45
#define MAVLINK_MSG_ID_15002_MIN_LEN 45

#define MAVLINK_MSG_ID_COMMAND_SHORT_CRC 158
#define MAVLINK_MSG_ID_15002_CRC 158

#define MAVLINK_MSG_COMMAND_SHORT_FIELD_PARAM3_LEN 32

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_COMMAND_SHORT { \
    15002, \
    "COMMAND_SHORT", \
    7, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_command_short_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 11, offsetof(mavlink_command_short_t, target_component) }, \
         { "command", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_command_short_t, command) }, \
         { "confirmation", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_command_short_t, confirmation) }, \
         { "param1", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_command_short_t, param1) }, \
         { "param2", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_command_short_t, param2) }, \
         { "param3", NULL, MAVLINK_TYPE_CHAR, 32, 13, offsetof(mavlink_command_short_t, param3) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_COMMAND_SHORT { \
    "COMMAND_SHORT", \
    7, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_command_short_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 11, offsetof(mavlink_command_short_t, target_component) }, \
         { "command", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_command_short_t, command) }, \
         { "confirmation", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_command_short_t, confirmation) }, \
         { "param1", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_command_short_t, param1) }, \
         { "param2", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_command_short_t, param2) }, \
         { "param3", NULL, MAVLINK_TYPE_CHAR, 32, 13, offsetof(mavlink_command_short_t, param3) }, \
         } \
}
#endif

/**
 * @brief Pack a command_short message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param command  The scheduled action for the mission item.
 * @param confirmation  0: First transmission of this command. 1-255: Confirmation transmissions (e.g. for kill command)
 * @param param1  
 * @param param2  
 * @param param3  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_command_short_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint16_t command, uint8_t confirmation, int32_t param1, float param2, const char *param3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMMAND_SHORT_LEN];
    _mav_put_int32_t(buf, 0, param1);
    _mav_put_float(buf, 4, param2);
    _mav_put_uint16_t(buf, 8, command);
    _mav_put_uint8_t(buf, 10, target_system);
    _mav_put_uint8_t(buf, 11, target_component);
    _mav_put_uint8_t(buf, 12, confirmation);
    _mav_put_char_array(buf, 13, param3, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMMAND_SHORT_LEN);
#else
    mavlink_command_short_t packet;
    packet.param1 = param1;
    packet.param2 = param2;
    packet.command = command;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.confirmation = confirmation;
    mav_array_assign_char(packet.param3, param3, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COMMAND_SHORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COMMAND_SHORT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_COMMAND_SHORT_MIN_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_CRC);
}

/**
 * @brief Pack a command_short message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param command  The scheduled action for the mission item.
 * @param confirmation  0: First transmission of this command. 1-255: Confirmation transmissions (e.g. for kill command)
 * @param param1  
 * @param param2  
 * @param param3  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_command_short_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint16_t command, uint8_t confirmation, int32_t param1, float param2, const char *param3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMMAND_SHORT_LEN];
    _mav_put_int32_t(buf, 0, param1);
    _mav_put_float(buf, 4, param2);
    _mav_put_uint16_t(buf, 8, command);
    _mav_put_uint8_t(buf, 10, target_system);
    _mav_put_uint8_t(buf, 11, target_component);
    _mav_put_uint8_t(buf, 12, confirmation);
    _mav_put_char_array(buf, 13, param3, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMMAND_SHORT_LEN);
#else
    mavlink_command_short_t packet;
    packet.param1 = param1;
    packet.param2 = param2;
    packet.command = command;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.confirmation = confirmation;
    mav_array_memcpy(packet.param3, param3, sizeof(char)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COMMAND_SHORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COMMAND_SHORT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_COMMAND_SHORT_MIN_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_COMMAND_SHORT_MIN_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_LEN);
#endif
}

/**
 * @brief Pack a command_short message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param command  The scheduled action for the mission item.
 * @param confirmation  0: First transmission of this command. 1-255: Confirmation transmissions (e.g. for kill command)
 * @param param1  
 * @param param2  
 * @param param3  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_command_short_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint16_t command,uint8_t confirmation,int32_t param1,float param2,const char *param3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMMAND_SHORT_LEN];
    _mav_put_int32_t(buf, 0, param1);
    _mav_put_float(buf, 4, param2);
    _mav_put_uint16_t(buf, 8, command);
    _mav_put_uint8_t(buf, 10, target_system);
    _mav_put_uint8_t(buf, 11, target_component);
    _mav_put_uint8_t(buf, 12, confirmation);
    _mav_put_char_array(buf, 13, param3, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMMAND_SHORT_LEN);
#else
    mavlink_command_short_t packet;
    packet.param1 = param1;
    packet.param2 = param2;
    packet.command = command;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.confirmation = confirmation;
    mav_array_assign_char(packet.param3, param3, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COMMAND_SHORT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COMMAND_SHORT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_COMMAND_SHORT_MIN_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_CRC);
}

/**
 * @brief Encode a command_short struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param command_short C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_command_short_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_command_short_t* command_short)
{
    return mavlink_msg_command_short_pack(system_id, component_id, msg, command_short->target_system, command_short->target_component, command_short->command, command_short->confirmation, command_short->param1, command_short->param2, command_short->param3);
}

/**
 * @brief Encode a command_short struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param command_short C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_command_short_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_command_short_t* command_short)
{
    return mavlink_msg_command_short_pack_chan(system_id, component_id, chan, msg, command_short->target_system, command_short->target_component, command_short->command, command_short->confirmation, command_short->param1, command_short->param2, command_short->param3);
}

/**
 * @brief Encode a command_short struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param command_short C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_command_short_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_command_short_t* command_short)
{
    return mavlink_msg_command_short_pack_status(system_id, component_id, _status, msg,  command_short->target_system, command_short->target_component, command_short->command, command_short->confirmation, command_short->param1, command_short->param2, command_short->param3);
}

/**
 * @brief Send a command_short message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param command  The scheduled action for the mission item.
 * @param confirmation  0: First transmission of this command. 1-255: Confirmation transmissions (e.g. for kill command)
 * @param param1  
 * @param param2  
 * @param param3  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_command_short_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint16_t command, uint8_t confirmation, int32_t param1, float param2, const char *param3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMMAND_SHORT_LEN];
    _mav_put_int32_t(buf, 0, param1);
    _mav_put_float(buf, 4, param2);
    _mav_put_uint16_t(buf, 8, command);
    _mav_put_uint8_t(buf, 10, target_system);
    _mav_put_uint8_t(buf, 11, target_component);
    _mav_put_uint8_t(buf, 12, confirmation);
    _mav_put_char_array(buf, 13, param3, 32);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMMAND_SHORT, buf, MAVLINK_MSG_ID_COMMAND_SHORT_MIN_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_CRC);
#else
    mavlink_command_short_t packet;
    packet.param1 = param1;
    packet.param2 = param2;
    packet.command = command;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.confirmation = confirmation;
    mav_array_assign_char(packet.param3, param3, 32);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMMAND_SHORT, (const char *)&packet, MAVLINK_MSG_ID_COMMAND_SHORT_MIN_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_CRC);
#endif
}

/**
 * @brief Send a command_short message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_command_short_send_struct(mavlink_channel_t chan, const mavlink_command_short_t* command_short)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_command_short_send(chan, command_short->target_system, command_short->target_component, command_short->command, command_short->confirmation, command_short->param1, command_short->param2, command_short->param3);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMMAND_SHORT, (const char *)command_short, MAVLINK_MSG_ID_COMMAND_SHORT_MIN_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_CRC);
#endif
}

#if MAVLINK_MSG_ID_COMMAND_SHORT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_command_short_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint16_t command, uint8_t confirmation, int32_t param1, float param2, const char *param3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int32_t(buf, 0, param1);
    _mav_put_float(buf, 4, param2);
    _mav_put_uint16_t(buf, 8, command);
    _mav_put_uint8_t(buf, 10, target_system);
    _mav_put_uint8_t(buf, 11, target_component);
    _mav_put_uint8_t(buf, 12, confirmation);
    _mav_put_char_array(buf, 13, param3, 32);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMMAND_SHORT, buf, MAVLINK_MSG_ID_COMMAND_SHORT_MIN_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_CRC);
#else
    mavlink_command_short_t *packet = (mavlink_command_short_t *)msgbuf;
    packet->param1 = param1;
    packet->param2 = param2;
    packet->command = command;
    packet->target_system = target_system;
    packet->target_component = target_component;
    packet->confirmation = confirmation;
    mav_array_assign_char(packet->param3, param3, 32);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMMAND_SHORT, (const char *)packet, MAVLINK_MSG_ID_COMMAND_SHORT_MIN_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_LEN, MAVLINK_MSG_ID_COMMAND_SHORT_CRC);
#endif
}
#endif

#endif

// MESSAGE COMMAND_SHORT UNPACKING


/**
 * @brief Get field target_system from command_short message
 *
 * @return  System ID
 */
static inline uint8_t mavlink_msg_command_short_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field target_component from command_short message
 *
 * @return  Component ID
 */
static inline uint8_t mavlink_msg_command_short_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  11);
}

/**
 * @brief Get field command from command_short message
 *
 * @return  The scheduled action for the mission item.
 */
static inline uint16_t mavlink_msg_command_short_get_command(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field confirmation from command_short message
 *
 * @return  0: First transmission of this command. 1-255: Confirmation transmissions (e.g. for kill command)
 */
static inline uint8_t mavlink_msg_command_short_get_confirmation(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field param1 from command_short message
 *
 * @return  
 */
static inline int32_t mavlink_msg_command_short_get_param1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field param2 from command_short message
 *
 * @return  
 */
static inline float mavlink_msg_command_short_get_param2(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field param3 from command_short message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_command_short_get_param3(const mavlink_message_t* msg, char *param3)
{
    return _MAV_RETURN_char_array(msg, param3, 32,  13);
}

/**
 * @brief Decode a command_short message into a struct
 *
 * @param msg The message to decode
 * @param command_short C-struct to decode the message contents into
 */
static inline void mavlink_msg_command_short_decode(const mavlink_message_t* msg, mavlink_command_short_t* command_short)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    command_short->param1 = mavlink_msg_command_short_get_param1(msg);
    command_short->param2 = mavlink_msg_command_short_get_param2(msg);
    command_short->command = mavlink_msg_command_short_get_command(msg);
    command_short->target_system = mavlink_msg_command_short_get_target_system(msg);
    command_short->target_component = mavlink_msg_command_short_get_target_component(msg);
    command_short->confirmation = mavlink_msg_command_short_get_confirmation(msg);
    mavlink_msg_command_short_get_param3(msg, command_short->param3);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_COMMAND_SHORT_LEN? msg->len : MAVLINK_MSG_ID_COMMAND_SHORT_LEN;
        memset(command_short, 0, MAVLINK_MSG_ID_COMMAND_SHORT_LEN);
    memcpy(command_short, _MAV_PAYLOAD(msg), len);
#endif
}
