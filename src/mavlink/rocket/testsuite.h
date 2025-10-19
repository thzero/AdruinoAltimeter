/** @file
 *    @brief MAVLink comm protocol testsuite generated from rocket.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef ROCKET_TESTSUITE_H
#define ROCKET_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_standard(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_rocket(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_standard(system_id, component_id, last_msg);
    mavlink_test_rocket(system_id, component_id, last_msg);
}
#endif

#include "../standard/testsuite.h"


static void mavlink_test_sys_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SYS_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_sys_status_t packet_in = {
        963497464,963497672,963497880,17859,17963,18067,18171,18275,18379,18483,18587,18691,223,963499076,963499284,963499492
    };
    mavlink_sys_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.onboard_control_sensors_present = packet_in.onboard_control_sensors_present;
        packet1.onboard_control_sensors_enabled = packet_in.onboard_control_sensors_enabled;
        packet1.onboard_control_sensors_health = packet_in.onboard_control_sensors_health;
        packet1.load = packet_in.load;
        packet1.voltage_battery = packet_in.voltage_battery;
        packet1.current_battery = packet_in.current_battery;
        packet1.drop_rate_comm = packet_in.drop_rate_comm;
        packet1.errors_comm = packet_in.errors_comm;
        packet1.errors_count1 = packet_in.errors_count1;
        packet1.errors_count2 = packet_in.errors_count2;
        packet1.errors_count3 = packet_in.errors_count3;
        packet1.errors_count4 = packet_in.errors_count4;
        packet1.battery_remaining = packet_in.battery_remaining;
        packet1.onboard_control_sensors_present_extended = packet_in.onboard_control_sensors_present_extended;
        packet1.onboard_control_sensors_enabled_extended = packet_in.onboard_control_sensors_enabled_extended;
        packet1.onboard_control_sensors_health_extended = packet_in.onboard_control_sensors_health_extended;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SYS_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SYS_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sys_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_sys_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sys_status_pack(system_id, component_id, &msg , packet1.onboard_control_sensors_present , packet1.onboard_control_sensors_enabled , packet1.onboard_control_sensors_health , packet1.load , packet1.voltage_battery , packet1.current_battery , packet1.battery_remaining , packet1.drop_rate_comm , packet1.errors_comm , packet1.errors_count1 , packet1.errors_count2 , packet1.errors_count3 , packet1.errors_count4 , packet1.onboard_control_sensors_present_extended , packet1.onboard_control_sensors_enabled_extended , packet1.onboard_control_sensors_health_extended );
    mavlink_msg_sys_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sys_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.onboard_control_sensors_present , packet1.onboard_control_sensors_enabled , packet1.onboard_control_sensors_health , packet1.load , packet1.voltage_battery , packet1.current_battery , packet1.battery_remaining , packet1.drop_rate_comm , packet1.errors_comm , packet1.errors_count1 , packet1.errors_count2 , packet1.errors_count3 , packet1.errors_count4 , packet1.onboard_control_sensors_present_extended , packet1.onboard_control_sensors_enabled_extended , packet1.onboard_control_sensors_health_extended );
    mavlink_msg_sys_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_sys_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sys_status_send(MAVLINK_COMM_1 , packet1.onboard_control_sensors_present , packet1.onboard_control_sensors_enabled , packet1.onboard_control_sensors_health , packet1.load , packet1.voltage_battery , packet1.current_battery , packet1.battery_remaining , packet1.drop_rate_comm , packet1.errors_comm , packet1.errors_count1 , packet1.errors_count2 , packet1.errors_count3 , packet1.errors_count4 , packet1.onboard_control_sensors_present_extended , packet1.onboard_control_sensors_enabled_extended , packet1.onboard_control_sensors_health_extended );
    mavlink_msg_sys_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SYS_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SYS_STATUS) != NULL);
#endif
}

static void mavlink_test_system_time(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SYSTEM_TIME >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_system_time_t packet_in = {
        93372036854775807ULL,963497880
    };
    mavlink_system_time_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_unix_usec = packet_in.time_unix_usec;
        packet1.time_boot_ms = packet_in.time_boot_ms;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SYSTEM_TIME_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SYSTEM_TIME_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_system_time_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_system_time_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_system_time_pack(system_id, component_id, &msg , packet1.time_unix_usec , packet1.time_boot_ms );
    mavlink_msg_system_time_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_system_time_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_unix_usec , packet1.time_boot_ms );
    mavlink_msg_system_time_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_system_time_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_system_time_send(MAVLINK_COMM_1 , packet1.time_unix_usec , packet1.time_boot_ms );
    mavlink_msg_system_time_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SYSTEM_TIME") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SYSTEM_TIME) != NULL);
#endif
}

static void mavlink_test_ping(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PING >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_ping_t packet_in = {
        93372036854775807ULL,963497880,41,108
    };
    mavlink_ping_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.seq = packet_in.seq;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PING_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PING_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_ping_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_ping_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_ping_pack(system_id, component_id, &msg , packet1.time_usec , packet1.seq , packet1.target_system , packet1.target_component );
    mavlink_msg_ping_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_ping_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.seq , packet1.target_system , packet1.target_component );
    mavlink_msg_ping_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_ping_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_ping_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.seq , packet1.target_system , packet1.target_component );
    mavlink_msg_ping_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PING") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PING) != NULL);
#endif
}

static void mavlink_test_set_mode(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SET_MODE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_set_mode_t packet_in = {
        963497464,17,84
    };
    mavlink_set_mode_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.custom_mode = packet_in.custom_mode;
        packet1.target_system = packet_in.target_system;
        packet1.base_mode = packet_in.base_mode;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SET_MODE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SET_MODE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_set_mode_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_set_mode_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_set_mode_pack(system_id, component_id, &msg , packet1.target_system , packet1.base_mode , packet1.custom_mode );
    mavlink_msg_set_mode_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_set_mode_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.base_mode , packet1.custom_mode );
    mavlink_msg_set_mode_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_set_mode_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_set_mode_send(MAVLINK_COMM_1 , packet1.target_system , packet1.base_mode , packet1.custom_mode );
    mavlink_msg_set_mode_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SET_MODE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SET_MODE) != NULL);
#endif
}

static void mavlink_test_param_request_read(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PARAM_REQUEST_READ >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_param_request_read_t packet_in = {
        17235,139,206,"EFGHIJKLMNOPQRS"
    };
    mavlink_param_request_read_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.param_index = packet_in.param_index;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        mav_array_memcpy(packet1.param_id, packet_in.param_id, sizeof(char)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PARAM_REQUEST_READ_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PARAM_REQUEST_READ_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_request_read_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_param_request_read_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_request_read_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.param_id , packet1.param_index );
    mavlink_msg_param_request_read_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_request_read_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.param_id , packet1.param_index );
    mavlink_msg_param_request_read_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_param_request_read_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_request_read_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.param_id , packet1.param_index );
    mavlink_msg_param_request_read_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PARAM_REQUEST_READ") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PARAM_REQUEST_READ) != NULL);
#endif
}

static void mavlink_test_param_request_list(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PARAM_REQUEST_LIST >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_param_request_list_t packet_in = {
        5,72
    };
    mavlink_param_request_list_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PARAM_REQUEST_LIST_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PARAM_REQUEST_LIST_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_request_list_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_param_request_list_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_request_list_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component );
    mavlink_msg_param_request_list_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_request_list_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component );
    mavlink_msg_param_request_list_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_param_request_list_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_request_list_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component );
    mavlink_msg_param_request_list_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PARAM_REQUEST_LIST") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PARAM_REQUEST_LIST) != NULL);
#endif
}

static void mavlink_test_param_value(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PARAM_VALUE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_param_value_t packet_in = {
        17.0,17443,17547,"IJKLMNOPQRSTUVW",77
    };
    mavlink_param_value_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.param_value = packet_in.param_value;
        packet1.param_count = packet_in.param_count;
        packet1.param_index = packet_in.param_index;
        packet1.param_type = packet_in.param_type;
        
        mav_array_memcpy(packet1.param_id, packet_in.param_id, sizeof(char)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PARAM_VALUE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PARAM_VALUE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_value_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_param_value_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_value_pack(system_id, component_id, &msg , packet1.param_id , packet1.param_value , packet1.param_type , packet1.param_count , packet1.param_index );
    mavlink_msg_param_value_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_value_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.param_id , packet1.param_value , packet1.param_type , packet1.param_count , packet1.param_index );
    mavlink_msg_param_value_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_param_value_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_value_send(MAVLINK_COMM_1 , packet1.param_id , packet1.param_value , packet1.param_type , packet1.param_count , packet1.param_index );
    mavlink_msg_param_value_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PARAM_VALUE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PARAM_VALUE) != NULL);
#endif
}

static void mavlink_test_param_set(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PARAM_SET >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_param_set_t packet_in = {
        17.0,17,84,"GHIJKLMNOPQRSTU",199
    };
    mavlink_param_set_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.param_value = packet_in.param_value;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        packet1.param_type = packet_in.param_type;
        
        mav_array_memcpy(packet1.param_id, packet_in.param_id, sizeof(char)*16);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PARAM_SET_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PARAM_SET_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_set_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_param_set_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_set_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.param_id , packet1.param_value , packet1.param_type );
    mavlink_msg_param_set_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_set_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.param_id , packet1.param_value , packet1.param_type );
    mavlink_msg_param_set_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_param_set_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_param_set_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.param_id , packet1.param_value , packet1.param_type );
    mavlink_msg_param_set_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PARAM_SET") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PARAM_SET) != NULL);
#endif
}

static void mavlink_test_gps_raw_int(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_GPS_RAW_INT >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_gps_raw_int_t packet_in = {
        93372036854775807ULL,963497880,963498088,963498296,18275,18379,18483,18587,89,156,963499024,963499232,963499440,963499648,963499856,19835
    };
    mavlink_gps_raw_int_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.eph = packet_in.eph;
        packet1.epv = packet_in.epv;
        packet1.vel = packet_in.vel;
        packet1.cog = packet_in.cog;
        packet1.fix_type = packet_in.fix_type;
        packet1.satellites_visible = packet_in.satellites_visible;
        packet1.alt_ellipsoid = packet_in.alt_ellipsoid;
        packet1.h_acc = packet_in.h_acc;
        packet1.v_acc = packet_in.v_acc;
        packet1.vel_acc = packet_in.vel_acc;
        packet1.hdg_acc = packet_in.hdg_acc;
        packet1.yaw = packet_in.yaw;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_GPS_RAW_INT_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_GPS_RAW_INT_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gps_raw_int_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_gps_raw_int_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gps_raw_int_pack(system_id, component_id, &msg , packet1.time_usec , packet1.fix_type , packet1.lat , packet1.lon , packet1.alt , packet1.eph , packet1.epv , packet1.vel , packet1.cog , packet1.satellites_visible , packet1.alt_ellipsoid , packet1.h_acc , packet1.v_acc , packet1.vel_acc , packet1.hdg_acc , packet1.yaw );
    mavlink_msg_gps_raw_int_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gps_raw_int_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.fix_type , packet1.lat , packet1.lon , packet1.alt , packet1.eph , packet1.epv , packet1.vel , packet1.cog , packet1.satellites_visible , packet1.alt_ellipsoid , packet1.h_acc , packet1.v_acc , packet1.vel_acc , packet1.hdg_acc , packet1.yaw );
    mavlink_msg_gps_raw_int_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_gps_raw_int_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gps_raw_int_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.fix_type , packet1.lat , packet1.lon , packet1.alt , packet1.eph , packet1.epv , packet1.vel , packet1.cog , packet1.satellites_visible , packet1.alt_ellipsoid , packet1.h_acc , packet1.v_acc , packet1.vel_acc , packet1.hdg_acc , packet1.yaw );
    mavlink_msg_gps_raw_int_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("GPS_RAW_INT") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_GPS_RAW_INT) != NULL);
#endif
}

static void mavlink_test_gps_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_GPS_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_gps_status_t packet_in = {
        5,{ 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91 },{ 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151 },{ 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211 },{ 252, 253, 254, 255, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },{ 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75 }
    };
    mavlink_gps_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.satellites_visible = packet_in.satellites_visible;
        
        mav_array_memcpy(packet1.satellite_prn, packet_in.satellite_prn, sizeof(uint8_t)*20);
        mav_array_memcpy(packet1.satellite_used, packet_in.satellite_used, sizeof(uint8_t)*20);
        mav_array_memcpy(packet1.satellite_elevation, packet_in.satellite_elevation, sizeof(uint8_t)*20);
        mav_array_memcpy(packet1.satellite_azimuth, packet_in.satellite_azimuth, sizeof(uint8_t)*20);
        mav_array_memcpy(packet1.satellite_snr, packet_in.satellite_snr, sizeof(uint8_t)*20);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_GPS_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_GPS_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gps_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_gps_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gps_status_pack(system_id, component_id, &msg , packet1.satellites_visible , packet1.satellite_prn , packet1.satellite_used , packet1.satellite_elevation , packet1.satellite_azimuth , packet1.satellite_snr );
    mavlink_msg_gps_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gps_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.satellites_visible , packet1.satellite_prn , packet1.satellite_used , packet1.satellite_elevation , packet1.satellite_azimuth , packet1.satellite_snr );
    mavlink_msg_gps_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_gps_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_gps_status_send(MAVLINK_COMM_1 , packet1.satellites_visible , packet1.satellite_prn , packet1.satellite_used , packet1.satellite_elevation , packet1.satellite_azimuth , packet1.satellite_snr );
    mavlink_msg_gps_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("GPS_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_GPS_STATUS) != NULL);
#endif
}

static void mavlink_test_raw_imu(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_RAW_IMU >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_raw_imu_t packet_in = {
        93372036854775807ULL,17651,17755,17859,17963,18067,18171,18275,18379,18483,211,18639
    };
    mavlink_raw_imu_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.xacc = packet_in.xacc;
        packet1.yacc = packet_in.yacc;
        packet1.zacc = packet_in.zacc;
        packet1.xgyro = packet_in.xgyro;
        packet1.ygyro = packet_in.ygyro;
        packet1.zgyro = packet_in.zgyro;
        packet1.xmag = packet_in.xmag;
        packet1.ymag = packet_in.ymag;
        packet1.zmag = packet_in.zmag;
        packet1.id = packet_in.id;
        packet1.temperature = packet_in.temperature;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_RAW_IMU_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_RAW_IMU_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_raw_imu_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_raw_imu_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_raw_imu_pack(system_id, component_id, &msg , packet1.time_usec , packet1.xacc , packet1.yacc , packet1.zacc , packet1.xgyro , packet1.ygyro , packet1.zgyro , packet1.xmag , packet1.ymag , packet1.zmag , packet1.id , packet1.temperature );
    mavlink_msg_raw_imu_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_raw_imu_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.xacc , packet1.yacc , packet1.zacc , packet1.xgyro , packet1.ygyro , packet1.zgyro , packet1.xmag , packet1.ymag , packet1.zmag , packet1.id , packet1.temperature );
    mavlink_msg_raw_imu_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_raw_imu_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_raw_imu_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.xacc , packet1.yacc , packet1.zacc , packet1.xgyro , packet1.ygyro , packet1.zgyro , packet1.xmag , packet1.ymag , packet1.zmag , packet1.id , packet1.temperature );
    mavlink_msg_raw_imu_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("RAW_IMU") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_RAW_IMU) != NULL);
#endif
}

static void mavlink_test_raw_pressure(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_RAW_PRESSURE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_raw_pressure_t packet_in = {
        93372036854775807ULL,17651,17755,17859,17963
    };
    mavlink_raw_pressure_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.press_abs = packet_in.press_abs;
        packet1.press_diff1 = packet_in.press_diff1;
        packet1.press_diff2 = packet_in.press_diff2;
        packet1.temperature = packet_in.temperature;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_RAW_PRESSURE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_RAW_PRESSURE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_raw_pressure_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_raw_pressure_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_raw_pressure_pack(system_id, component_id, &msg , packet1.time_usec , packet1.press_abs , packet1.press_diff1 , packet1.press_diff2 , packet1.temperature );
    mavlink_msg_raw_pressure_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_raw_pressure_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.press_abs , packet1.press_diff1 , packet1.press_diff2 , packet1.temperature );
    mavlink_msg_raw_pressure_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_raw_pressure_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_raw_pressure_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.press_abs , packet1.press_diff1 , packet1.press_diff2 , packet1.temperature );
    mavlink_msg_raw_pressure_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("RAW_PRESSURE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_RAW_PRESSURE) != NULL);
#endif
}

static void mavlink_test_attitude(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ATTITUDE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_attitude_t packet_in = {
        963497464,45.0,73.0,101.0,129.0,157.0,185.0
    };
    mavlink_attitude_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_boot_ms = packet_in.time_boot_ms;
        packet1.roll = packet_in.roll;
        packet1.pitch = packet_in.pitch;
        packet1.yaw = packet_in.yaw;
        packet1.rollspeed = packet_in.rollspeed;
        packet1.pitchspeed = packet_in.pitchspeed;
        packet1.yawspeed = packet_in.yawspeed;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ATTITUDE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ATTITUDE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_attitude_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_attitude_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_attitude_pack(system_id, component_id, &msg , packet1.time_boot_ms , packet1.roll , packet1.pitch , packet1.yaw , packet1.rollspeed , packet1.pitchspeed , packet1.yawspeed );
    mavlink_msg_attitude_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_attitude_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_boot_ms , packet1.roll , packet1.pitch , packet1.yaw , packet1.rollspeed , packet1.pitchspeed , packet1.yawspeed );
    mavlink_msg_attitude_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_attitude_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_attitude_send(MAVLINK_COMM_1 , packet1.time_boot_ms , packet1.roll , packet1.pitch , packet1.yaw , packet1.rollspeed , packet1.pitchspeed , packet1.yawspeed );
    mavlink_msg_attitude_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ATTITUDE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ATTITUDE) != NULL);
#endif
}

static void mavlink_test_attitude_quaternion(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ATTITUDE_QUATERNION >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_attitude_quaternion_t packet_in = {
        963497464,45.0,73.0,101.0,129.0,157.0,185.0,213.0,{ 241.0, 242.0, 243.0, 244.0 }
    };
    mavlink_attitude_quaternion_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_boot_ms = packet_in.time_boot_ms;
        packet1.q1 = packet_in.q1;
        packet1.q2 = packet_in.q2;
        packet1.q3 = packet_in.q3;
        packet1.q4 = packet_in.q4;
        packet1.rollspeed = packet_in.rollspeed;
        packet1.pitchspeed = packet_in.pitchspeed;
        packet1.yawspeed = packet_in.yawspeed;
        
        mav_array_memcpy(packet1.repr_offset_q, packet_in.repr_offset_q, sizeof(float)*4);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ATTITUDE_QUATERNION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ATTITUDE_QUATERNION_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_attitude_quaternion_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_attitude_quaternion_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_attitude_quaternion_pack(system_id, component_id, &msg , packet1.time_boot_ms , packet1.q1 , packet1.q2 , packet1.q3 , packet1.q4 , packet1.rollspeed , packet1.pitchspeed , packet1.yawspeed , packet1.repr_offset_q );
    mavlink_msg_attitude_quaternion_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_attitude_quaternion_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_boot_ms , packet1.q1 , packet1.q2 , packet1.q3 , packet1.q4 , packet1.rollspeed , packet1.pitchspeed , packet1.yawspeed , packet1.repr_offset_q );
    mavlink_msg_attitude_quaternion_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_attitude_quaternion_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_attitude_quaternion_send(MAVLINK_COMM_1 , packet1.time_boot_ms , packet1.q1 , packet1.q2 , packet1.q3 , packet1.q4 , packet1.rollspeed , packet1.pitchspeed , packet1.yawspeed , packet1.repr_offset_q );
    mavlink_msg_attitude_quaternion_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ATTITUDE_QUATERNION") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ATTITUDE_QUATERNION) != NULL);
#endif
}

static void mavlink_test_servo_output_raw(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERVO_OUTPUT_RAW >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_servo_output_raw_t packet_in = {
        963497464,17443,17547,17651,17755,17859,17963,18067,18171,65,18327,18431,18535,18639,18743,18847,18951,19055
    };
    mavlink_servo_output_raw_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.servo1_raw = packet_in.servo1_raw;
        packet1.servo2_raw = packet_in.servo2_raw;
        packet1.servo3_raw = packet_in.servo3_raw;
        packet1.servo4_raw = packet_in.servo4_raw;
        packet1.servo5_raw = packet_in.servo5_raw;
        packet1.servo6_raw = packet_in.servo6_raw;
        packet1.servo7_raw = packet_in.servo7_raw;
        packet1.servo8_raw = packet_in.servo8_raw;
        packet1.port = packet_in.port;
        packet1.servo9_raw = packet_in.servo9_raw;
        packet1.servo10_raw = packet_in.servo10_raw;
        packet1.servo11_raw = packet_in.servo11_raw;
        packet1.servo12_raw = packet_in.servo12_raw;
        packet1.servo13_raw = packet_in.servo13_raw;
        packet1.servo14_raw = packet_in.servo14_raw;
        packet1.servo15_raw = packet_in.servo15_raw;
        packet1.servo16_raw = packet_in.servo16_raw;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SERVO_OUTPUT_RAW_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SERVO_OUTPUT_RAW_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_servo_output_raw_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_servo_output_raw_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_servo_output_raw_pack(system_id, component_id, &msg , packet1.time_usec , packet1.port , packet1.servo1_raw , packet1.servo2_raw , packet1.servo3_raw , packet1.servo4_raw , packet1.servo5_raw , packet1.servo6_raw , packet1.servo7_raw , packet1.servo8_raw , packet1.servo9_raw , packet1.servo10_raw , packet1.servo11_raw , packet1.servo12_raw , packet1.servo13_raw , packet1.servo14_raw , packet1.servo15_raw , packet1.servo16_raw );
    mavlink_msg_servo_output_raw_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_servo_output_raw_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.port , packet1.servo1_raw , packet1.servo2_raw , packet1.servo3_raw , packet1.servo4_raw , packet1.servo5_raw , packet1.servo6_raw , packet1.servo7_raw , packet1.servo8_raw , packet1.servo9_raw , packet1.servo10_raw , packet1.servo11_raw , packet1.servo12_raw , packet1.servo13_raw , packet1.servo14_raw , packet1.servo15_raw , packet1.servo16_raw );
    mavlink_msg_servo_output_raw_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_servo_output_raw_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_servo_output_raw_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.port , packet1.servo1_raw , packet1.servo2_raw , packet1.servo3_raw , packet1.servo4_raw , packet1.servo5_raw , packet1.servo6_raw , packet1.servo7_raw , packet1.servo8_raw , packet1.servo9_raw , packet1.servo10_raw , packet1.servo11_raw , packet1.servo12_raw , packet1.servo13_raw , packet1.servo14_raw , packet1.servo15_raw , packet1.servo16_raw );
    mavlink_msg_servo_output_raw_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERVO_OUTPUT_RAW") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERVO_OUTPUT_RAW) != NULL);
#endif
}

static void mavlink_test_command_int(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_COMMAND_INT >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_command_int_t packet_in = {
        17.0,45.0,73.0,101.0,963498296,963498504,185.0,18691,223,34,101,168,235
    };
    mavlink_command_int_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.param1 = packet_in.param1;
        packet1.param2 = packet_in.param2;
        packet1.param3 = packet_in.param3;
        packet1.param4 = packet_in.param4;
        packet1.x = packet_in.x;
        packet1.y = packet_in.y;
        packet1.z = packet_in.z;
        packet1.command = packet_in.command;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        packet1.frame = packet_in.frame;
        packet1.current = packet_in.current;
        packet1.autocontinue = packet_in.autocontinue;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_COMMAND_INT_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_COMMAND_INT_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_int_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_command_int_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_int_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.frame , packet1.command , packet1.current , packet1.autocontinue , packet1.param1 , packet1.param2 , packet1.param3 , packet1.param4 , packet1.x , packet1.y , packet1.z );
    mavlink_msg_command_int_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_int_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.frame , packet1.command , packet1.current , packet1.autocontinue , packet1.param1 , packet1.param2 , packet1.param3 , packet1.param4 , packet1.x , packet1.y , packet1.z );
    mavlink_msg_command_int_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_command_int_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_int_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.frame , packet1.command , packet1.current , packet1.autocontinue , packet1.param1 , packet1.param2 , packet1.param3 , packet1.param4 , packet1.x , packet1.y , packet1.z );
    mavlink_msg_command_int_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("COMMAND_INT") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_COMMAND_INT) != NULL);
#endif
}

static void mavlink_test_command_long(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_COMMAND_LONG >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_command_long_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,185.0,18691,223,34,101
    };
    mavlink_command_long_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.param1 = packet_in.param1;
        packet1.param2 = packet_in.param2;
        packet1.param3 = packet_in.param3;
        packet1.param4 = packet_in.param4;
        packet1.param5 = packet_in.param5;
        packet1.param6 = packet_in.param6;
        packet1.param7 = packet_in.param7;
        packet1.command = packet_in.command;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        packet1.confirmation = packet_in.confirmation;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_COMMAND_LONG_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_COMMAND_LONG_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_long_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_command_long_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_long_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.command , packet1.confirmation , packet1.param1 , packet1.param2 , packet1.param3 , packet1.param4 , packet1.param5 , packet1.param6 , packet1.param7 );
    mavlink_msg_command_long_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_long_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.command , packet1.confirmation , packet1.param1 , packet1.param2 , packet1.param3 , packet1.param4 , packet1.param5 , packet1.param6 , packet1.param7 );
    mavlink_msg_command_long_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_command_long_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_long_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.command , packet1.confirmation , packet1.param1 , packet1.param2 , packet1.param3 , packet1.param4 , packet1.param5 , packet1.param6 , packet1.param7 );
    mavlink_msg_command_long_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("COMMAND_LONG") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_COMMAND_LONG) != NULL);
#endif
}

static void mavlink_test_command_ack(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_COMMAND_ACK >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_command_ack_t packet_in = {
        17235,139,206,963497672,29,96
    };
    mavlink_command_ack_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.command = packet_in.command;
        packet1.result = packet_in.result;
        packet1.progress = packet_in.progress;
        packet1.result_param2 = packet_in.result_param2;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_COMMAND_ACK_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_COMMAND_ACK_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_ack_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_command_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_ack_pack(system_id, component_id, &msg , packet1.command , packet1.result , packet1.progress , packet1.result_param2 , packet1.target_system , packet1.target_component );
    mavlink_msg_command_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_ack_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.command , packet1.result , packet1.progress , packet1.result_param2 , packet1.target_system , packet1.target_component );
    mavlink_msg_command_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_command_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_ack_send(MAVLINK_COMM_1 , packet1.command , packet1.result , packet1.progress , packet1.result_param2 , packet1.target_system , packet1.target_component );
    mavlink_msg_command_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("COMMAND_ACK") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_COMMAND_ACK) != NULL);
#endif
}

static void mavlink_test_command_cancel(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_COMMAND_CANCEL >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_command_cancel_t packet_in = {
        17235,139,206
    };
    mavlink_command_cancel_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.command = packet_in.command;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_COMMAND_CANCEL_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_COMMAND_CANCEL_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_cancel_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_command_cancel_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_cancel_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.command );
    mavlink_msg_command_cancel_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_cancel_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.command );
    mavlink_msg_command_cancel_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_command_cancel_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_command_cancel_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.command );
    mavlink_msg_command_cancel_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("COMMAND_CANCEL") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_COMMAND_CANCEL) != NULL);
#endif
}

static void mavlink_test_sim_state(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SIM_STATE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_sim_state_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,185.0,213.0,241.0,269.0,297.0,325.0,353.0,381.0,409.0,437.0,465.0,493.0,521.0,549.0,577.0,963501832,963502040
    };
    mavlink_sim_state_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.q1 = packet_in.q1;
        packet1.q2 = packet_in.q2;
        packet1.q3 = packet_in.q3;
        packet1.q4 = packet_in.q4;
        packet1.roll = packet_in.roll;
        packet1.pitch = packet_in.pitch;
        packet1.yaw = packet_in.yaw;
        packet1.xacc = packet_in.xacc;
        packet1.yacc = packet_in.yacc;
        packet1.zacc = packet_in.zacc;
        packet1.xgyro = packet_in.xgyro;
        packet1.ygyro = packet_in.ygyro;
        packet1.zgyro = packet_in.zgyro;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.std_dev_horz = packet_in.std_dev_horz;
        packet1.std_dev_vert = packet_in.std_dev_vert;
        packet1.vn = packet_in.vn;
        packet1.ve = packet_in.ve;
        packet1.vd = packet_in.vd;
        packet1.lat_int = packet_in.lat_int;
        packet1.lon_int = packet_in.lon_int;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SIM_STATE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SIM_STATE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sim_state_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_sim_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sim_state_pack(system_id, component_id, &msg , packet1.q1 , packet1.q2 , packet1.q3 , packet1.q4 , packet1.roll , packet1.pitch , packet1.yaw , packet1.xacc , packet1.yacc , packet1.zacc , packet1.xgyro , packet1.ygyro , packet1.zgyro , packet1.lat , packet1.lon , packet1.alt , packet1.std_dev_horz , packet1.std_dev_vert , packet1.vn , packet1.ve , packet1.vd , packet1.lat_int , packet1.lon_int );
    mavlink_msg_sim_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sim_state_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.q1 , packet1.q2 , packet1.q3 , packet1.q4 , packet1.roll , packet1.pitch , packet1.yaw , packet1.xacc , packet1.yacc , packet1.zacc , packet1.xgyro , packet1.ygyro , packet1.zgyro , packet1.lat , packet1.lon , packet1.alt , packet1.std_dev_horz , packet1.std_dev_vert , packet1.vn , packet1.ve , packet1.vd , packet1.lat_int , packet1.lon_int );
    mavlink_msg_sim_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_sim_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_sim_state_send(MAVLINK_COMM_1 , packet1.q1 , packet1.q2 , packet1.q3 , packet1.q4 , packet1.roll , packet1.pitch , packet1.yaw , packet1.xacc , packet1.yacc , packet1.zacc , packet1.xgyro , packet1.ygyro , packet1.zgyro , packet1.lat , packet1.lon , packet1.alt , packet1.std_dev_horz , packet1.std_dev_vert , packet1.vn , packet1.ve , packet1.vd , packet1.lat_int , packet1.lon_int );
    mavlink_msg_sim_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SIM_STATE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SIM_STATE) != NULL);
#endif
}

static void mavlink_test_timesync(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TIMESYNC >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_timesync_t packet_in = {
        93372036854775807LL,93372036854776311LL,53,120
    };
    mavlink_timesync_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.tc1 = packet_in.tc1;
        packet1.ts1 = packet_in.ts1;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TIMESYNC_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TIMESYNC_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_timesync_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_timesync_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_timesync_pack(system_id, component_id, &msg , packet1.tc1 , packet1.ts1 , packet1.target_system , packet1.target_component );
    mavlink_msg_timesync_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_timesync_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.tc1 , packet1.ts1 , packet1.target_system , packet1.target_component );
    mavlink_msg_timesync_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_timesync_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_timesync_send(MAVLINK_COMM_1 , packet1.tc1 , packet1.ts1 , packet1.target_system , packet1.target_component );
    mavlink_msg_timesync_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TIMESYNC") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TIMESYNC) != NULL);
#endif
}

static void mavlink_test_camera_trigger(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_CAMERA_TRIGGER >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_camera_trigger_t packet_in = {
        93372036854775807ULL,963497880
    };
    mavlink_camera_trigger_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.seq = packet_in.seq;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_CAMERA_TRIGGER_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_CAMERA_TRIGGER_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_camera_trigger_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_camera_trigger_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_camera_trigger_pack(system_id, component_id, &msg , packet1.time_usec , packet1.seq );
    mavlink_msg_camera_trigger_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_camera_trigger_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.seq );
    mavlink_msg_camera_trigger_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_camera_trigger_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_camera_trigger_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.seq );
    mavlink_msg_camera_trigger_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("CAMERA_TRIGGER") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_CAMERA_TRIGGER) != NULL);
#endif
}

static void mavlink_test_hil_state(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_HIL_STATE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_hil_state_t packet_in = {
        93372036854775807ULL,73.0,101.0,129.0,157.0,185.0,213.0,963499128,963499336,963499544,19523,19627,19731,19835,19939,20043
    };
    mavlink_hil_state_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.roll = packet_in.roll;
        packet1.pitch = packet_in.pitch;
        packet1.yaw = packet_in.yaw;
        packet1.rollspeed = packet_in.rollspeed;
        packet1.pitchspeed = packet_in.pitchspeed;
        packet1.yawspeed = packet_in.yawspeed;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.xacc = packet_in.xacc;
        packet1.yacc = packet_in.yacc;
        packet1.zacc = packet_in.zacc;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_HIL_STATE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_HIL_STATE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_state_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_hil_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_state_pack(system_id, component_id, &msg , packet1.time_usec , packet1.roll , packet1.pitch , packet1.yaw , packet1.rollspeed , packet1.pitchspeed , packet1.yawspeed , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.xacc , packet1.yacc , packet1.zacc );
    mavlink_msg_hil_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_state_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.roll , packet1.pitch , packet1.yaw , packet1.rollspeed , packet1.pitchspeed , packet1.yawspeed , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.xacc , packet1.yacc , packet1.zacc );
    mavlink_msg_hil_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_hil_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_state_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.roll , packet1.pitch , packet1.yaw , packet1.rollspeed , packet1.pitchspeed , packet1.yawspeed , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.xacc , packet1.yacc , packet1.zacc );
    mavlink_msg_hil_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("HIL_STATE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_HIL_STATE) != NULL);
#endif
}

static void mavlink_test_hil_gps(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_HIL_GPS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_hil_gps_t packet_in = {
        93372036854775807ULL,963497880,963498088,963498296,18275,18379,18483,18587,18691,18795,18899,235,46,113,19159
    };
    mavlink_hil_gps_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.eph = packet_in.eph;
        packet1.epv = packet_in.epv;
        packet1.vel = packet_in.vel;
        packet1.vn = packet_in.vn;
        packet1.ve = packet_in.ve;
        packet1.vd = packet_in.vd;
        packet1.cog = packet_in.cog;
        packet1.fix_type = packet_in.fix_type;
        packet1.satellites_visible = packet_in.satellites_visible;
        packet1.id = packet_in.id;
        packet1.yaw = packet_in.yaw;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_HIL_GPS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_HIL_GPS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_gps_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_hil_gps_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_gps_pack(system_id, component_id, &msg , packet1.time_usec , packet1.fix_type , packet1.lat , packet1.lon , packet1.alt , packet1.eph , packet1.epv , packet1.vel , packet1.vn , packet1.ve , packet1.vd , packet1.cog , packet1.satellites_visible , packet1.id , packet1.yaw );
    mavlink_msg_hil_gps_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_gps_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.fix_type , packet1.lat , packet1.lon , packet1.alt , packet1.eph , packet1.epv , packet1.vel , packet1.vn , packet1.ve , packet1.vd , packet1.cog , packet1.satellites_visible , packet1.id , packet1.yaw );
    mavlink_msg_hil_gps_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_hil_gps_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_gps_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.fix_type , packet1.lat , packet1.lon , packet1.alt , packet1.eph , packet1.epv , packet1.vel , packet1.vn , packet1.ve , packet1.vd , packet1.cog , packet1.satellites_visible , packet1.id , packet1.yaw );
    mavlink_msg_hil_gps_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("HIL_GPS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_HIL_GPS) != NULL);
#endif
}

static void mavlink_test_hil_state_quaternion(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_HIL_STATE_QUATERNION >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_hil_state_quaternion_t packet_in = {
        93372036854775807ULL,{ 73.0, 74.0, 75.0, 76.0 },185.0,213.0,241.0,963499336,963499544,963499752,19731,19835,19939,20043,20147,20251,20355,20459
    };
    mavlink_hil_state_quaternion_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.rollspeed = packet_in.rollspeed;
        packet1.pitchspeed = packet_in.pitchspeed;
        packet1.yawspeed = packet_in.yawspeed;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.ind_airspeed = packet_in.ind_airspeed;
        packet1.true_airspeed = packet_in.true_airspeed;
        packet1.xacc = packet_in.xacc;
        packet1.yacc = packet_in.yacc;
        packet1.zacc = packet_in.zacc;
        
        mav_array_memcpy(packet1.attitude_quaternion, packet_in.attitude_quaternion, sizeof(float)*4);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_HIL_STATE_QUATERNION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_HIL_STATE_QUATERNION_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_state_quaternion_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_hil_state_quaternion_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_state_quaternion_pack(system_id, component_id, &msg , packet1.time_usec , packet1.attitude_quaternion , packet1.rollspeed , packet1.pitchspeed , packet1.yawspeed , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.ind_airspeed , packet1.true_airspeed , packet1.xacc , packet1.yacc , packet1.zacc );
    mavlink_msg_hil_state_quaternion_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_state_quaternion_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.attitude_quaternion , packet1.rollspeed , packet1.pitchspeed , packet1.yawspeed , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.ind_airspeed , packet1.true_airspeed , packet1.xacc , packet1.yacc , packet1.zacc );
    mavlink_msg_hil_state_quaternion_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_hil_state_quaternion_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_state_quaternion_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.attitude_quaternion , packet1.rollspeed , packet1.pitchspeed , packet1.yawspeed , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.ind_airspeed , packet1.true_airspeed , packet1.xacc , packet1.yacc , packet1.zacc );
    mavlink_msg_hil_state_quaternion_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("HIL_STATE_QUATERNION") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_HIL_STATE_QUATERNION) != NULL);
#endif
}

static void mavlink_test_hil_rc_inputs_raw(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_HIL_RC_INPUTS_RAW >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_hil_rc_inputs_raw_t packet_in = {
        93372036854775807ULL,17651,17755,17859,17963,18067,18171,18275,18379,18483,18587,18691,18795,101
    };
    mavlink_hil_rc_inputs_raw_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.chan1_raw = packet_in.chan1_raw;
        packet1.chan2_raw = packet_in.chan2_raw;
        packet1.chan3_raw = packet_in.chan3_raw;
        packet1.chan4_raw = packet_in.chan4_raw;
        packet1.chan5_raw = packet_in.chan5_raw;
        packet1.chan6_raw = packet_in.chan6_raw;
        packet1.chan7_raw = packet_in.chan7_raw;
        packet1.chan8_raw = packet_in.chan8_raw;
        packet1.chan9_raw = packet_in.chan9_raw;
        packet1.chan10_raw = packet_in.chan10_raw;
        packet1.chan11_raw = packet_in.chan11_raw;
        packet1.chan12_raw = packet_in.chan12_raw;
        packet1.rssi = packet_in.rssi;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_HIL_RC_INPUTS_RAW_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_HIL_RC_INPUTS_RAW_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_rc_inputs_raw_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_hil_rc_inputs_raw_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_rc_inputs_raw_pack(system_id, component_id, &msg , packet1.time_usec , packet1.chan1_raw , packet1.chan2_raw , packet1.chan3_raw , packet1.chan4_raw , packet1.chan5_raw , packet1.chan6_raw , packet1.chan7_raw , packet1.chan8_raw , packet1.chan9_raw , packet1.chan10_raw , packet1.chan11_raw , packet1.chan12_raw , packet1.rssi );
    mavlink_msg_hil_rc_inputs_raw_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_rc_inputs_raw_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.chan1_raw , packet1.chan2_raw , packet1.chan3_raw , packet1.chan4_raw , packet1.chan5_raw , packet1.chan6_raw , packet1.chan7_raw , packet1.chan8_raw , packet1.chan9_raw , packet1.chan10_raw , packet1.chan11_raw , packet1.chan12_raw , packet1.rssi );
    mavlink_msg_hil_rc_inputs_raw_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_hil_rc_inputs_raw_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_hil_rc_inputs_raw_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.chan1_raw , packet1.chan2_raw , packet1.chan3_raw , packet1.chan4_raw , packet1.chan5_raw , packet1.chan6_raw , packet1.chan7_raw , packet1.chan8_raw , packet1.chan9_raw , packet1.chan10_raw , packet1.chan11_raw , packet1.chan12_raw , packet1.rssi );
    mavlink_msg_hil_rc_inputs_raw_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("HIL_RC_INPUTS_RAW") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_HIL_RC_INPUTS_RAW) != NULL);
#endif
}

static void mavlink_test_log_request_list(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LOG_REQUEST_LIST >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_log_request_list_t packet_in = {
        17235,17339,17,84
    };
    mavlink_log_request_list_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.start = packet_in.start;
        packet1.end = packet_in.end;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LOG_REQUEST_LIST_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LOG_REQUEST_LIST_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_request_list_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_log_request_list_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_request_list_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.start , packet1.end );
    mavlink_msg_log_request_list_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_request_list_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.start , packet1.end );
    mavlink_msg_log_request_list_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_log_request_list_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_request_list_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.start , packet1.end );
    mavlink_msg_log_request_list_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LOG_REQUEST_LIST") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LOG_REQUEST_LIST) != NULL);
#endif
}

static void mavlink_test_log_entry(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LOG_ENTRY >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_log_entry_t packet_in = {
        963497464,963497672,17651,17755,17859
    };
    mavlink_log_entry_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_utc = packet_in.time_utc;
        packet1.size = packet_in.size;
        packet1.id = packet_in.id;
        packet1.num_logs = packet_in.num_logs;
        packet1.last_log_num = packet_in.last_log_num;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LOG_ENTRY_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LOG_ENTRY_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_entry_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_log_entry_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_entry_pack(system_id, component_id, &msg , packet1.id , packet1.num_logs , packet1.last_log_num , packet1.time_utc , packet1.size );
    mavlink_msg_log_entry_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_entry_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.id , packet1.num_logs , packet1.last_log_num , packet1.time_utc , packet1.size );
    mavlink_msg_log_entry_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_log_entry_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_entry_send(MAVLINK_COMM_1 , packet1.id , packet1.num_logs , packet1.last_log_num , packet1.time_utc , packet1.size );
    mavlink_msg_log_entry_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LOG_ENTRY") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LOG_ENTRY) != NULL);
#endif
}

static void mavlink_test_log_request_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LOG_REQUEST_DATA >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_log_request_data_t packet_in = {
        963497464,963497672,17651,163,230
    };
    mavlink_log_request_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.ofs = packet_in.ofs;
        packet1.count = packet_in.count;
        packet1.id = packet_in.id;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LOG_REQUEST_DATA_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LOG_REQUEST_DATA_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_request_data_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_log_request_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_request_data_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.id , packet1.ofs , packet1.count );
    mavlink_msg_log_request_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_request_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.id , packet1.ofs , packet1.count );
    mavlink_msg_log_request_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_log_request_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_request_data_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.id , packet1.ofs , packet1.count );
    mavlink_msg_log_request_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LOG_REQUEST_DATA") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LOG_REQUEST_DATA) != NULL);
#endif
}

static void mavlink_test_log_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LOG_DATA >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_log_data_t packet_in = {
        963497464,17443,151,{ 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 }
    };
    mavlink_log_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.ofs = packet_in.ofs;
        packet1.id = packet_in.id;
        packet1.count = packet_in.count;
        
        mav_array_memcpy(packet1.data, packet_in.data, sizeof(uint8_t)*90);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LOG_DATA_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LOG_DATA_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_data_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_log_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_data_pack(system_id, component_id, &msg , packet1.id , packet1.ofs , packet1.count , packet1.data );
    mavlink_msg_log_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.id , packet1.ofs , packet1.count , packet1.data );
    mavlink_msg_log_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_log_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_data_send(MAVLINK_COMM_1 , packet1.id , packet1.ofs , packet1.count , packet1.data );
    mavlink_msg_log_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LOG_DATA") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LOG_DATA) != NULL);
#endif
}

static void mavlink_test_log_erase(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LOG_ERASE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_log_erase_t packet_in = {
        5,72
    };
    mavlink_log_erase_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LOG_ERASE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LOG_ERASE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_erase_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_log_erase_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_erase_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component );
    mavlink_msg_log_erase_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_erase_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component );
    mavlink_msg_log_erase_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_log_erase_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_erase_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component );
    mavlink_msg_log_erase_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LOG_ERASE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LOG_ERASE) != NULL);
#endif
}

static void mavlink_test_log_request_end(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LOG_REQUEST_END >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_log_request_end_t packet_in = {
        5,72
    };
    mavlink_log_request_end_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LOG_REQUEST_END_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LOG_REQUEST_END_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_request_end_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_log_request_end_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_request_end_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component );
    mavlink_msg_log_request_end_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_request_end_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component );
    mavlink_msg_log_request_end_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_log_request_end_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_log_request_end_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component );
    mavlink_msg_log_request_end_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LOG_REQUEST_END") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LOG_REQUEST_END) != NULL);
#endif
}

static void mavlink_test_message_interval(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MESSAGE_INTERVAL >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_message_interval_t packet_in = {
        963497464,17443
    };
    mavlink_message_interval_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.interval_us = packet_in.interval_us;
        packet1.message_id = packet_in.message_id;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MESSAGE_INTERVAL_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MESSAGE_INTERVAL_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_message_interval_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_message_interval_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_message_interval_pack(system_id, component_id, &msg , packet1.message_id , packet1.interval_us );
    mavlink_msg_message_interval_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_message_interval_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.message_id , packet1.interval_us );
    mavlink_msg_message_interval_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_message_interval_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_message_interval_send(MAVLINK_COMM_1 , packet1.message_id , packet1.interval_us );
    mavlink_msg_message_interval_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MESSAGE_INTERVAL") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MESSAGE_INTERVAL) != NULL);
#endif
}

static void mavlink_test_storage_information(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_STORAGE_INFORMATION >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_storage_information_t packet_in = {
        963497464,45.0,73.0,101.0,129.0,157.0,77,144,211,22,"CDEFGHIJKLMNOPQRSTUVWXYZABCDEFG",185
    };
    mavlink_storage_information_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_boot_ms = packet_in.time_boot_ms;
        packet1.total_capacity = packet_in.total_capacity;
        packet1.used_capacity = packet_in.used_capacity;
        packet1.available_capacity = packet_in.available_capacity;
        packet1.read_speed = packet_in.read_speed;
        packet1.write_speed = packet_in.write_speed;
        packet1.storage_id = packet_in.storage_id;
        packet1.storage_count = packet_in.storage_count;
        packet1.status = packet_in.status;
        packet1.type = packet_in.type;
        packet1.storage_usage = packet_in.storage_usage;
        
        mav_array_memcpy(packet1.name, packet_in.name, sizeof(char)*32);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_STORAGE_INFORMATION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_STORAGE_INFORMATION_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_storage_information_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_storage_information_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_storage_information_pack(system_id, component_id, &msg , packet1.time_boot_ms , packet1.storage_id , packet1.storage_count , packet1.status , packet1.total_capacity , packet1.used_capacity , packet1.available_capacity , packet1.read_speed , packet1.write_speed , packet1.type , packet1.name , packet1.storage_usage );
    mavlink_msg_storage_information_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_storage_information_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_boot_ms , packet1.storage_id , packet1.storage_count , packet1.status , packet1.total_capacity , packet1.used_capacity , packet1.available_capacity , packet1.read_speed , packet1.write_speed , packet1.type , packet1.name , packet1.storage_usage );
    mavlink_msg_storage_information_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_storage_information_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_storage_information_send(MAVLINK_COMM_1 , packet1.time_boot_ms , packet1.storage_id , packet1.storage_count , packet1.status , packet1.total_capacity , packet1.used_capacity , packet1.available_capacity , packet1.read_speed , packet1.write_speed , packet1.type , packet1.name , packet1.storage_usage );
    mavlink_msg_storage_information_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("STORAGE_INFORMATION") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_STORAGE_INFORMATION) != NULL);
#endif
}

static void mavlink_test_wifi_config_ap(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_WIFI_CONFIG_AP >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_wifi_config_ap_t packet_in = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDE","GHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQ",37,104
    };
    mavlink_wifi_config_ap_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.mode = packet_in.mode;
        packet1.response = packet_in.response;
        
        mav_array_memcpy(packet1.ssid, packet_in.ssid, sizeof(char)*32);
        mav_array_memcpy(packet1.password, packet_in.password, sizeof(char)*64);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_WIFI_CONFIG_AP_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_WIFI_CONFIG_AP_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_wifi_config_ap_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_wifi_config_ap_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_wifi_config_ap_pack(system_id, component_id, &msg , packet1.ssid , packet1.password , packet1.mode , packet1.response );
    mavlink_msg_wifi_config_ap_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_wifi_config_ap_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.ssid , packet1.password , packet1.mode , packet1.response );
    mavlink_msg_wifi_config_ap_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_wifi_config_ap_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_wifi_config_ap_send(MAVLINK_COMM_1 , packet1.ssid , packet1.password , packet1.mode , packet1.response );
    mavlink_msg_wifi_config_ap_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("WIFI_CONFIG_AP") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_WIFI_CONFIG_AP) != NULL);
#endif
}

static void mavlink_test_play_tune_v2(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PLAY_TUNE_V2 >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_play_tune_v2_t packet_in = {
        963497464,17,84,"GHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRS"
    };
    mavlink_play_tune_v2_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.format = packet_in.format;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        mav_array_memcpy(packet1.tune, packet_in.tune, sizeof(char)*248);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PLAY_TUNE_V2_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PLAY_TUNE_V2_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_play_tune_v2_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_play_tune_v2_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_play_tune_v2_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.format , packet1.tune );
    mavlink_msg_play_tune_v2_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_play_tune_v2_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.format , packet1.tune );
    mavlink_msg_play_tune_v2_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_play_tune_v2_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_play_tune_v2_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.format , packet1.tune );
    mavlink_msg_play_tune_v2_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PLAY_TUNE_V2") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PLAY_TUNE_V2) != NULL);
#endif
}

static void mavlink_test_supported_tunes(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SUPPORTED_TUNES >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_supported_tunes_t packet_in = {
        963497464,17,84
    };
    mavlink_supported_tunes_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.format = packet_in.format;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SUPPORTED_TUNES_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SUPPORTED_TUNES_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_supported_tunes_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_supported_tunes_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_supported_tunes_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.format );
    mavlink_msg_supported_tunes_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_supported_tunes_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.format );
    mavlink_msg_supported_tunes_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_supported_tunes_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_supported_tunes_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.format );
    mavlink_msg_supported_tunes_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SUPPORTED_TUNES") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SUPPORTED_TUNES) != NULL);
#endif
}

static void mavlink_test_barometer_altitude(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_BAROMETER_ALTITUDE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_barometer_altitude_t packet_in = {
        93372036854775807ULL,963497880,17859,17963,18067
    };
    mavlink_barometer_altitude_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.altitude = packet_in.altitude;
        packet1.humidity = packet_in.humidity;
        packet1.pressure = packet_in.pressure;
        packet1.temperature = packet_in.temperature;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_BAROMETER_ALTITUDE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_BAROMETER_ALTITUDE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_barometer_altitude_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_barometer_altitude_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_barometer_altitude_pack(system_id, component_id, &msg , packet1.time_usec , packet1.humidity , packet1.pressure , packet1.temperature , packet1.altitude );
    mavlink_msg_barometer_altitude_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_barometer_altitude_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.humidity , packet1.pressure , packet1.temperature , packet1.altitude );
    mavlink_msg_barometer_altitude_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_barometer_altitude_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_barometer_altitude_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.humidity , packet1.pressure , packet1.temperature , packet1.altitude );
    mavlink_msg_barometer_altitude_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("BAROMETER_ALTITUDE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_BAROMETER_ALTITUDE) != NULL);
#endif
}

static void mavlink_test_combined_sensors(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_COMBINED_SENSORS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_combined_sensors_t packet_in = {
        93372036854775807ULL,963497880,963498088,963498296,963498504,18483,18587,18691,18795,18899,19003,19107,19211,19315,19419,19523,19627
    };
    mavlink_combined_sensors_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.altitude = packet_in.altitude;
        packet1.xvel = packet_in.xvel;
        packet1.yvel = packet_in.yvel;
        packet1.zvel = packet_in.zvel;
        packet1.xacc = packet_in.xacc;
        packet1.yacc = packet_in.yacc;
        packet1.zacc = packet_in.zacc;
        packet1.xgyro = packet_in.xgyro;
        packet1.ygyro = packet_in.ygyro;
        packet1.zgyro = packet_in.zgyro;
        packet1.xmag = packet_in.xmag;
        packet1.ymag = packet_in.ymag;
        packet1.zmag = packet_in.zmag;
        packet1.humidity = packet_in.humidity;
        packet1.pressure = packet_in.pressure;
        packet1.temperature = packet_in.temperature;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_COMBINED_SENSORS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_COMBINED_SENSORS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_combined_sensors_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_combined_sensors_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_combined_sensors_pack(system_id, component_id, &msg , packet1.time_usec , packet1.xacc , packet1.yacc , packet1.zacc , packet1.xgyro , packet1.ygyro , packet1.zgyro , packet1.xmag , packet1.ymag , packet1.zmag , packet1.humidity , packet1.pressure , packet1.temperature , packet1.altitude , packet1.xvel , packet1.yvel , packet1.zvel );
    mavlink_msg_combined_sensors_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_combined_sensors_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.xacc , packet1.yacc , packet1.zacc , packet1.xgyro , packet1.ygyro , packet1.zgyro , packet1.xmag , packet1.ymag , packet1.zmag , packet1.humidity , packet1.pressure , packet1.temperature , packet1.altitude , packet1.xvel , packet1.yvel , packet1.zvel );
    mavlink_msg_combined_sensors_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_combined_sensors_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_combined_sensors_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.xacc , packet1.yacc , packet1.zacc , packet1.xgyro , packet1.ygyro , packet1.zgyro , packet1.xmag , packet1.ymag , packet1.zmag , packet1.humidity , packet1.pressure , packet1.temperature , packet1.altitude , packet1.xvel , packet1.yvel , packet1.zvel );
    mavlink_msg_combined_sensors_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("COMBINED_SENSORS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_COMBINED_SENSORS) != NULL);
#endif
}

static void mavlink_test_rocket(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_sys_status(system_id, component_id, last_msg);
    mavlink_test_system_time(system_id, component_id, last_msg);
    mavlink_test_ping(system_id, component_id, last_msg);
    mavlink_test_set_mode(system_id, component_id, last_msg);
    mavlink_test_param_request_read(system_id, component_id, last_msg);
    mavlink_test_param_request_list(system_id, component_id, last_msg);
    mavlink_test_param_value(system_id, component_id, last_msg);
    mavlink_test_param_set(system_id, component_id, last_msg);
    mavlink_test_gps_raw_int(system_id, component_id, last_msg);
    mavlink_test_gps_status(system_id, component_id, last_msg);
    mavlink_test_raw_imu(system_id, component_id, last_msg);
    mavlink_test_raw_pressure(system_id, component_id, last_msg);
    mavlink_test_attitude(system_id, component_id, last_msg);
    mavlink_test_attitude_quaternion(system_id, component_id, last_msg);
    mavlink_test_servo_output_raw(system_id, component_id, last_msg);
    mavlink_test_command_int(system_id, component_id, last_msg);
    mavlink_test_command_long(system_id, component_id, last_msg);
    mavlink_test_command_ack(system_id, component_id, last_msg);
    mavlink_test_command_cancel(system_id, component_id, last_msg);
    mavlink_test_sim_state(system_id, component_id, last_msg);
    mavlink_test_timesync(system_id, component_id, last_msg);
    mavlink_test_camera_trigger(system_id, component_id, last_msg);
    mavlink_test_hil_state(system_id, component_id, last_msg);
    mavlink_test_hil_gps(system_id, component_id, last_msg);
    mavlink_test_hil_state_quaternion(system_id, component_id, last_msg);
    mavlink_test_hil_rc_inputs_raw(system_id, component_id, last_msg);
    mavlink_test_log_request_list(system_id, component_id, last_msg);
    mavlink_test_log_entry(system_id, component_id, last_msg);
    mavlink_test_log_request_data(system_id, component_id, last_msg);
    mavlink_test_log_data(system_id, component_id, last_msg);
    mavlink_test_log_erase(system_id, component_id, last_msg);
    mavlink_test_log_request_end(system_id, component_id, last_msg);
    mavlink_test_message_interval(system_id, component_id, last_msg);
    mavlink_test_storage_information(system_id, component_id, last_msg);
    mavlink_test_wifi_config_ap(system_id, component_id, last_msg);
    mavlink_test_play_tune_v2(system_id, component_id, last_msg);
    mavlink_test_supported_tunes(system_id, component_id, last_msg);
    mavlink_test_barometer_altitude(system_id, component_id, last_msg);
    mavlink_test_combined_sensors(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // ROCKET_TESTSUITE_H
