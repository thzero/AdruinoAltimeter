/** @file
 *  @brief MAVLink comm protocol generated from rocket.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_ROCKET_H
#define MAVLINK_ROCKET_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_ROCKET.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_ROCKET_XML_HASH 6283125372011404993

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{0, 50, 9, 9, 0, 0, 0}, {1, 124, 31, 43, 0, 0, 0}, {2, 137, 12, 12, 0, 0, 0}, {4, 237, 14, 14, 3, 12, 13}, {11, 89, 6, 6, 1, 4, 0}, {20, 214, 20, 20, 3, 2, 3}, {21, 159, 2, 2, 3, 0, 1}, {22, 220, 25, 25, 0, 0, 0}, {23, 168, 23, 23, 3, 4, 5}, {24, 24, 30, 52, 0, 0, 0}, {25, 23, 101, 101, 0, 0, 0}, {27, 144, 26, 29, 0, 0, 0}, {28, 67, 16, 16, 0, 0, 0}, {30, 39, 28, 28, 0, 0, 0}, {31, 246, 32, 48, 0, 0, 0}, {33, 104, 28, 28, 0, 0, 0}, {36, 222, 21, 37, 0, 0, 0}, {75, 158, 35, 35, 3, 30, 31}, {76, 152, 33, 33, 3, 30, 31}, {77, 143, 3, 10, 3, 8, 9}, {80, 14, 4, 4, 3, 2, 3}, {90, 183, 56, 56, 0, 0, 0}, {92, 54, 33, 33, 0, 0, 0}, {108, 32, 84, 92, 0, 0, 0}, {111, 34, 16, 18, 3, 16, 17}, {112, 174, 12, 12, 0, 0, 0}, {113, 124, 36, 39, 0, 0, 0}, {115, 4, 64, 64, 0, 0, 0}, {117, 128, 6, 6, 3, 4, 5}, {118, 56, 14, 14, 0, 0, 0}, {119, 116, 12, 12, 3, 10, 11}, {120, 134, 97, 97, 0, 0, 0}, {121, 237, 2, 2, 3, 0, 1}, {122, 203, 2, 2, 3, 0, 1}, {148, 178, 60, 78, 0, 0, 0}, {244, 95, 6, 6, 0, 0, 0}, {261, 179, 27, 61, 0, 0, 0}, {299, 19, 96, 98, 0, 0, 0}, {300, 217, 22, 22, 0, 0, 0}, {400, 110, 254, 254, 3, 4, 5}, {401, 183, 6, 6, 3, 4, 5}, {15000, 139, 18, 18, 0, 0, 0}, {15001, 88, 48, 48, 0, 0, 0}, {15002, 158, 45, 45, 3, 10, 11}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_ROCKET

// ENUM DEFINITIONS


/** @brief Flags to report failure cases over the high latency telemetry. */
#ifndef HAVE_ENUM_HL_FAILURE_FLAG
#define HAVE_ENUM_HL_FAILURE_FLAG
typedef enum HL_FAILURE_FLAG
{
   HL_FAILURE_FLAG_GPS=1, /* GPS failure. | */
   HL_FAILURE_FLAG_DIFFERENTIAL_PRESSURE=2, /* Differential pressure sensor failure. | */
   HL_FAILURE_FLAG_ABSOLUTE_PRESSURE=4, /* Absolute pressure sensor failure. | */
   HL_FAILURE_FLAG_3D_ACCEL=8, /* Accelerometer sensor failure. | */
   HL_FAILURE_FLAG_3D_GYRO=16, /* Gyroscope sensor failure. | */
   HL_FAILURE_FLAG_3D_MAG=32, /* Magnetometer sensor failure. | */
   HL_FAILURE_FLAG_TERRAIN=64, /* Terrain subsystem failure. | */
   HL_FAILURE_FLAG_BATTERY=128, /* Battery failure/critical low battery. | */
   HL_FAILURE_FLAG_RC_RECEIVER=256, /* RC receiver failure/no RC connection. | */
   HL_FAILURE_FLAG_OFFBOARD_LINK=512, /* Offboard link failure. | */
   HL_FAILURE_FLAG_ENGINE=1024, /* Engine failure. | */
   HL_FAILURE_FLAG_GEOFENCE=2048, /* Geofence violation. | */
   HL_FAILURE_FLAG_ESTIMATOR=4096, /* Estimator failure, for example measurement rejection or large variances. | */
   HL_FAILURE_FLAG_MISSION=8192, /* Mission failure. | */
   HL_FAILURE_FLAG_ENUM_END=8193, /*  | */
} HL_FAILURE_FLAG;
#endif

