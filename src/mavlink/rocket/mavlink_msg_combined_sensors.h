#pragma once
// MESSAGE COMBINED_SENSORS PACKING

#define MAVLINK_MSG_ID_COMBINED_SENSORS 15001


typedef struct __mavlink_combined_sensors_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.*/
 uint32_t altitude; /*< [m] */
 uint32_t xvel; /*< [m/s] Velocity x axis (filtered)*/
 uint32_t yvel; /*< [m/s] Velocity y axis (filtered)*/
 uint32_t zvel; /*< [m/s] Velocity z axis (filtered)*/
 int16_t xacc; /*<  X acceleration (filtered)*/
 int16_t yacc; /*<  Y acceleration (filtered)*/
 int16_t zacc; /*<  Z acceleration (filtered)*/
 int16_t xgyro; /*<  Angular speed around X axis (filtered)*/
 int16_t ygyro; /*<  Angular speed around Y axis (filtered)*/
 int16_t zgyro; /*<  Angular speed around Z axis (filtered)*/
 int16_t xmag; /*<  X Magnetic field (filtered)*/
 int16_t ymag; /*<  Y Magnetic field (filtered)*/
 int16_t zmag; /*<  Z Magnetic field (filtered)*/
 int16_t humidity; /*<  Humidity (filtered)*/
 int16_t pressure; /*<  Pressure (filtered)*/
 int16_t temperature; /*< [cdegC] Temperature (filtered)*/
} mavlink_combined_sensors_t;

#define MAVLINK_MSG_ID_COMBINED_SENSORS_LEN 48
#define MAVLINK_MSG_ID_COMBINED_SENSORS_MIN_LEN 48
#define MAVLINK_MSG_ID_15001_LEN 48
#define MAVLINK_MSG_ID_15001_MIN_LEN 48

