#include "rplidar_python_interface.h"
#include "sl_lidar_driver.h"
#include <string>

#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))

sl::ILidarDriver* drv = NULL;
sl::IChannel* channel;
bool is_connected=false;
float scan_duration = 0.1;

void rplidar_create_driver()
{
    if(drv==NULL)
        drv = *sl::createLidarDriver();
    printf("RPLidar driver created");
}

bool rplidar_connect_cpp(const char* device = "/dev/ttyUSB0", int baudrate = 1000000)
{
    rplidar_create_driver();
    sl_lidar_response_device_info_t devinfo;
    channel = *sl::createSerialPortChannel(std::string(device), baudrate);
    if (SL_IS_OK((drv)->connect(channel))) 
    {
        if(SL_IS_OK(drv->getDeviceInfo(devinfo)))
        {
            is_connected = true;
            printf("\n"
                    "Firmware Ver: %d.%02d\n"
                    "Hardware Rev: %d\n"
                    , devinfo.firmware_version>>8
                    , devinfo.firmware_version & 0xFF
                    , (int)devinfo.hardware_version);
            sl_lidar_response_device_health_t healthinfo;
            if (SL_IS_OK(drv->getHealth(healthinfo))) 
            {
                printf("SLAMTEC Lidar health status : %d\n", healthinfo.status);
                if (healthinfo.status == SL_LIDAR_STATUS_ERROR) {
                    fprintf(stderr, "Error, slamtec lidar internal error detected. Please reboot the device to retry.\n");
                    is_connected = false;
                }
            }
        }
    }
    return is_connected;
}

bool rplidar_start_scan_cpp()
{
    return SL_IS_OK(drv->startScan(0,1));
}

bool rplidar_stop_scan_cpp()
{   
    return SL_IS_OK(drv->stop());
}

bool rplidar_set_motor_speed_cpp(unsigned short speed)
{
    if(SL_IS_OK(drv->setMotorSpeed(speed)))
    {
        scan_duration = 1.0f / ((speed)/60.0f);
        return true;
    }
    return false;
}

bool rplidar_exit_cpp()
{
    if(drv) {
        printf("Closing rplidar lib.");
        delete drv;
        drv = NULL;
    }
    return true;
}

unsigned int rplidar_get_scan_data_cpp(sl_lidar_response_measurement_node_hq_t* nodes, unsigned int count)
{
    size_t node_count = (size_t)count;
    if (SL_IS_OK(drv->grabScanDataHq(nodes, node_count))) 
    {
        drv->ascendScanData(nodes, node_count);
        /*
        printf("%d", (int)node_count);
        for (int pos = 0; pos < (int)node_count ; ++pos) {
            printf("%s theta: %03.2f Dist: %08.2f Q: %d \n", 
                (nodes[pos].flag & SL_LIDAR_RESP_HQ_FLAG_SYNCBIT) ?"S ":"  ", 
                (nodes[pos].angle_z_q14 * 90.f) / 16384.f,
                nodes[pos].dist_mm_q2/4.0f,
                nodes[pos].quality >> SL_LIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);
        }
        */
        return (unsigned int)node_count;
    }
    return 0;
}


unsigned int rplidar_get_scan_data_float_cpp(scan_data_t* nodes, unsigned int count)
{
    sl_lidar_response_measurement_node_hq_t _nodes[8192];
    size_t node_count = count;
    unsigned int scan_size = rplidar_get_scan_data_cpp(_nodes, node_count);
    for(unsigned int i = 0; i < scan_size; ++i)
    {   
        nodes[i].timestamp = (float(i)*scan_duration/float(node_count));
        nodes[i].angle = float(_nodes[i].angle_z_q14) * 90.0f / 16384.0f;
        nodes[i].distance = float(_nodes[i].dist_mm_q2)*0.25f;
        nodes[i].quality = float(_nodes[i].quality >> SL_LIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);
    }
    return scan_size;
}


class Cleanup {
public:
    ~Cleanup()
    {
        rplidar_exit_cpp();
    }
}

cleanup = Cleanup();