/** @brief Predefined OR-combined MAV_MODE_FLAG values. These can simplify using the flags when setting modes. Note that manual input is enabled in all modes as a safety override. */
#ifndef HAVE_ENUM_MAV_MODE
#define HAVE_ENUM_MAV_MODE
typedef enum MAV_MODE
{
   MAV_MODE_PREFLIGHT=0, /* System is not ready to fly, booting, calibrating, etc. No flag is set. | */
   MAV_MODE_MANUAL_DISARMED=64, /* System is allowed to be active, under manual (RC) control, no stabilization (MAV_MODE_FLAG_MANUAL_INPUT_ENABLED) | */
   MAV_MODE_TEST_DISARMED=66, /* UNDEFINED mode. This solely depends on the autopilot - use with caution, intended for developers only. (MAV_MODE_FLAG_MANUAL_INPUT_ENABLED, MAV_MODE_FLAG_TEST_ENABLED). | */
   MAV_MODE_STABILIZE_DISARMED=80, /* System is allowed to be active, under assisted RC control (MAV_MODE_FLAG_SAFETY_ARMED, MAV_MODE_FLAG_STABILIZE_ENABLED) | */
   MAV_MODE_GUIDED_DISARMED=88, /* System is allowed to be active, under autonomous control, manual setpoint (MAV_MODE_FLAG_SAFETY_ARMED, MAV_MODE_FLAG_STABILIZE_ENABLED, MAV_MODE_FLAG_GUIDED_ENABLED) | */
   MAV_MODE_AUTO_DISARMED=92, /* System is allowed to be active, under autonomous control and navigation (the trajectory is decided onboard and not pre-programmed by waypoints). (MAV_MODE_FLAG_SAFETY_ARMED, MAV_MODE_FLAG_STABILIZE_ENABLED, MAV_MODE_FLAG_GUIDED_ENABLED, MAV_MODE_FLAG_AUTO_ENABLED). | */
   MAV_MODE_MANUAL_ARMED=192, /* System is allowed to be active, under manual (RC) control, no stabilization (MAV_MODE_FLAG_SAFETY_ARMED, MAV_MODE_FLAG_MANUAL_INPUT_ENABLED) | */
   MAV_MODE_TEST_ARMED=194, /* UNDEFINED mode. This solely depends on the autopilot - use with caution, intended for developers only (MAV_MODE_FLAG_SAFETY_ARMED, MAV_MODE_FLAG_MANUAL_INPUT_ENABLED, MAV_MODE_FLAG_TEST_ENABLED) | */
   MAV_MODE_STABILIZE_ARMED=208, /* System is allowed to be active, under assisted RC control (MAV_MODE_FLAG_SAFETY_ARMED, MAV_MODE_FLAG_MANUAL_INPUT_ENABLED, MAV_MODE_FLAG_STABILIZE_ENABLED) | */
   MAV_MODE_GUIDED_ARMED=216, /* System is allowed to be active, under autonomous control, manual setpoint (MAV_MODE_FLAG_SAFETY_ARMED, MAV_MODE_FLAG_MANUAL_INPUT_ENABLED, MAV_MODE_FLAG_STABILIZE_ENABLED, MAV_MODE_FLAG_GUIDED_ENABLED) | */
   MAV_MODE_AUTO_ARMED=220, /* System is allowed to be active, under autonomous control and navigation (the trajectory is decided onboard and not pre-programmed by waypoints). (MAV_MODE_FLAG_SAFETY_ARMED, MAV_MODE_FLAG_MANUAL_INPUT_ENABLED, MAV_MODE_FLAG_STABILIZE_ENABLED, MAV_MODE_FLAG_GUIDED_ENABLED,MAV_MODE_FLAG_AUTO_ENABLED). | */
   MAV_MODE_ENUM_END=221, /*  | */
} MAV_MODE;
#endif

/** @brief These encode the sensors whose status is sent as part of the SYS_STATUS message. */
#ifndef HAVE_ENUM_MAV_SYS_STATUS_SENSOR
#define HAVE_ENUM_MAV_SYS_STATUS_SENSOR
typedef enum MAV_SYS_STATUS_SENSOR
{
   MAV_SYS_STATUS_SENSOR_3D_GYRO=1, /* 0x01 3D gyro | */
   MAV_SYS_STATUS_SENSOR_3D_ACCEL=2, /* 0x02 3D accelerometer | */
   MAV_SYS_STATUS_SENSOR_3D_MAG=4, /* 0x04 3D magnetometer | */
   MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE=8, /* 0x08 absolute pressure | */
   MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE=16, /* 0x10 differential pressure | */
   MAV_SYS_STATUS_SENSOR_GPS=32, /* 0x20 GPS | */
   MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW=64, /* 0x40 optical flow | */
   MAV_SYS_STATUS_SENSOR_VISION_POSITION=128, /* 0x80 computer vision position | */
   MAV_SYS_STATUS_SENSOR_LASER_POSITION=256, /* 0x100 laser based position | */
   MAV_SYS_STATUS_SENSOR_EXTERNAL_GROUND_TRUTH=512, /* 0x200 external ground truth (Vicon or Leica) | */
   MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL=1024, /* 0x400 3D angular rate control | */
   MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION=2048, /* 0x800 attitude stabilization | */
   MAV_SYS_STATUS_SENSOR_YAW_POSITION=4096, /* 0x1000 yaw position | */
   MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL=8192, /* 0x2000 z/altitude control | */
   MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL=16384, /* 0x4000 x/y position control | */
   MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS=32768, /* 0x8000 motor outputs / control | */
   MAV_SYS_STATUS_SENSOR_RC_RECEIVER=65536, /* 0x10000 RC receiver | */
   MAV_SYS_STATUS_SENSOR_3D_GYRO2=131072, /* 0x20000 2nd 3D gyro | */
   MAV_SYS_STATUS_SENSOR_3D_ACCEL2=262144, /* 0x40000 2nd 3D accelerometer | */
   MAV_SYS_STATUS_SENSOR_3D_MAG2=524288, /* 0x80000 2nd 3D magnetometer | */
   MAV_SYS_STATUS_GEOFENCE=1048576, /* 0x100000 geofence | */
   MAV_SYS_STATUS_AHRS=2097152, /* 0x200000 AHRS subsystem health | */
   MAV_SYS_STATUS_TERRAIN=4194304, /* 0x400000 Terrain subsystem health | */
   MAV_SYS_STATUS_REVERSE_MOTOR=8388608, /* 0x800000 Motors are reversed | */
   MAV_SYS_STATUS_LOGGING=16777216, /* 0x1000000 Logging | */
   MAV_SYS_STATUS_SENSOR_BATTERY=33554432, /* 0x2000000 Battery | */
   MAV_SYS_STATUS_SENSOR_PROXIMITY=67108864, /* 0x4000000 Proximity | */
   MAV_SYS_STATUS_SENSOR_SATCOM=134217728, /* 0x8000000 Satellite Communication  | */
   MAV_SYS_STATUS_PREARM_CHECK=268435456, /* 0x10000000 pre-arm check status. Always healthy when armed | */
   MAV_SYS_STATUS_OBSTACLE_AVOIDANCE=536870912, /* 0x20000000 Avoidance/collision prevention | */
   MAV_SYS_STATUS_SENSOR_PROPULSION=1073741824, /* 0x40000000 propulsion (actuator, esc, motor or propellor) | */
   MAV_SYS_STATUS_EXTENSION_USED=2147483648, /* 0x80000000 Extended bit-field are used for further sensor status bits (needs to be set in onboard_control_sensors_present only) | */
   MAV_SYS_STATUS_SENSOR_ENUM_END=2147483649, /*  | */
} MAV_SYS_STATUS_SENSOR;
#endif

