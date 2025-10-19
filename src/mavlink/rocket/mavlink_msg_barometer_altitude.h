#pragma once
// MESSAGE BAROMETER_ALTITUDE PACKING

#define MAVLINK_MSG_ID_BAROMETER_ALTITUDE 15000


typedef struct __mavlink_barometer_altitude_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.*/
 int32_t altitude; /*< [m] */
 int16_t humidity; /*<  Humidity (filtered)*/
 int16_t pressure; /*<  Pressure (filtered)*/
 int16_t temperature; /*< [cdegC] Temperature (filtered)*/
} mavlink_barometer_altitude_t;

#define MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN 18
#define MAVLINK_MSG_ID_BAROMETER_ALTITUDE_MIN_LEN 18
#define MAVLINK_MSG_ID_15000_LEN 18
#define MAVLINK_MSG_ID_15000_MIN_LEN 18

#define MAVLINK_MSG_ID_BAROMETER_ALTITUDE_CRC 139
#define MAVLINK_MSG_ID_15000_CRC 139



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_BAROMETER_ALTITUDE { \
    15000, \
    "BAROMETER_ALTITUDE", \
    5, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_barometer_altitude_t, time_usec) }, \
         { "humidity", NULL, MAVLINK_TYPE_INT16_T, 0, 12, offsetof(mavlink_barometer_altitude_t, humidity) }, \
         { "pressure", NULL, MAVLINK_TYPE_INT16_T, 0, 14, offsetof(mavlink_barometer_altitude_t, pressure) }, \
         { "temperature", NULL, MAVLINK_TYPE_INT16_T, 0, 16, offsetof(mavlink_barometer_altitude_t, temperature) }, \
         { "altitude", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_barometer_altitude_t, altitude) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_BAROMETER_ALTITUDE { \
    "BAROMETER_ALTITUDE", \
    5, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_barometer_altitude_t, time_usec) }, \
         { "humidity", NULL, MAVLINK_TYPE_INT16_T, 0, 12, offsetof(mavlink_barometer_altitude_t, humidity) }, \
         { "pressure", NULL, MAVLINK_TYPE_INT16_T, 0, 14, offsetof(mavlink_barometer_altitude_t, pressure) }, \
         { "temperature", NULL, MAVLINK_TYPE_INT16_T, 0, 16, offsetof(mavlink_barometer_altitude_t, temperature) }, \
         { "altitude", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_barometer_altitude_t, altitude) }, \
         } \
}
#endif