#define MAVLINK_MSG_ID_COMBINED_SENSORS_CRC 88
#define MAVLINK_MSG_ID_15001_CRC 88



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_COMBINED_SENSORS { \
    15001, \
    "COMBINED_SENSORS", \
    17, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_combined_sensors_t, time_usec) }, \
         { "xacc", NULL, MAVLINK_TYPE_INT16_T, 0, 24, offsetof(mavlink_combined_sensors_t, xacc) }, \
         { "yacc", NULL, MAVLINK_TYPE_INT16_T, 0, 26, offsetof(mavlink_combined_sensors_t, yacc) }, \
         { "zacc", NULL, MAVLINK_TYPE_INT16_T, 0, 28, offsetof(mavlink_combined_sensors_t, zacc) }, \
         { "xgyro", NULL, MAVLINK_TYPE_INT16_T, 0, 30, offsetof(mavlink_combined_sensors_t, xgyro) }, \
         { "ygyro", NULL, MAVLINK_TYPE_INT16_T, 0, 32, offsetof(mavlink_combined_sensors_t, ygyro) }, \
         { "zgyro", NULL, MAVLINK_TYPE_INT16_T, 0, 34, offsetof(mavlink_combined_sensors_t, zgyro) }, \
         { "xmag", NULL, MAVLINK_TYPE_INT16_T, 0, 36, offsetof(mavlink_combined_sensors_t, xmag) }, \
         { "ymag", NULL, MAVLINK_TYPE_INT16_T, 0, 38, offsetof(mavlink_combined_sensors_t, ymag) }, \
         { "zmag", NULL, MAVLINK_TYPE_INT16_T, 0, 40, offsetof(mavlink_combined_sensors_t, zmag) }, \
         { "humidity", NULL, MAVLINK_TYPE_INT16_T, 0, 42, offsetof(mavlink_combined_sensors_t, humidity) }, \
         { "pressure", NULL, MAVLINK_TYPE_INT16_T, 0, 44, offsetof(mavlink_combined_sensors_t, pressure) }, \
         { "temperature", NULL, MAVLINK_TYPE_INT16_T, 0, 46, offsetof(mavlink_combined_sensors_t, temperature) }, \
         { "altitude", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_combined_sensors_t, altitude) }, \
         { "xvel", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_combined_sensors_t, xvel) }, \
         { "yvel", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_combined_sensors_t, yvel) }, \
         { "zvel", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_combined_sensors_t, zvel) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_COMBINED_SENSORS { \
    "COMBINED_SENSORS", \
    17, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_combined_sensors_t, time_usec) }, \
         { "xacc", NULL, MAVLINK_TYPE_INT16_T, 0, 24, offsetof(mavlink_combined_sensors_t, xacc) }, \
         { "yacc", NULL, MAVLINK_TYPE_INT16_T, 0, 26, offsetof(mavlink_combined_sensors_t, yacc) }, \
         { "zacc", NULL, MAVLINK_TYPE_INT16_T, 0, 28, offsetof(mavlink_combined_sensors_t, zacc) }, \
         { "xgyro", NULL, MAVLINK_TYPE_INT16_T, 0, 30, offsetof(mavlink_combined_sensors_t, xgyro) }, \
         { "ygyro", NULL, MAVLINK_TYPE_INT16_T, 0, 32, offsetof(mavlink_combined_sensors_t, ygyro) }, \
         { "zgyro", NULL, MAVLINK_TYPE_INT16_T, 0, 34, offsetof(mavlink_combined_sensors_t, zgyro) }, \
         { "xmag", NULL, MAVLINK_TYPE_INT16_T, 0, 36, offsetof(mavlink_combined_sensors_t, xmag) }, \
         { "ymag", NULL, MAVLINK_TYPE_INT16_T, 0, 38, offsetof(mavlink_combined_sensors_t, ymag) }, \
         { "zmag", NULL, MAVLINK_TYPE_INT16_T, 0, 40, offsetof(mavlink_combined_sensors_t, zmag) }, \
         { "humidity", NULL, MAVLINK_TYPE_INT16_T, 0, 42, offsetof(mavlink_combined_sensors_t, humidity) }, \
         { "pressure", NULL, MAVLINK_TYPE_INT16_T, 0, 44, offsetof(mavlink_combined_sensors_t, pressure) }, \
         { "temperature", NULL, MAVLINK_TYPE_INT16_T, 0, 46, offsetof(mavlink_combined_sensors_t, temperature) }, \
         { "altitude", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_combined_sensors_t, altitude) }, \
         { "xvel", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_combined_sensors_t, xvel) }, \
         { "yvel", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_combined_sensors_t, yvel) }, \
         { "zvel", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_combined_sensors_t, zvel) }, \
         } \
}
#endif