/** @brief Coordinate frames used by MAVLink. Not all frames are supported by all commands, messages, or vehicles.

      Global frames use the following naming conventions:
      - "GLOBAL": Global coordinate frame with WGS84 latitude/longitude and altitude positive over mean sea level (MSL) by default.
        The following modifiers may be used with "GLOBAL":
        - "RELATIVE_ALT": Altitude is relative to the vehicle home position rather than MSL.
        - "TERRAIN_ALT": Altitude is relative to ground level rather than MSL.
        - "INT": Latitude/longitude (in degrees) are scaled by multiplying by 1E7.

      Local frames use the following naming conventions:
      - "LOCAL": Origin of local frame is fixed relative to earth. Unless otherwise specified this origin is the origin of the vehicle position-estimator ("EKF").
      - "BODY": Origin of local frame travels with the vehicle. NOTE, "BODY" does NOT indicate alignment of frame axis with vehicle attitude.
      - "OFFSET": Deprecated synonym for "BODY" (origin travels with the vehicle). Not to be used for new frames.

      Some deprecated frames do not follow these conventions (e.g. MAV_FRAME_BODY_NED and MAV_FRAME_BODY_OFFSET_NED).
       */
#ifndef HAVE_ENUM_MAV_FRAME
#define HAVE_ENUM_MAV_FRAME
typedef enum MAV_FRAME
{
   MAV_FRAME_GLOBAL=0, /* Global (WGS84) coordinate frame + altitude relative to mean sea level (MSL). | */
   MAV_FRAME_LOCAL_NED=1, /* NED local tangent frame (x: North, y: East, z: Down) with origin fixed relative to earth. | */
   MAV_FRAME_MISSION=2, /* NOT a coordinate frame, indicates a mission command. | */
   MAV_FRAME_GLOBAL_RELATIVE_ALT=3, /* 
          Global (WGS84) coordinate frame + altitude relative to the home position.
         | */
   MAV_FRAME_LOCAL_ENU=4, /* ENU local tangent frame (x: East, y: North, z: Up) with origin fixed relative to earth. | */
   MAV_FRAME_GLOBAL_INT=5, /* Global (WGS84) coordinate frame (scaled) + altitude relative to mean sea level (MSL). | */
   MAV_FRAME_GLOBAL_RELATIVE_ALT_INT=6, /* Global (WGS84) coordinate frame (scaled) + altitude relative to the home position.  | */
   MAV_FRAME_LOCAL_OFFSET_NED=7, /* NED local tangent frame (x: North, y: East, z: Down) with origin that travels with the vehicle. | */
   MAV_FRAME_BODY_NED=8, /* Same as MAV_FRAME_LOCAL_NED when used to represent position values. Same as MAV_FRAME_BODY_FRD when used with velocity/acceleration values. | */
   MAV_FRAME_BODY_OFFSET_NED=9, /* This is the same as MAV_FRAME_BODY_FRD. | */
   MAV_FRAME_GLOBAL_TERRAIN_ALT=10, /* Global (WGS84) coordinate frame with AGL altitude (altitude at ground level). | */
   MAV_FRAME_GLOBAL_TERRAIN_ALT_INT=11, /* Global (WGS84) coordinate frame (scaled) with AGL altitude (altitude at ground level). | */
   MAV_FRAME_BODY_FRD=12, /* FRD local frame aligned to the vehicle's attitude (x: Forward, y: Right, z: Down) with an origin that travels with vehicle. | */
   MAV_FRAME_RESERVED_13=13, /* MAV_FRAME_BODY_FLU - Body fixed frame of reference, Z-up (x: Forward, y: Left, z: Up). | */
   MAV_FRAME_RESERVED_14=14, /* MAV_FRAME_MOCAP_NED - Odometry local coordinate frame of data given by a motion capture system, Z-down (x: North, y: East, z: Down). | */
   MAV_FRAME_RESERVED_15=15, /* MAV_FRAME_MOCAP_ENU - Odometry local coordinate frame of data given by a motion capture system, Z-up (x: East, y: North, z: Up). | */
   MAV_FRAME_RESERVED_16=16, /* MAV_FRAME_VISION_NED - Odometry local coordinate frame of data given by a vision estimation system, Z-down (x: North, y: East, z: Down). | */
   MAV_FRAME_RESERVED_17=17, /* MAV_FRAME_VISION_ENU - Odometry local coordinate frame of data given by a vision estimation system, Z-up (x: East, y: North, z: Up). | */
   MAV_FRAME_RESERVED_18=18, /* MAV_FRAME_ESTIM_NED - Odometry local coordinate frame of data given by an estimator running onboard the vehicle, Z-down (x: North, y: East, z: Down). | */
   MAV_FRAME_RESERVED_19=19, /* MAV_FRAME_ESTIM_ENU - Odometry local coordinate frame of data given by an estimator running onboard the vehicle, Z-up (x: East, y: North, z: Up). | */
   MAV_FRAME_LOCAL_FRD=20, /* FRD local tangent frame (x: Forward, y: Right, z: Down) with origin fixed relative to earth. The forward axis is aligned to the front of the vehicle in the horizontal plane. | */
   MAV_FRAME_LOCAL_FLU=21, /* FLU local tangent frame (x: Forward, y: Left, z: Up) with origin fixed relative to earth. The forward axis is aligned to the front of the vehicle in the horizontal plane. | */
   MAV_FRAME_ENUM_END=22, /*  | */
} MAV_FRAME;
#endif