/**
 * @brief Pack a barometer_altitude message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 * @param humidity  Humidity (filtered)
 * @param pressure  Pressure (filtered)
 * @param temperature [cdegC] Temperature (filtered)
 * @param altitude [m] 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_barometer_altitude_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, int16_t humidity, int16_t pressure, int16_t temperature, int32_t altitude)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, altitude);
    _mav_put_int16_t(buf, 12, humidity);
    _mav_put_int16_t(buf, 14, pressure);
    _mav_put_int16_t(buf, 16, temperature);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN);
#else
    mavlink_barometer_altitude_t packet;
    packet.time_usec = time_usec;
    packet.altitude = altitude;
    packet.humidity = humidity;
    packet.pressure = pressure;
    packet.temperature = temperature;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_BAROMETER_ALTITUDE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_MIN_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_CRC);
}

/**
 * @brief Pack a barometer_altitude message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 * @param humidity  Humidity (filtered)
 * @param pressure  Pressure (filtered)
 * @param temperature [cdegC] Temperature (filtered)
 * @param altitude [m] 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_barometer_altitude_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, int16_t humidity, int16_t pressure, int16_t temperature, int32_t altitude)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, altitude);
    _mav_put_int16_t(buf, 12, humidity);
    _mav_put_int16_t(buf, 14, pressure);
    _mav_put_int16_t(buf, 16, temperature);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN);
#else
    mavlink_barometer_altitude_t packet;
    packet.time_usec = time_usec;
    packet.altitude = altitude;
    packet.humidity = humidity;
    packet.pressure = pressure;
    packet.temperature = temperature;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_BAROMETER_ALTITUDE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_MIN_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_MIN_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN);
#endif
}

/**
 * @brief Pack a barometer_altitude message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 * @param humidity  Humidity (filtered)
 * @param pressure  Pressure (filtered)
 * @param temperature [cdegC] Temperature (filtered)
 * @param altitude [m] 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_barometer_altitude_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,int16_t humidity,int16_t pressure,int16_t temperature,int32_t altitude)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, altitude);
    _mav_put_int16_t(buf, 12, humidity);
    _mav_put_int16_t(buf, 14, pressure);
    _mav_put_int16_t(buf, 16, temperature);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN);
#else
    mavlink_barometer_altitude_t packet;
    packet.time_usec = time_usec;
    packet.altitude = altitude;
    packet.humidity = humidity;
    packet.pressure = pressure;
    packet.temperature = temperature;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_BAROMETER_ALTITUDE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_MIN_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_CRC);
}

/**
 * @brief Encode a barometer_altitude struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param barometer_altitude C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_barometer_altitude_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_barometer_altitude_t* barometer_altitude)
{
    return mavlink_msg_barometer_altitude_pack(system_id, component_id, msg, barometer_altitude->time_usec, barometer_altitude->humidity, barometer_altitude->pressure, barometer_altitude->temperature, barometer_altitude->altitude);
}

/**
 * @brief Encode a barometer_altitude struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param barometer_altitude C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_barometer_altitude_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_barometer_altitude_t* barometer_altitude)
{
    return mavlink_msg_barometer_altitude_pack_chan(system_id, component_id, chan, msg, barometer_altitude->time_usec, barometer_altitude->humidity, barometer_altitude->pressure, barometer_altitude->temperature, barometer_altitude->altitude);
}

/**
 * @brief Encode a barometer_altitude struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param barometer_altitude C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_barometer_altitude_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_barometer_altitude_t* barometer_altitude)
{
    return mavlink_msg_barometer_altitude_pack_status(system_id, component_id, _status, msg,  barometer_altitude->time_usec, barometer_altitude->humidity, barometer_altitude->pressure, barometer_altitude->temperature, barometer_altitude->altitude);
}

/**
 * @brief Send a barometer_altitude message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 * @param humidity  Humidity (filtered)
 * @param pressure  Pressure (filtered)
 * @param temperature [cdegC] Temperature (filtered)
 * @param altitude [m] 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_barometer_altitude_send(mavlink_channel_t chan, uint64_t time_usec, int16_t humidity, int16_t pressure, int16_t temperature, int32_t altitude)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, altitude);
    _mav_put_int16_t(buf, 12, humidity);
    _mav_put_int16_t(buf, 14, pressure);
    _mav_put_int16_t(buf, 16, temperature);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BAROMETER_ALTITUDE, buf, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_MIN_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_CRC);
#else
    mavlink_barometer_altitude_t packet;
    packet.time_usec = time_usec;
    packet.altitude = altitude;
    packet.humidity = humidity;
    packet.pressure = pressure;
    packet.temperature = temperature;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BAROMETER_ALTITUDE, (const char *)&packet, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_MIN_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_CRC);
#endif
}

/**
 * @brief Send a barometer_altitude message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_barometer_altitude_send_struct(mavlink_channel_t chan, const mavlink_barometer_altitude_t* barometer_altitude)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_barometer_altitude_send(chan, barometer_altitude->time_usec, barometer_altitude->humidity, barometer_altitude->pressure, barometer_altitude->temperature, barometer_altitude->altitude);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BAROMETER_ALTITUDE, (const char *)barometer_altitude, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_MIN_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_CRC);
#endif
}

#if MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_barometer_altitude_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, int16_t humidity, int16_t pressure, int16_t temperature, int32_t altitude)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_int32_t(buf, 8, altitude);
    _mav_put_int16_t(buf, 12, humidity);
    _mav_put_int16_t(buf, 14, pressure);
    _mav_put_int16_t(buf, 16, temperature);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BAROMETER_ALTITUDE, buf, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_MIN_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_CRC);
#else
    mavlink_barometer_altitude_t *packet = (mavlink_barometer_altitude_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->altitude = altitude;
    packet->humidity = humidity;
    packet->pressure = pressure;
    packet->temperature = temperature;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BAROMETER_ALTITUDE, (const char *)packet, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_MIN_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_CRC);
#endif
}
#endif

#endif

// MESSAGE BAROMETER_ALTITUDE UNPACKING


/**
 * @brief Get field time_usec from barometer_altitude message
 *
 * @return [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 */
static inline uint64_t mavlink_msg_barometer_altitude_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field humidity from barometer_altitude message
 *
 * @return  Humidity (filtered)
 */
static inline int16_t mavlink_msg_barometer_altitude_get_humidity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  12);
}

/**
 * @brief Get field pressure from barometer_altitude message
 *
 * @return  Pressure (filtered)
 */
static inline int16_t mavlink_msg_barometer_altitude_get_pressure(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  14);
}

/**
 * @brief Get field temperature from barometer_altitude message
 *
 * @return [cdegC] Temperature (filtered)
 */
static inline int16_t mavlink_msg_barometer_altitude_get_temperature(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  16);
}

/**
 * @brief Get field altitude from barometer_altitude message
 *
 * @return [m] 
 */
static inline int32_t mavlink_msg_barometer_altitude_get_altitude(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Decode a barometer_altitude message into a struct
 *
 * @param msg The message to decode
 * @param barometer_altitude C-struct to decode the message contents into
 */
static inline void mavlink_msg_barometer_altitude_decode(const mavlink_message_t* msg, mavlink_barometer_altitude_t* barometer_altitude)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    barometer_altitude->time_usec = mavlink_msg_barometer_altitude_get_time_usec(msg);
    barometer_altitude->altitude = mavlink_msg_barometer_altitude_get_altitude(msg);
    barometer_altitude->humidity = mavlink_msg_barometer_altitude_get_humidity(msg);
    barometer_altitude->pressure = mavlink_msg_barometer_altitude_get_pressure(msg);
    barometer_altitude->temperature = mavlink_msg_barometer_altitude_get_temperature(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN? msg->len : MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN;
        memset(barometer_altitude, 0, MAVLINK_MSG_ID_BAROMETER_ALTITUDE_LEN);
    memcpy(barometer_altitude, _MAV_PAYLOAD(msg), len);
#endif
}
