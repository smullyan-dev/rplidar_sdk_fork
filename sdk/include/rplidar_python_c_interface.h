#pragma once

#include <stdbool.h>

bool rplidar_connect(const char* device, int baudrate);
bool rplidar_start_scan();
bool rplidar_stop_scan();
bool rplidar_set_motor_speed(unsigned short speed);