/** @brief Possible responses from a WIFI_CONFIG_AP message. */
#ifndef HAVE_ENUM_WIFI_CONFIG_AP_RESPONSE
#define HAVE_ENUM_WIFI_CONFIG_AP_RESPONSE
typedef enum WIFI_CONFIG_AP_RESPONSE
{
   WIFI_CONFIG_AP_RESPONSE_UNDEFINED=0, /* Undefined response. Likely an indicative of a system that doesn't support this request. | */
   WIFI_CONFIG_AP_RESPONSE_ACCEPTED=1, /* Changes accepted. | */
   WIFI_CONFIG_AP_RESPONSE_REJECTED=2, /* Changes rejected. | */
   WIFI_CONFIG_AP_RESPONSE_MODE_ERROR=3, /* Invalid Mode. | */
   WIFI_CONFIG_AP_RESPONSE_SSID_ERROR=4, /* Invalid SSID. | */
   WIFI_CONFIG_AP_RESPONSE_PASSWORD_ERROR=5, /* Invalid Password. | */
   WIFI_CONFIG_AP_RESPONSE_ENUM_END=6, /*  | */
} WIFI_CONFIG_AP_RESPONSE;
#endif

/** @brief WiFi Mode. */
#ifndef HAVE_ENUM_WIFI_CONFIG_AP_MODE
#define HAVE_ENUM_WIFI_CONFIG_AP_MODE
typedef enum WIFI_CONFIG_AP_MODE
{
   WIFI_CONFIG_AP_MODE_UNDEFINED=0, /* WiFi mode is undefined. | */
   WIFI_CONFIG_AP_MODE_AP=1, /* WiFi configured as an access point. | */
   WIFI_CONFIG_AP_MODE_STATION=2, /* WiFi configured as a station connected to an existing local WiFi network. | */
   WIFI_CONFIG_AP_MODE_DISABLED=3, /* WiFi disabled. | */
   WIFI_CONFIG_AP_MODE_ENUM_END=4, /*  | */
} WIFI_CONFIG_AP_MODE;
#endif

/** @brief Reboot/shutdown action for selected component in MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN. */
#ifndef HAVE_ENUM_REBOOT_SHUTDOWN_ACTION
#define HAVE_ENUM_REBOOT_SHUTDOWN_ACTION
typedef enum REBOOT_SHUTDOWN_ACTION
{
   REBOOT_SHUTDOWN_ACTION_NONE=0, /* Do nothing. | */
   REBOOT_SHUTDOWN_ACTION_REBOOT=1, /* Reboot component. | */
   REBOOT_SHUTDOWN_ACTION_SHUTDOWN=2, /* Shutdown component. | */
   REBOOT_SHUTDOWN_ACTION_REBOOT_TO_BOOTLOADER=3, /* Reboot component and keep it in the bootloader until upgraded. | */
   REBOOT_SHUTDOWN_ACTION_POWER_ON=4, /* Power on component. Do nothing if component is already powered (ACK command with MAV_RESULT_ACCEPTED). | */
   REBOOT_SHUTDOWN_ACTION_ENUM_END=5, /*  | */
} REBOOT_SHUTDOWN_ACTION;
#endif

/** @brief Specifies the conditions under which the MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN command should be accepted. */
#ifndef HAVE_ENUM_REBOOT_SHUTDOWN_CONDITIONS
#define HAVE_ENUM_REBOOT_SHUTDOWN_CONDITIONS
typedef enum REBOOT_SHUTDOWN_CONDITIONS
{
   REBOOT_SHUTDOWN_CONDITIONS_SAFETY_INTERLOCKED=0, /* Reboot/Shutdown only if allowed by safety checks, such as being landed. | */
   REBOOT_SHUTDOWN_CONDITIONS_FORCE=20190226, /* Force reboot/shutdown of the autopilot/component regardless of system state. | */
   REBOOT_SHUTDOWN_CONDITIONS_ENUM_END=20190227, /*  | */
} REBOOT_SHUTDOWN_CONDITIONS;
#endif

