#include "rplidar_python_c_interface.h"

bool rplidar_connect_cpp(const char* device, int baudrate);
bool rplidar_start_scan_cpp();
bool rplidar_stop_scan_cpp();
bool rplidar_set_motor_speed_cpp(unsigned short speed);


bool rplidar_connect(const char* device, int baudrate)
{  
    printf("rplidar_connect");
    return rplidar_connect_cpp("/dev/ttyUSB0", 1000000);    
}

bool rplidar_start_scan()
{
    printf("rplidar_start_scan");
    return rplidar_start_scan_cpp();
}

bool rplidar_stop_scan()
{
    printf("rplidar_stop_scan");
    return rplidar_stop_scan_cpp();
}

bool rplidar_set_motor_speed(unsigned short speed)
{
    printf("rplidar_set_motor_speed(%i)", speed);
    return rplidar_set_motor_speed_cpp(speed);
}
