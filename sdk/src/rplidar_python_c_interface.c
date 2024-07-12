#include "rplidar_python_c_interface.h"
#include <stdio.h>

bool rplidar_connect_cpp(const char* device, int baudrate);
bool rplidar_start_scan_cpp();
bool rplidar_stop_scan_cpp();
bool rplidar_set_motor_speed_cpp(unsigned short speed);


bool rplidar_connect(const char* device, int baudrate)
{  
    printf("rplidar_connect\n");
    return rplidar_connect_cpp(device, baudrate);    
}

bool rplidar_start_scan()
{
    printf("rplidar_start_scan\n");
    return rplidar_start_scan_cpp();
}

bool rplidar_stop_scan()
{
    printf("rplidar_stop_scan\n");
    return rplidar_stop_scan_cpp();
}

bool rplidar_set_motor_speed(unsigned short speed)
{
    printf("rplidar_set_motor_speed(%d)\n", speed);
    return rplidar_set_motor_speed_cpp(speed);
}

unsigned int rplidar_get_scan_data(void* nodes, unsigned int count)
{
    printf("rplidar_get_scan_data %d\n", count);
    return rplidar_get_scan_data_cpp(nodes, count);
}

unsigned int rplidar_get_scan_data_float(void* nodes, unsigned int count)
{
    return rplidar_get_scan_data_float_cpp(nodes, count);
}