/** @brief Specifies the datatype of a MAVLink parameter. */
#ifndef HAVE_ENUM_MAV_PARAM_TYPE
#define HAVE_ENUM_MAV_PARAM_TYPE
typedef enum MAV_PARAM_TYPE
{
   MAV_PARAM_TYPE_UINT8=1, /* 8-bit unsigned integer | */
   MAV_PARAM_TYPE_INT8=2, /* 8-bit signed integer | */
   MAV_PARAM_TYPE_UINT16=3, /* 16-bit unsigned integer | */
   MAV_PARAM_TYPE_INT16=4, /* 16-bit signed integer | */
   MAV_PARAM_TYPE_UINT32=5, /* 32-bit unsigned integer | */
   MAV_PARAM_TYPE_INT32=6, /* 32-bit signed integer | */
   MAV_PARAM_TYPE_UINT64=7, /* 64-bit unsigned integer | */
   MAV_PARAM_TYPE_INT64=8, /* 64-bit signed integer | */
   MAV_PARAM_TYPE_REAL32=9, /* 32-bit floating-point | */
   MAV_PARAM_TYPE_REAL64=10, /* 64-bit floating-point | */
   MAV_PARAM_TYPE_ENUM_END=11, /*  | */
} MAV_PARAM_TYPE;
#endif

/** @brief Parameter protocol error types (see PARAM_ERROR). */
#ifndef HAVE_ENUM_MAV_PARAM_ERROR
#define HAVE_ENUM_MAV_PARAM_ERROR
typedef enum MAV_PARAM_ERROR
{
   MAV_PARAM_ERROR_NO_ERROR=0, /* No error occurred (not expected in PARAM_ERROR but may be used in future implementations. | */
   MAV_PARAM_ERROR_DOES_NOT_EXIST=1, /* Parameter does not exist | */
   MAV_PARAM_ERROR_VALUE_OUT_OF_RANGE=2, /* Parameter value does not fit within accepted range | */
   MAV_PARAM_ERROR_PERMISSION_DENIED=3, /* Caller is not permitted to set the value of this parameter | */
   MAV_PARAM_ERROR_COMPONENT_NOT_FOUND=4, /* Unknown component specified | */
   MAV_PARAM_ERROR_READ_ONLY=5, /* Parameter is read-only | */
   MAV_PARAM_ERROR_ENUM_END=6, /*  | */
} MAV_PARAM_ERROR;
#endif

/** @brief Specifies the datatype of a MAVLink extended parameter. */
#ifndef HAVE_ENUM_MAV_PARAM_EXT_TYPE
#define HAVE_ENUM_MAV_PARAM_EXT_TYPE
typedef enum MAV_PARAM_EXT_TYPE
{
   MAV_PARAM_EXT_TYPE_UINT8=1, /* 8-bit unsigned integer | */
   MAV_PARAM_EXT_TYPE_INT8=2, /* 8-bit signed integer | */
   MAV_PARAM_EXT_TYPE_UINT16=3, /* 16-bit unsigned integer | */
   MAV_PARAM_EXT_TYPE_INT16=4, /* 16-bit signed integer | */
   MAV_PARAM_EXT_TYPE_UINT32=5, /* 32-bit unsigned integer | */
   MAV_PARAM_EXT_TYPE_INT32=6, /* 32-bit signed integer | */
   MAV_PARAM_EXT_TYPE_UINT64=7, /* 64-bit unsigned integer | */
   MAV_PARAM_EXT_TYPE_INT64=8, /* 64-bit signed integer | */
   MAV_PARAM_EXT_TYPE_REAL32=9, /* 32-bit floating-point | */
   MAV_PARAM_EXT_TYPE_REAL64=10, /* 64-bit floating-point | */
   MAV_PARAM_EXT_TYPE_CUSTOM=11, /* Custom Type | */
   MAV_PARAM_EXT_TYPE_ENUM_END=12, /*  | */
} MAV_PARAM_EXT_TYPE;
#endif

/** @brief Result from a MAVLink command (MAV_CMD) */
#ifndef HAVE_ENUM_MAV_RESULT
#define HAVE_ENUM_MAV_RESULT
typedef enum MAV_RESULT
{
   MAV_RESULT_ACCEPTED=0, /* Command is valid (is supported and has valid parameters), and was executed. | */
   MAV_RESULT_TEMPORARILY_REJECTED=1, /* Command is valid, but cannot be executed at this time. This is used to indicate a problem that should be fixed just by waiting (e.g. a state machine is busy, can't arm because have not got GPS lock, etc.). Retrying later should work. | */
   MAV_RESULT_DENIED=2, /* Command is invalid (is supported but has invalid parameters). Retrying same command and parameters will not work. | */
   MAV_RESULT_UNSUPPORTED=3, /* Command is not supported (unknown). | */
   MAV_RESULT_FAILED=4, /* Command is valid, but execution has failed. This is used to indicate any non-temporary or unexpected problem, i.e. any problem that must be fixed before the command can succeed/be retried. For example, attempting to write a file when out of memory, attempting to arm when sensors are not calibrated, etc. | */
   MAV_RESULT_IN_PROGRESS=5, /* Command is valid and is being executed. This will be followed by further progress updates, i.e. the component may send further COMMAND_ACK messages with result MAV_RESULT_IN_PROGRESS (at a rate decided by the implementation), and must terminate by sending a COMMAND_ACK message with final result of the operation. The COMMAND_ACK.progress field can be used to indicate the progress of the operation. | */
   MAV_RESULT_CANCELLED=6, /* Command has been cancelled (as a result of receiving a COMMAND_CANCEL message). | */
   MAV_RESULT_COMMAND_LONG_ONLY=7, /* Command is only accepted when sent as a COMMAND_LONG. | */
   MAV_RESULT_COMMAND_INT_ONLY=8, /* Command is only accepted when sent as a COMMAND_INT. | */
   MAV_RESULT_COMMAND_UNSUPPORTED_MAV_FRAME=9, /* Command is invalid because a frame is required and the specified frame is not supported. | */
   MAV_RESULT_NOT_IN_CONTROL=10, /* Command has been rejected because source system is not in control of the target system/component. | */
   MAV_RESULT_ENUM_END=11, /*  | */
} MAV_RESULT;
#endif