/**
 * @brief Pack a combined_sensors message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 * @param xacc  X acceleration (filtered)
 * @param yacc  Y acceleration (filtered)
 * @param zacc  Z acceleration (filtered)
 * @param xgyro  Angular speed around X axis (filtered)
 * @param ygyro  Angular speed around Y axis (filtered)
 * @param zgyro  Angular speed around Z axis (filtered)
 * @param xmag  X Magnetic field (filtered)
 * @param ymag  Y Magnetic field (filtered)
 * @param zmag  Z Magnetic field (filtered)
 * @param humidity  Humidity (filtered)
 * @param pressure  Pressure (filtered)
 * @param temperature [cdegC] Temperature (filtered)
 * @param altitude [m] 
 * @param xvel [m/s] Velocity x axis (filtered)
 * @param yvel [m/s] Velocity y axis (filtered)
 * @param zvel [m/s] Velocity z axis (filtered)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_combined_sensors_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag, int16_t humidity, int16_t pressure, int16_t temperature, uint32_t altitude, uint32_t xvel, uint32_t yvel, uint32_t zvel)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMBINED_SENSORS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, altitude);
    _mav_put_uint32_t(buf, 12, xvel);
    _mav_put_uint32_t(buf, 16, yvel);
    _mav_put_uint32_t(buf, 20, zvel);
    _mav_put_int16_t(buf, 24, xacc);
    _mav_put_int16_t(buf, 26, yacc);
    _mav_put_int16_t(buf, 28, zacc);
    _mav_put_int16_t(buf, 30, xgyro);
    _mav_put_int16_t(buf, 32, ygyro);
    _mav_put_int16_t(buf, 34, zgyro);
    _mav_put_int16_t(buf, 36, xmag);
    _mav_put_int16_t(buf, 38, ymag);
    _mav_put_int16_t(buf, 40, zmag);
    _mav_put_int16_t(buf, 42, humidity);
    _mav_put_int16_t(buf, 44, pressure);
    _mav_put_int16_t(buf, 46, temperature);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN);
#else
    mavlink_combined_sensors_t packet;
    packet.time_usec = time_usec;
    packet.altitude = altitude;
    packet.xvel = xvel;
    packet.yvel = yvel;
    packet.zvel = zvel;
    packet.xacc = xacc;
    packet.yacc = yacc;
    packet.zacc = zacc;
    packet.xgyro = xgyro;
    packet.ygyro = ygyro;
    packet.zgyro = zgyro;
    packet.xmag = xmag;
    packet.ymag = ymag;
    packet.zmag = zmag;
    packet.humidity = humidity;
    packet.pressure = pressure;
    packet.temperature = temperature;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COMBINED_SENSORS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_COMBINED_SENSORS_MIN_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_CRC);
}

/**
 * @brief Pack a combined_sensors message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 * @param xacc  X acceleration (filtered)
 * @param yacc  Y acceleration (filtered)
 * @param zacc  Z acceleration (filtered)
 * @param xgyro  Angular speed around X axis (filtered)
 * @param ygyro  Angular speed around Y axis (filtered)
 * @param zgyro  Angular speed around Z axis (filtered)
 * @param xmag  X Magnetic field (filtered)
 * @param ymag  Y Magnetic field (filtered)
 * @param zmag  Z Magnetic field (filtered)
 * @param humidity  Humidity (filtered)
 * @param pressure  Pressure (filtered)
 * @param temperature [cdegC] Temperature (filtered)
 * @param altitude [m] 
 * @param xvel [m/s] Velocity x axis (filtered)
 * @param yvel [m/s] Velocity y axis (filtered)
 * @param zvel [m/s] Velocity z axis (filtered)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_combined_sensors_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag, int16_t humidity, int16_t pressure, int16_t temperature, uint32_t altitude, uint32_t xvel, uint32_t yvel, uint32_t zvel)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMBINED_SENSORS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, altitude);
    _mav_put_uint32_t(buf, 12, xvel);
    _mav_put_uint32_t(buf, 16, yvel);
    _mav_put_uint32_t(buf, 20, zvel);
    _mav_put_int16_t(buf, 24, xacc);
    _mav_put_int16_t(buf, 26, yacc);
    _mav_put_int16_t(buf, 28, zacc);
    _mav_put_int16_t(buf, 30, xgyro);
    _mav_put_int16_t(buf, 32, ygyro);
    _mav_put_int16_t(buf, 34, zgyro);
    _mav_put_int16_t(buf, 36, xmag);
    _mav_put_int16_t(buf, 38, ymag);
    _mav_put_int16_t(buf, 40, zmag);
    _mav_put_int16_t(buf, 42, humidity);
    _mav_put_int16_t(buf, 44, pressure);
    _mav_put_int16_t(buf, 46, temperature);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN);
#else
    mavlink_combined_sensors_t packet;
    packet.time_usec = time_usec;
    packet.altitude = altitude;
    packet.xvel = xvel;
    packet.yvel = yvel;
    packet.zvel = zvel;
    packet.xacc = xacc;
    packet.yacc = yacc;
    packet.zacc = zacc;
    packet.xgyro = xgyro;
    packet.ygyro = ygyro;
    packet.zgyro = zgyro;
    packet.xmag = xmag;
    packet.ymag = ymag;
    packet.zmag = zmag;
    packet.humidity = humidity;
    packet.pressure = pressure;
    packet.temperature = temperature;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COMBINED_SENSORS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_COMBINED_SENSORS_MIN_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_COMBINED_SENSORS_MIN_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN);
#endif
}

/**
 * @brief Pack a combined_sensors message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 * @param xacc  X acceleration (filtered)
 * @param yacc  Y acceleration (filtered)
 * @param zacc  Z acceleration (filtered)
 * @param xgyro  Angular speed around X axis (filtered)
 * @param ygyro  Angular speed around Y axis (filtered)
 * @param zgyro  Angular speed around Z axis (filtered)
 * @param xmag  X Magnetic field (filtered)
 * @param ymag  Y Magnetic field (filtered)
 * @param zmag  Z Magnetic field (filtered)
 * @param humidity  Humidity (filtered)
 * @param pressure  Pressure (filtered)
 * @param temperature [cdegC] Temperature (filtered)
 * @param altitude [m] 
 * @param xvel [m/s] Velocity x axis (filtered)
 * @param yvel [m/s] Velocity y axis (filtered)
 * @param zvel [m/s] Velocity z axis (filtered)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_combined_sensors_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,int16_t xacc,int16_t yacc,int16_t zacc,int16_t xgyro,int16_t ygyro,int16_t zgyro,int16_t xmag,int16_t ymag,int16_t zmag,int16_t humidity,int16_t pressure,int16_t temperature,uint32_t altitude,uint32_t xvel,uint32_t yvel,uint32_t zvel)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMBINED_SENSORS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, altitude);
    _mav_put_uint32_t(buf, 12, xvel);
    _mav_put_uint32_t(buf, 16, yvel);
    _mav_put_uint32_t(buf, 20, zvel);
    _mav_put_int16_t(buf, 24, xacc);
    _mav_put_int16_t(buf, 26, yacc);
    _mav_put_int16_t(buf, 28, zacc);
    _mav_put_int16_t(buf, 30, xgyro);
    _mav_put_int16_t(buf, 32, ygyro);
    _mav_put_int16_t(buf, 34, zgyro);
    _mav_put_int16_t(buf, 36, xmag);
    _mav_put_int16_t(buf, 38, ymag);
    _mav_put_int16_t(buf, 40, zmag);
    _mav_put_int16_t(buf, 42, humidity);
    _mav_put_int16_t(buf, 44, pressure);
    _mav_put_int16_t(buf, 46, temperature);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN);
#else
    mavlink_combined_sensors_t packet;
    packet.time_usec = time_usec;
    packet.altitude = altitude;
    packet.xvel = xvel;
    packet.yvel = yvel;
    packet.zvel = zvel;
    packet.xacc = xacc;
    packet.yacc = yacc;
    packet.zacc = zacc;
    packet.xgyro = xgyro;
    packet.ygyro = ygyro;
    packet.zgyro = zgyro;
    packet.xmag = xmag;
    packet.ymag = ymag;
    packet.zmag = zmag;
    packet.humidity = humidity;
    packet.pressure = pressure;
    packet.temperature = temperature;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COMBINED_SENSORS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_COMBINED_SENSORS_MIN_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_CRC);
}

/**
 * @brief Encode a combined_sensors struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param combined_sensors C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_combined_sensors_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_combined_sensors_t* combined_sensors)
{
    return mavlink_msg_combined_sensors_pack(system_id, component_id, msg, combined_sensors->time_usec, combined_sensors->xacc, combined_sensors->yacc, combined_sensors->zacc, combined_sensors->xgyro, combined_sensors->ygyro, combined_sensors->zgyro, combined_sensors->xmag, combined_sensors->ymag, combined_sensors->zmag, combined_sensors->humidity, combined_sensors->pressure, combined_sensors->temperature, combined_sensors->altitude, combined_sensors->xvel, combined_sensors->yvel, combined_sensors->zvel);
}

/**
 * @brief Encode a combined_sensors struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param combined_sensors C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_combined_sensors_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_combined_sensors_t* combined_sensors)
{
    return mavlink_msg_combined_sensors_pack_chan(system_id, component_id, chan, msg, combined_sensors->time_usec, combined_sensors->xacc, combined_sensors->yacc, combined_sensors->zacc, combined_sensors->xgyro, combined_sensors->ygyro, combined_sensors->zgyro, combined_sensors->xmag, combined_sensors->ymag, combined_sensors->zmag, combined_sensors->humidity, combined_sensors->pressure, combined_sensors->temperature, combined_sensors->altitude, combined_sensors->xvel, combined_sensors->yvel, combined_sensors->zvel);
}

/**
 * @brief Encode a combined_sensors struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param combined_sensors C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_combined_sensors_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_combined_sensors_t* combined_sensors)
{
    return mavlink_msg_combined_sensors_pack_status(system_id, component_id, _status, msg,  combined_sensors->time_usec, combined_sensors->xacc, combined_sensors->yacc, combined_sensors->zacc, combined_sensors->xgyro, combined_sensors->ygyro, combined_sensors->zgyro, combined_sensors->xmag, combined_sensors->ymag, combined_sensors->zmag, combined_sensors->humidity, combined_sensors->pressure, combined_sensors->temperature, combined_sensors->altitude, combined_sensors->xvel, combined_sensors->yvel, combined_sensors->zvel);
}

/**
 * @brief Send a combined_sensors message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 * @param xacc  X acceleration (filtered)
 * @param yacc  Y acceleration (filtered)
 * @param zacc  Z acceleration (filtered)
 * @param xgyro  Angular speed around X axis (filtered)
 * @param ygyro  Angular speed around Y axis (filtered)
 * @param zgyro  Angular speed around Z axis (filtered)
 * @param xmag  X Magnetic field (filtered)
 * @param ymag  Y Magnetic field (filtered)
 * @param zmag  Z Magnetic field (filtered)
 * @param humidity  Humidity (filtered)
 * @param pressure  Pressure (filtered)
 * @param temperature [cdegC] Temperature (filtered)
 * @param altitude [m] 
 * @param xvel [m/s] Velocity x axis (filtered)
 * @param yvel [m/s] Velocity y axis (filtered)
 * @param zvel [m/s] Velocity z axis (filtered)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_combined_sensors_send(mavlink_channel_t chan, uint64_t time_usec, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag, int16_t humidity, int16_t pressure, int16_t temperature, uint32_t altitude, uint32_t xvel, uint32_t yvel, uint32_t zvel)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMBINED_SENSORS_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, altitude);
    _mav_put_uint32_t(buf, 12, xvel);
    _mav_put_uint32_t(buf, 16, yvel);
    _mav_put_uint32_t(buf, 20, zvel);
    _mav_put_int16_t(buf, 24, xacc);
    _mav_put_int16_t(buf, 26, yacc);
    _mav_put_int16_t(buf, 28, zacc);
    _mav_put_int16_t(buf, 30, xgyro);
    _mav_put_int16_t(buf, 32, ygyro);
    _mav_put_int16_t(buf, 34, zgyro);
    _mav_put_int16_t(buf, 36, xmag);
    _mav_put_int16_t(buf, 38, ymag);
    _mav_put_int16_t(buf, 40, zmag);
    _mav_put_int16_t(buf, 42, humidity);
    _mav_put_int16_t(buf, 44, pressure);
    _mav_put_int16_t(buf, 46, temperature);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMBINED_SENSORS, buf, MAVLINK_MSG_ID_COMBINED_SENSORS_MIN_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_CRC);
#else
    mavlink_combined_sensors_t packet;
    packet.time_usec = time_usec;
    packet.altitude = altitude;
    packet.xvel = xvel;
    packet.yvel = yvel;
    packet.zvel = zvel;
    packet.xacc = xacc;
    packet.yacc = yacc;
    packet.zacc = zacc;
    packet.xgyro = xgyro;
    packet.ygyro = ygyro;
    packet.zgyro = zgyro;
    packet.xmag = xmag;
    packet.ymag = ymag;
    packet.zmag = zmag;
    packet.humidity = humidity;
    packet.pressure = pressure;
    packet.temperature = temperature;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMBINED_SENSORS, (const char *)&packet, MAVLINK_MSG_ID_COMBINED_SENSORS_MIN_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_CRC);
#endif
}

/**
 * @brief Send a combined_sensors message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_combined_sensors_send_struct(mavlink_channel_t chan, const mavlink_combined_sensors_t* combined_sensors)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_combined_sensors_send(chan, combined_sensors->time_usec, combined_sensors->xacc, combined_sensors->yacc, combined_sensors->zacc, combined_sensors->xgyro, combined_sensors->ygyro, combined_sensors->zgyro, combined_sensors->xmag, combined_sensors->ymag, combined_sensors->zmag, combined_sensors->humidity, combined_sensors->pressure, combined_sensors->temperature, combined_sensors->altitude, combined_sensors->xvel, combined_sensors->yvel, combined_sensors->zvel);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMBINED_SENSORS, (const char *)combined_sensors, MAVLINK_MSG_ID_COMBINED_SENSORS_MIN_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_CRC);
#endif
}

#if MAVLINK_MSG_ID_COMBINED_SENSORS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_combined_sensors_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag, int16_t humidity, int16_t pressure, int16_t temperature, uint32_t altitude, uint32_t xvel, uint32_t yvel, uint32_t zvel)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, altitude);
    _mav_put_uint32_t(buf, 12, xvel);
    _mav_put_uint32_t(buf, 16, yvel);
    _mav_put_uint32_t(buf, 20, zvel);
    _mav_put_int16_t(buf, 24, xacc);
    _mav_put_int16_t(buf, 26, yacc);
    _mav_put_int16_t(buf, 28, zacc);
    _mav_put_int16_t(buf, 30, xgyro);
    _mav_put_int16_t(buf, 32, ygyro);
    _mav_put_int16_t(buf, 34, zgyro);
    _mav_put_int16_t(buf, 36, xmag);
    _mav_put_int16_t(buf, 38, ymag);
    _mav_put_int16_t(buf, 40, zmag);
    _mav_put_int16_t(buf, 42, humidity);
    _mav_put_int16_t(buf, 44, pressure);
    _mav_put_int16_t(buf, 46, temperature);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMBINED_SENSORS, buf, MAVLINK_MSG_ID_COMBINED_SENSORS_MIN_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_CRC);
#else
    mavlink_combined_sensors_t *packet = (mavlink_combined_sensors_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->altitude = altitude;
    packet->xvel = xvel;
    packet->yvel = yvel;
    packet->zvel = zvel;
    packet->xacc = xacc;
    packet->yacc = yacc;
    packet->zacc = zacc;
    packet->xgyro = xgyro;
    packet->ygyro = ygyro;
    packet->zgyro = zgyro;
    packet->xmag = xmag;
    packet->ymag = ymag;
    packet->zmag = zmag;
    packet->humidity = humidity;
    packet->pressure = pressure;
    packet->temperature = temperature;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMBINED_SENSORS, (const char *)packet, MAVLINK_MSG_ID_COMBINED_SENSORS_MIN_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN, MAVLINK_MSG_ID_COMBINED_SENSORS_CRC);
#endif
}
#endif

#endif

// MESSAGE COMBINED_SENSORS UNPACKING


/**
 * @brief Get field time_usec from combined_sensors message
 *
 * @return [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
 */
