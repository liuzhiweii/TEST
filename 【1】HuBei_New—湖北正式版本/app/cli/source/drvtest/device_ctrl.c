#include "bsp.h"


unsigned int  drvtest_device_rst(unsigned int dwDeviceId)
{
    
    if (dwDeviceId > DRV_DEV_RST_ETH1)
    {
        printf("input device id error!\r\n");
    }

    (void)bsp_epld_init();
    (void)bsp_fpga_init();
    (void)bsp_devicectl_init();


    (void)bsp_device_rst_ctl(dwDeviceId);

    return 0;
}

unsigned int  drvtest_device_powctl(unsigned int dwDeviceId, unsigned int dwPowState)
{
    
    if (dwDeviceId > DRV_DEV_PSAM3)
    {
        printf("input device id error!\r\n");
    }

    (void)bsp_epld_init();
    (void)bsp_fpga_init();
    (void)bsp_devicectl_init();

    (void)bsp_device_power_ctl(dwDeviceId, dwPowState);

    return 0;
}