/** @brief Indicates the severity level, generally used for status messages to indicate their relative urgency. Based on RFC-5424 using expanded definitions at: http://www.kiwisyslog.com/kb/info:-syslog-message-levels/. */
#ifndef HAVE_ENUM_MAV_SEVERITY
#define HAVE_ENUM_MAV_SEVERITY
typedef enum MAV_SEVERITY
{
   MAV_SEVERITY_EMERGENCY=0, /* System is unusable. This is a "panic" condition. | */
   MAV_SEVERITY_ALERT=1, /* Action should be taken immediately. Indicates error in non-critical systems. | */
   MAV_SEVERITY_CRITICAL=2, /* Action must be taken immediately. Indicates failure in a primary system. | */
   MAV_SEVERITY_ERROR=3, /* Indicates an error in secondary/redundant systems. | */
   MAV_SEVERITY_WARNING=4, /* Indicates about a possible future error if this is not resolved within a given timeframe. Example would be a low battery warning. | */
   MAV_SEVERITY_NOTICE=5, /* An unusual event has occurred, though not an error condition. This should be investigated for the root cause. | */
   MAV_SEVERITY_INFO=6, /* Normal operational messages. Useful for logging. No action is required for these messages. | */
   MAV_SEVERITY_DEBUG=7, /* Useful non-operational messages that can assist in debugging. These should not occur during normal operation. | */
   MAV_SEVERITY_ENUM_END=8, /*  | */
} MAV_SEVERITY;
#endif

/** @brief Enumeration for battery charge states. */
#ifndef HAVE_ENUM_MAV_BATTERY_CHARGE_STATE
#define HAVE_ENUM_MAV_BATTERY_CHARGE_STATE
typedef enum MAV_BATTERY_CHARGE_STATE
{
   MAV_BATTERY_CHARGE_STATE_UNDEFINED=0, /* Low battery state is not provided | */
   MAV_BATTERY_CHARGE_STATE_OK=1, /* Battery is not in low state. Normal operation. | */
   MAV_BATTERY_CHARGE_STATE_LOW=2, /* Battery state is low, warn and monitor close. | */
   MAV_BATTERY_CHARGE_STATE_CRITICAL=3, /* Battery state is critical, return or abort immediately. | */
   MAV_BATTERY_CHARGE_STATE_EMERGENCY=4, /* Battery state is too low for ordinary abort sequence. Perform fastest possible emergency stop to prevent damage. | */
   MAV_BATTERY_CHARGE_STATE_FAILED=5, /* Battery failed, damage unavoidable. Possible causes (faults) are listed in MAV_BATTERY_FAULT. | */
   MAV_BATTERY_CHARGE_STATE_UNHEALTHY=6, /* Battery is diagnosed to be defective or an error occurred, usage is discouraged / prohibited. Possible causes (faults) are listed in MAV_BATTERY_FAULT. | */
   MAV_BATTERY_CHARGE_STATE_CHARGING=7, /* Battery is charging. | */
   MAV_BATTERY_CHARGE_STATE_ENUM_END=8, /*  | */
} MAV_BATTERY_CHARGE_STATE;
#endif

/** @brief Smart battery supply status/fault flags (bitmask) for health indication. The battery must also report either MAV_BATTERY_CHARGE_STATE_FAILED or MAV_BATTERY_CHARGE_STATE_UNHEALTHY if any of these are set. */
#ifndef HAVE_ENUM_MAV_BATTERY_FAULT
#define HAVE_ENUM_MAV_BATTERY_FAULT
typedef enum MAV_BATTERY_FAULT
{
   MAV_BATTERY_FAULT_DEEP_DISCHARGE=1, /* Battery has deep discharged. | */
   MAV_BATTERY_FAULT_SPIKES=2, /* Voltage spikes. | */
   MAV_BATTERY_FAULT_CELL_FAIL=4, /* One or more cells have failed. Battery should also report MAV_BATTERY_CHARGE_STATE_FAILE (and should not be used). | */
   MAV_BATTERY_FAULT_OVER_CURRENT=8, /* Over-current fault. | */
   MAV_BATTERY_FAULT_OVER_TEMPERATURE=16, /* Over-temperature fault. | */
   MAV_BATTERY_FAULT_UNDER_TEMPERATURE=32, /* Under-temperature fault. | */
   MAV_BATTERY_FAULT_INCOMPATIBLE_VOLTAGE=64, /* Vehicle voltage is not compatible with this battery (batteries on same power rail should have similar voltage). | */
   MAV_BATTERY_FAULT_INCOMPATIBLE_FIRMWARE=128, /* Battery firmware is not compatible with current autopilot firmware. | */
   BATTERY_FAULT_INCOMPATIBLE_CELLS_CONFIGURATION=256, /* Battery is not compatible due to cell configuration (e.g. 5s1p when vehicle requires 6s). | */
   MAV_BATTERY_FAULT_ENUM_END=257, /*  | */
} MAV_BATTERY_FAULT;
#endif