static inline uint64_t mavlink_msg_combined_sensors_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field xacc from combined_sensors message
 *
 * @return  X acceleration (filtered)
 */
static inline int16_t mavlink_msg_combined_sensors_get_xacc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  24);
}

/**
 * @brief Get field yacc from combined_sensors message
 *
 * @return  Y acceleration (filtered)
 */
static inline int16_t mavlink_msg_combined_sensors_get_yacc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  26);
}

/**
 * @brief Get field zacc from combined_sensors message
 *
 * @return  Z acceleration (filtered)
 */
static inline int16_t mavlink_msg_combined_sensors_get_zacc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  28);
}

/**
 * @brief Get field xgyro from combined_sensors message
 *
 * @return  Angular speed around X axis (filtered)
 */
static inline int16_t mavlink_msg_combined_sensors_get_xgyro(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  30);
}

/**
 * @brief Get field ygyro from combined_sensors message
 *
 * @return  Angular speed around Y axis (filtered)
 */
static inline int16_t mavlink_msg_combined_sensors_get_ygyro(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  32);
}

/**
 * @brief Get field zgyro from combined_sensors message
 *
 * @return  Angular speed around Z axis (filtered)
 */
static inline int16_t mavlink_msg_combined_sensors_get_zgyro(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  34);
}

