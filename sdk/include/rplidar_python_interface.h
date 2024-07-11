
#pragma once

extern "C" {
bool rplidar_connect_cpp(const char* device, int baudrate);
bool rplidar_start_scan_cpp();
bool rplidar_stop_scan_cpp();
bool rplidar_set_motor_speed_cpp(unsigned short speed);
bool rplidar_exit_cpp();

}