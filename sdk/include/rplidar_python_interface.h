
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

bool rplidar_connect(const char* device, int baudrate);
bool rplidar_start_scan();
bool rplidar_stop_scan();
bool rplidar_set_motor_speed(unsigned short speed);
bool rplidar_exit();
unsigned int rplidar_get_scan_data(sl_lidar_response_measurement_node_hq_t* nodes, unsigned int count);
unsigned int rplidar_get_scan_data_float(scan_data_t* nodes, unsigned int count);

}