/**
 * @brief Get field xmag from combined_sensors message
 *
 * @return  X Magnetic field (filtered)
 */
static inline int16_t mavlink_msg_combined_sensors_get_xmag(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  36);
}

/**
 * @brief Get field ymag from combined_sensors message
 *
 * @return  Y Magnetic field (filtered)
 */
static inline int16_t mavlink_msg_combined_sensors_get_ymag(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  38);
}

/**
 * @brief Get field zmag from combined_sensors message
 *
 * @return  Z Magnetic field (filtered)
 */
static inline int16_t mavlink_msg_combined_sensors_get_zmag(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  40);
}

/**
 * @brief Get field humidity from combined_sensors message
 *
 * @return  Humidity (filtered)
 */
static inline int16_t mavlink_msg_combined_sensors_get_humidity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  42);
}

/**
 * @brief Get field pressure from combined_sensors message
 *
 * @return  Pressure (filtered)
 */
static inline int16_t mavlink_msg_combined_sensors_get_pressure(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  44);
}

/**
 * @brief Get field temperature from combined_sensors message
 *
 * @return [cdegC] Temperature (filtered)
 */
static inline int16_t mavlink_msg_combined_sensors_get_temperature(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  46);
}

/**
 * @brief Get field altitude from combined_sensors message
 *
 * @return [m] 
 */