/** @brief Type of GPS fix */
#ifndef HAVE_ENUM_GPS_FIX_TYPE
#define HAVE_ENUM_GPS_FIX_TYPE
typedef enum GPS_FIX_TYPE
{
   GPS_FIX_TYPE_NO_GPS=0, /* No GPS connected | */
   GPS_FIX_TYPE_NO_FIX=1, /* No position information, GPS is connected | */
   GPS_FIX_TYPE_2D_FIX=2, /* 2D position | */
   GPS_FIX_TYPE_3D_FIX=3, /* 3D position | */
   GPS_FIX_TYPE_DGPS=4, /* DGPS/SBAS aided 3D position | */
   GPS_FIX_TYPE_RTK_FLOAT=5, /* RTK float, 3D position | */
   GPS_FIX_TYPE_RTK_FIXED=6, /* RTK Fixed, 3D position | */
   GPS_FIX_TYPE_STATIC=7, /* Static fixed, typically used for base stations | */
   GPS_FIX_TYPE_PPP=8, /* PPP, 3D position. | */
   GPS_FIX_TYPE_ENUM_END=9, /*  | */
} GPS_FIX_TYPE;
#endif

/** @brief Result from PARAM_EXT_SET message. */
#ifndef HAVE_ENUM_PARAM_ACK
#define HAVE_ENUM_PARAM_ACK
typedef enum PARAM_ACK
{
   PARAM_ACK_ACCEPTED=0, /* Parameter value ACCEPTED and SET | */
   PARAM_ACK_VALUE_UNSUPPORTED=1, /* Parameter value UNKNOWN/UNSUPPORTED | */
   PARAM_ACK_FAILED=2, /* Parameter failed to set | */
   PARAM_ACK_IN_PROGRESS=3, /* Parameter value received but not yet set/accepted. A subsequent PARAM_EXT_ACK with the final result will follow once operation is completed. This is returned immediately for parameters that take longer to set, indicating that the the parameter was received and does not need to be resent. | */
   PARAM_ACK_ENUM_END=4, /*  | */
} PARAM_ACK;
#endif

/** @brief Parachute actions. Trigger release and enable/disable auto-release. */
#ifndef HAVE_ENUM_PARACHUTE_ACTION
#define HAVE_ENUM_PARACHUTE_ACTION
typedef enum PARACHUTE_ACTION
{
   PARACHUTE_DISABLE=0, /* Disable auto-release of parachute (i.e. release triggered by crash detectors). | */
   PARACHUTE_ENABLE=1, /* Enable auto-release of parachute. | */
   PARACHUTE_RELEASE=2, /* Release parachute and kill motors. | */
   PARACHUTE_ACTION_ENUM_END=3, /*  | */
} PARACHUTE_ACTION;
#endif

/** @brief Tune formats (used for vehicle buzzer/tone generation). */
#ifndef HAVE_ENUM_TUNE_FORMAT
#define HAVE_ENUM_TUNE_FORMAT
typedef enum TUNE_FORMAT
{
   TUNE_FORMAT_QBASIC1_1=1, /* Format is QBasic 1.1 Play: https://www.qbasic.net/en/reference/qb11/Statement/PLAY-006.htm. | */
   TUNE_FORMAT_MML_MODERN=2, /* Format is Modern Music Markup Language (MML): https://en.wikipedia.org/wiki/Music_Macro_Language#Modern_MML. | */
   TUNE_FORMAT_ENUM_END=3, /*  | */
} TUNE_FORMAT;
#endif

/** @brief Reason for an event error response. */
#ifndef HAVE_ENUM_MAV_EVENT_ERROR_REASON
#define HAVE_ENUM_MAV_EVENT_ERROR_REASON
typedef enum MAV_EVENT_ERROR_REASON
{
   MAV_EVENT_ERROR_REASON_UNAVAILABLE=0, /* The requested event is not available (anymore). | */
   MAV_EVENT_ERROR_REASON_ENUM_END=1, /*  | */
} MAV_EVENT_ERROR_REASON;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_sys_status.h"
#include "./mavlink_msg_system_time.h"
#include "./mavlink_msg_ping.h"
#include "./mavlink_msg_set_mode.h"
#include "./mavlink_msg_param_request_read.h"
#include "./mavlink_msg_param_request_list.h"
#include "./mavlink_msg_param_value.h"
#include "./mavlink_msg_param_set.h"
#include "./mavlink_msg_gps_raw_int.h"
#include "./mavlink_msg_gps_status.h"
#include "./mavlink_msg_raw_imu.h"
#include "./mavlink_msg_raw_pressure.h"
#include "./mavlink_msg_attitude.h"
#include "./mavlink_msg_attitude_quaternion.h"
#include "./mavlink_msg_servo_output_raw.h"
#include "./mavlink_msg_command_int.h"
#include "./mavlink_msg_command_long.h"
#include "./mavlink_msg_command_ack.h"
#include "./mavlink_msg_command_cancel.h"
#include "./mavlink_msg_sim_state.h"
#include "./mavlink_msg_timesync.h"
#include "./mavlink_msg_camera_trigger.h"
#include "./mavlink_msg_hil_state.h"
#include "./mavlink_msg_hil_gps.h"
#include "./mavlink_msg_hil_state_quaternion.h"
#include "./mavlink_msg_hil_rc_inputs_raw.h"
#include "./mavlink_msg_log_request_list.h"
#include "./mavlink_msg_log_entry.h"
#include "./mavlink_msg_log_request_data.h"
#include "./mavlink_msg_log_data.h"
#include "./mavlink_msg_log_erase.h"
#include "./mavlink_msg_log_request_end.h"
#include "./mavlink_msg_message_interval.h"
#include "./mavlink_msg_storage_information.h"
#include "./mavlink_msg_wifi_config_ap.h"
#include "./mavlink_msg_play_tune_v2.h"
#include "./mavlink_msg_supported_tunes.h"
#include "./mavlink_msg_barometer_altitude.h"
#include "./mavlink_msg_combined_sensors.h"
#include "./mavlink_msg_command_short.h"

