
#pragma once

#include "sl_lidar_driver.h"

struct scan_data_t
{
    float timestamp;
    float angle;
    float distance;
    float quality;
};

extern "C" {

bool rplidar_connect_cpp(const char* device, int baudrate);
bool rplidar_start_scan_cpp();
bool rplidar_stop_scan_cpp();
bool rplidar_set_motor_speed_cpp(unsigned short speed);
bool rplidar_exit_cpp();
unsigned int rplidar_get_scan_data_cpp(sl_lidar_response_measurement_node_hq_t* nodes, unsigned int count);
unsigned int rplidar_get_scan_data_float_cpp(scan_data_t* nodes, unsigned int count);

}