static inline uint32_t mavlink_msg_combined_sensors_get_altitude(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field xvel from combined_sensors message
 *
 * @return [m/s] Velocity x axis (filtered)
 */
static inline uint32_t mavlink_msg_combined_sensors_get_xvel(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field yvel from combined_sensors message
 *
 * @return [m/s] Velocity y axis (filtered)
 */
static inline uint32_t mavlink_msg_combined_sensors_get_yvel(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field zvel from combined_sensors message
 *
 * @return [m/s] Velocity z axis (filtered)
 */
static inline uint32_t mavlink_msg_combined_sensors_get_zvel(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  20);
}

/**
 * @brief Decode a combined_sensors message into a struct
 *
 * @param msg The message to decode
 * @param combined_sensors C-struct to decode the message contents into
 */
static inline void mavlink_msg_combined_sensors_decode(const mavlink_message_t* msg, mavlink_combined_sensors_t* combined_sensors)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    combined_sensors->time_usec = mavlink_msg_combined_sensors_get_time_usec(msg);
    combined_sensors->altitude = mavlink_msg_combined_sensors_get_altitude(msg);
    combined_sensors->xvel = mavlink_msg_combined_sensors_get_xvel(msg);
    combined_sensors->yvel = mavlink_msg_combined_sensors_get_yvel(msg);
    combined_sensors->zvel = mavlink_msg_combined_sensors_get_zvel(msg);
    combined_sensors->xacc = mavlink_msg_combined_sensors_get_xacc(msg);
    combined_sensors->yacc = mavlink_msg_combined_sensors_get_yacc(msg);
    combined_sensors->zacc = mavlink_msg_combined_sensors_get_zacc(msg);
    combined_sensors->xgyro = mavlink_msg_combined_sensors_get_xgyro(msg);
    combined_sensors->ygyro = mavlink_msg_combined_sensors_get_ygyro(msg);
    combined_sensors->zgyro = mavlink_msg_combined_sensors_get_zgyro(msg);
    combined_sensors->xmag = mavlink_msg_combined_sensors_get_xmag(msg);
    combined_sensors->ymag = mavlink_msg_combined_sensors_get_ymag(msg);
    combined_sensors->zmag = mavlink_msg_combined_sensors_get_zmag(msg);
    combined_sensors->humidity = mavlink_msg_combined_sensors_get_humidity(msg);
    combined_sensors->pressure = mavlink_msg_combined_sensors_get_pressure(msg);
    combined_sensors->temperature = mavlink_msg_combined_sensors_get_temperature(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_COMBINED_SENSORS_LEN? msg->len : MAVLINK_MSG_ID_COMBINED_SENSORS_LEN;
        memset(combined_sensors, 0, MAVLINK_MSG_ID_COMBINED_SENSORS_LEN);
    memcpy(combined_sensors, _MAV_PAYLOAD(msg), len);
#endif
}