// base include
#include "../standard/standard.h"


#if MAVLINK_ROCKET_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_HEARTBEAT, MAVLINK_MESSAGE_INFO_SYS_STATUS, MAVLINK_MESSAGE_INFO_SYSTEM_TIME, MAVLINK_MESSAGE_INFO_PING, MAVLINK_MESSAGE_INFO_SET_MODE, MAVLINK_MESSAGE_INFO_PARAM_REQUEST_READ, MAVLINK_MESSAGE_INFO_PARAM_REQUEST_LIST, MAVLINK_MESSAGE_INFO_PARAM_VALUE, MAVLINK_MESSAGE_INFO_PARAM_SET, MAVLINK_MESSAGE_INFO_GPS_RAW_INT, MAVLINK_MESSAGE_INFO_GPS_STATUS, MAVLINK_MESSAGE_INFO_RAW_IMU, MAVLINK_MESSAGE_INFO_RAW_PRESSURE, MAVLINK_MESSAGE_INFO_ATTITUDE, MAVLINK_MESSAGE_INFO_ATTITUDE_QUATERNION, MAVLINK_MESSAGE_INFO_GLOBAL_POSITION_INT, MAVLINK_MESSAGE_INFO_SERVO_OUTPUT_RAW, MAVLINK_MESSAGE_INFO_COMMAND_INT, MAVLINK_MESSAGE_INFO_COMMAND_LONG, MAVLINK_MESSAGE_INFO_COMMAND_ACK, MAVLINK_MESSAGE_INFO_COMMAND_CANCEL, MAVLINK_MESSAGE_INFO_HIL_STATE, MAVLINK_MESSAGE_INFO_HIL_RC_INPUTS_RAW, MAVLINK_MESSAGE_INFO_SIM_STATE, MAVLINK_MESSAGE_INFO_TIMESYNC, MAVLINK_MESSAGE_INFO_CAMERA_TRIGGER, MAVLINK_MESSAGE_INFO_HIL_GPS, MAVLINK_MESSAGE_INFO_HIL_STATE_QUATERNION, MAVLINK_MESSAGE_INFO_LOG_REQUEST_LIST, MAVLINK_MESSAGE_INFO_LOG_ENTRY, MAVLINK_MESSAGE_INFO_LOG_REQUEST_DATA, MAVLINK_MESSAGE_INFO_LOG_DATA, MAVLINK_MESSAGE_INFO_LOG_ERASE, MAVLINK_MESSAGE_INFO_LOG_REQUEST_END, MAVLINK_MESSAGE_INFO_AUTOPILOT_VERSION, MAVLINK_MESSAGE_INFO_MESSAGE_INTERVAL, MAVLINK_MESSAGE_INFO_STORAGE_INFORMATION, MAVLINK_MESSAGE_INFO_WIFI_CONFIG_AP, MAVLINK_MESSAGE_INFO_PROTOCOL_VERSION, MAVLINK_MESSAGE_INFO_PLAY_TUNE_V2, MAVLINK_MESSAGE_INFO_SUPPORTED_TUNES, MAVLINK_MESSAGE_INFO_BAROMETER_ALTITUDE, MAVLINK_MESSAGE_INFO_COMBINED_SENSORS, MAVLINK_MESSAGE_INFO_COMMAND_SHORT}
# define MAVLINK_MESSAGE_NAMES {{ "ATTITUDE", 30 }, { "ATTITUDE_QUATERNION", 31 }, { "AUTOPILOT_VERSION", 148 }, { "BAROMETER_ALTITUDE", 15000 }, { "CAMERA_TRIGGER", 112 }, { "COMBINED_SENSORS", 15001 }, { "COMMAND_ACK", 77 }, { "COMMAND_CANCEL", 80 }, { "COMMAND_INT", 75 }, { "COMMAND_LONG", 76 }, { "COMMAND_SHORT", 15002 }, { "GLOBAL_POSITION_INT", 33 }, { "GPS_RAW_INT", 24 }, { "GPS_STATUS", 25 }, { "HEARTBEAT", 0 }, { "HIL_GPS", 113 }, { "HIL_RC_INPUTS_RAW", 92 }, { "HIL_STATE", 90 }, { "HIL_STATE_QUATERNION", 115 }, { "LOG_DATA", 120 }, { "LOG_ENTRY", 118 }, { "LOG_ERASE", 121 }, { "LOG_REQUEST_DATA", 119 }, { "LOG_REQUEST_END", 122 }, { "LOG_REQUEST_LIST", 117 }, { "MESSAGE_INTERVAL", 244 }, { "PARAM_REQUEST_LIST", 21 }, { "PARAM_REQUEST_READ", 20 }, { "PARAM_SET", 23 }, { "PARAM_VALUE", 22 }, { "PING", 4 }, { "PLAY_TUNE_V2", 400 }, { "PROTOCOL_VERSION", 300 }, { "RAW_IMU", 27 }, { "RAW_PRESSURE", 28 }, { "SERVO_OUTPUT_RAW", 36 }, { "SET_MODE", 11 }, { "SIM_STATE", 108 }, { "STORAGE_INFORMATION", 261 }, { "SUPPORTED_TUNES", 401 }, { "SYSTEM_TIME", 2 }, { "SYS_STATUS", 1 }, { "TIMESYNC", 111 }, { "WIFI_CONFIG_AP", 299 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_ROCKET_H
