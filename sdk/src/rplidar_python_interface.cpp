#include "rplidar_python_interface.h"
#include "sl_lidar_driver.h"
#include <string>

sl::ILidarDriver* drv = NULL;
sl::IChannel* channel;
bool is_connected=false;

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
    printf("Try to connect to %s", device);
    if (SL_IS_OK((drv)->connect(channel))) 
    {
        if(SL_IS_OK(drv->getDeviceInfo(devinfo)))
        {
            is_connected = true;
            printf("SLAMTEC LIDAR S/N: ");
            for (int pos = 0; pos < 16 ;++pos) {
                printf("%02X", devinfo.serialnum[pos]);
            }

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
    return SL_IS_OK(drv->setMotorSpeed(speed));
}

bool rplidar_exit_cpp()
{
    if(drv) {
        printf("Closing rplidar lib.");
        delete drv;
        drv = NULL;
    }
}

class Cleanup {
public:
    ~Cleanup()
    {
        rplidar_exit_cpp();
    }
}

cleanup = Cleanup();