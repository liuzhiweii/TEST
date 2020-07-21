/*
 * Driver Configurations
 */
#ifndef DRIVER_H
#define DRIVER_H



/*
 * system configuration
 */
#define OS_TYPE_USE_LINUX 1
#undef OS_TYPE_USE_FREERTOS
#undef OS_TYPE_USE_UBOOT
#undef LINUX_VERSION_USE_2_6_15
#define LINUX_VERSION_USE_2_6_38 1
#undef CPU_TYPE_USE_MPC852
#undef CPU_TYPE_USE_MPC8241
#undef CPU_TYPE_USE_MPC8306
#define CPU_TYPE_USE_MPC8313 1
#undef CPU_TYPE_USE_LPC2138
#undef CPU_TYPE_USE_LPC2148
#undef CPU_TYPE_USE_LPC2468
#undef HD_TYPE_USE_EC00_BOARD0
#undef HD_TYPE_USE_6601_BOARD0
#undef HD_TYPE_USE_8801_BOARD0
#undef HD_TYPE_USE_8700_BOARD0
#undef HD_TYPE_USE_8900_BOARD0
#undef HD_TYPE_USE_8900_BOARD1
#undef HD_TYPE_USE_6700_BOARD0
#undef HD_TYPE_USE_6700_BOARD1
#define HD_TYPE_USE_6700_BOARD2_D 1
#undef HD_TYPE_USE_6700_BOARD2_R

/*
 * UART configuration
 */
#define USP_DRV_UART_USE 1
#define USP_DRV_UART_NUM (3)
#define USP_DRV_EXT_UART_USE 1
#define UART_16752 (1)
#define UART_16554 (0)

/*
 * GPRS configuration
 */
#define USP_DRV_GPRS_USE 1
#define USP_DRV_GPRS_UART_INDEX (2)
#define GPRS_IOTYPE_EPLD_USE 1
#undef GPRS_IOTYPE_IOPORT_USE
#define USP_DRV_GPRS_POWER_DATA_OFFSET (0x168)
#define USP_DRV_GPRS_POWER_DATA_MASK (0x1)
#define USP_DRV_GPRS_POWER_DIRC (0x0)
#define USP_DRV_GPRS_POWER_DIRC_MASK (0x1)
#define USP_DRV_GPRS_RESET_DATA_OFFSET (0x168)
#define USP_DRV_GPRS_RESET_DATA_MASK (0x2)
#define USP_DRV_GPRS_RESET_DIRC (0x0)
#define USP_DRV_GPRS_RESET_DIRC_MASK (0x2)

/*
 * i2c configuration
 */
#define USP_DRV_I2C_USE 1

/*
 * first i2c configuration
 */
#define USP_DRV_I2C_FIRST_USE 1
#define I2C_FIRST_IOTYPE_EPLD_USE 1
#undef I2C_FIRST_IOTYPE_IOPORT_USE
#define USP_DRV_I2C_FIRST_RWOFFSET (0x02)
#define USP_DRV_I2C_FIRST_SDA_DATA_OFFSET (0xd2)
#define USP_DRV_I2C_FIRST_SDA_DATA_MASK (0x1)
#define USP_DRV_I2C_FIRST_SDA_DIRC_OFFSET (0x0)
#define USP_DRV_I2C_FIRST_SDA_DIRC_MASK (0x1)
#define USP_DRV_I2C_FIRST_SCL_DATA_OFFSET (0xd2)
#define USP_DRV_I2C_FIRST_SCL_DATA_MASK (0x2)
#define USP_DRV_I2C_FIRST_SCL_DIRC_OFFSET (0x0)
#define USP_DRV_I2C_FIRST_SCL_DIRC_MASK (0x2)
#define USP_DRV_I2C_FIRST_ENABLE_FLAG (1)
#define USP_DRV_I2C_FIRST_ENABLE_REG (0xdc)

/*
 * second i2c configuration
 */
#define USP_DRV_I2C_SECOND_USE 1
#define I2C_SECOND_IOTYPE_EPLD_USE 1
#undef I2C_SECOND_IOTYPE_IOPORT_USE
#define USP_DRV_I2C_SECOND_RWOFFSET (0x2)
#define USP_DRV_I2C_SECOND_SDA_DATA_OFFSET (0xe8)
#define USP_DRV_I2C_SECOND_SDA_DATA_MASK (0x1)
#define USP_DRV_I2C_SECOND_SDA_DIRC_OFFSET (0x0)
#define USP_DRV_I2C_SECOND_SDA_DIRC_MASK (0x1)
#define USP_DRV_I2C_SECOND_SCL_DATA_OFFSET (0xe8)
#define USP_DRV_I2C_SECOND_SCL_DATA_MASK (0x2)
#define USP_DRV_I2C_SECOND_SCL_DIRC_OFFSET (0x0)
#define USP_DRV_I2C_SECOND_SCL_DIRC_MASK (0x2)
#define USP_DRV_I2C_SECOND_ENABLE_FLAG (1)
#define USP_DRV_I2C_SECOND_ENABLE_REG (0xec)

/*
 * third i2c configuration
 */
#define USP_DRV_I2C_THIRD_USE 1
#define I2C_THIRD_IOTYPE_EPLD_USE 1
#undef I2C_THIRD_IOTYPE_IOPORT_USE
#define USP_DRV_I2C_THIRD_RWOFFSET (0x02)
#define USP_DRV_I2C_THIRD_SDA_DATA_OFFSET (0x10)
#define USP_DRV_I2C_THIRD_SDA_DATA_MASK (0x1)
#define USP_DRV_I2C_THIRD_SDA_DIRC_OFFSET (0x0)
#define USP_DRV_I2C_THIRD_SDA_DIRC_MASK (0x1)
#define USP_DRV_I2C_THIRD_SCL_DATA_OFFSET (0x10)
#define USP_DRV_I2C_THIRD_SCL_DATA_MASK (0x2)
#define USP_DRV_I2C_THIRD_SCL_DIRC_OFFSET (0x0)
#define USP_DRV_I2C_THIRD_SCL_DIRC_MASK (0x2)
#define USP_DRV_I2C_THIRD_ENABLE_FLAG (1)
#define USP_DRV_I2C_THIRD_ENABLE_REG (0x14)

/*
 * EEPROM configuration
 */
#define USP_DRV_EEPROM_USE 1
#define USP_DRV_EEPROM_IC (2)
#define USP_DRV_EEPROM_SIZE (512)
#define USP_DRV_EEPROM_SUB_SIZE (256)

/*
 * first eeprom configuration
 */
#define USP_DRV_EEPROM_FIRST 1
#define USP_DRV_EEPROM_FIRST_FREQ (100)
#define USP_DRV_EEPROM_FIRST_ADDR (0xA8)
#define USP_DRV_EEPROM_FIRST_INDEX (0)
#define USP_DRV_EEPROM_FIRST_WP_FLAG (1)
#define USP_DRV_EEPROM_FIRST_WP_REG (0xDE)
#define USP_DRV_EEPROM_FIRST_WP_REG_MASK (0x1)
#define USP_DRV_EEPROM_FIRST_WP_DIRC_REG (0x0)

/*
 * second eeprom configuration
 */
#define USP_DRV_EEPROM_SECOND 1
#define USP_DRV_EEPROM_SECOND_FREQ (100)
#define USP_DRV_EEPROM_SECOND_ADDR (0xA0)
#define USP_DRV_EEPROM_SECOND_INDEX (2)
#define USP_DRV_EEPROM_SECOND_WP_FLAG (1)
#define USP_DRV_EEPROM_SECOND_WP_REG (0x16)
#define USP_DRV_EEPROM_SECOND_WP_REG_MASK (0x1)
#define USP_DRV_EEPROM_SECOND_WP_DIRC_REG (0x0)

/*
 * ioexpander configuration
 */
#define USP_DRV_IOE_USE 1
#define USP_DRV_IOE_FREQ (50)
#define USP_DRV_IOE_FUN_NUM (0x0D)
#define USP_DRV_IOE_I2C_INDEX (2)
#define USP_DRV_IOE_ADDR_FIRST (0x38)
#define USP_DRV_IOE_ADDR_SECOND (0x39)
#define USP_DRV_IOE_ADDR_THIRD (0x3A)
#define USP_DRV_IOE_ADDR_FORTH (0x3B)
#define USP_DRV_IOE_ADDR_FIFTH (0x3C)
#define USP_DRV_IOE_ENABLE_FLAG (1)
#define USP_DRV_IOE_ENABLE_REG (0x14)
#define USP_DRV_IOE_ENABLE_MASK (0x01)

/*
 * tsensor configuration
 */
#define USP_DRV_TSENSOR_USE 1

/*
 * first tsensor configuration
 */
#define USP_DRV_TSENSOR_FIRST 1
#define USP_DRV_TSENSOR_FIRST_INDEX (1)
#define USP_DRV_TSENSOR_FIRST_ADDR (0x30)
#define USP_DRV_TSENSOR_FIRST_FREQ (50)

/*
 * second tsensor configuration
 */
#define USP_DRV_TSENSOR_SECOND 1
#define USP_DRV_TSENSOR_SECOND_INDEX (2)
#define USP_DRV_TSENSOR_SECOND_ADDR (0x30)
#define USP_DRV_TSENSOR_SECOND_FREQ (50)

/*
 * RTC configuration
 */
#define USP_DRV_RTC_USE 1
#define USP_DRV_RTC_ADDR (0xD0)
#define USP_DRV_RTC_I2C_INDEX (1)
#define USP_DRV_RTC_FREQ (50)

/*
 * EPLD configuration
 */
#define USP_DRV_EPLD_USE 1
#define USP_DRV_EPLD_ADDR_WIDTH (0x01000000)
#define USP_DRV_EPLD_PORT_WIDTH (0x10)
#define USP_EPLD_INT_CTRL_USE 1

/*
 * EPLD interrupt control configuration
 */
#define USP_EPLD_INT_CTRL_OFFSET (0x4a)
#define USP_EPLD_INT_CTRL_MASK (0x14)

/*
 * EPLD linux configuration
 */
#define USP_DRV_EPLD_DEVICE_NAME "usp_drv_epld0"
#define USP_DRV_EPLD_DEVICE_MINOR (137)
#define USP_DRV_EPLD_LINUX_DEVICE "/dev/misc/usp_drv_epld0"
#define USP_DRV_EPLD_BASE_ADDR (0xb0000000)

/*
 * EPLD freertos configuration
 */

/*
 * EPLD data configuration
 */
#define USP_DRV_EPLD_DATA_SET (0x)
#define USP_DRV_EPLD_DATA_CLR (0x)
#define USP_DRV_EPLD_DATA_DIRC (0x)
#define USP_DRV_EPLD_DATA_IN (0x)
#define USP_DRV_EPLD_DATA_BIT0_POS ()
#define USP_DRV_EPLD_DATA_BIT1_POS ()
#define USP_DRV_EPLD_DATA_BIT2_POS ()
#define USP_DRV_EPLD_DATA_BIT3_POS ()
#define USP_DRV_EPLD_DATA_BIT4_POS ()
#define USP_DRV_EPLD_DATA_BIT5_POS ()
#define USP_DRV_EPLD_DATA_BIT6_POS ()
#define USP_DRV_EPLD_DATA_BIT7_POS ()

/*
 * EPLD address configuration
 */
#define USP_DRV_EPLD_ADDR_SET (0x)
#define USP_DRV_EPLD_ADDR_CLR (0x)
#define USP_DRV_EPLD_ADDR_DIRC (0x)
#define USP_DRV_EPLD_ADDR_BIT0_POS ()
#define USP_DRV_EPLD_ADDR_BIT1_POS ()
#define USP_DRV_EPLD_ADDR_BIT2_POS ()
#define USP_DRV_EPLD_ADDR_BIT3_POS ()

/*
 * EPLD read enable configuration
 */
#define USP_DRV_EPLD_READ_N_SET (0x)
#define USP_DRV_EPLD_READ_N_CLR (0x)
#define USP_DRV_EPLD_READ_N_MASK (0x)
#define USP_DRV_EPLD_READ_N_DIRC (0x)

/*
 * EPLD write enable configuration
 */
#define USP_DRV_EPLD_WRITE_N_SET (0x)
#define USP_DRV_EPLD_WRITE_N_CLR (0x)
#define USP_DRV_EPLD_WRITE_N_MASK (0x)
#define USP_DRV_EPLD_WRITE_N_DIRC (0x)

/*
 * FPGA configuration
 */
#define USP_DRV_FPGA_USE 1
#define USP_DRV_FPGA_WITH_EPLD 1
#define USP_DRV_FPGA_PROTOCOL_UHF 1
#undef USP_DRV_FPGA_PROTOCOL_ETC

/*
 * FPGA address configuration
 */
#define USP_DRV_FPGA_BASE_ADDR (0xb0100000)
#define USP_DRV_FPGA_ADDR_WIDTH (0x400000)
#define USP_DRV_FPGA_PORT_WIDTH (0x10)

/*
 * FPGA linux configuration
 */
#define USP_DRV_FPGA_DEVICE_NAME "usp_drv_fpga"
#define USP_DRV_FPGA_DEVICE_MINOR (170)
#define USP_DRV_FPGA_LINUX_DEVICE "/dev/misc/usp_drv_fpga"
#define USP_DRV_FPGA_IRQ_NUMBER (48)

/*
 * GPIO configuration
 */
#define USP_DRV_GPIO_USE 1
#define USP_DRV_GPIO_STATE (0x7F)
#define USP_DRV_GPIO_NR (0x7)
#define USP_DRV_GPIO_DIR_POLARITY (1)
#define USP_DRV_GPIO_DATA_POLARITY (1)

/*
 * GPIO address configuration
 */
#define USP_DRV_GPIO_BASE_ADDR (0xb0100000)
#define USP_DRV_GPIO_ADDR_WIDTH (0x100000)
#define USP_DRV_GPIO_PORT_WIDTH (0x0010)

/*
 * GPIO linux configuration
 */
#define USP_DRV_GPIO_DEVICE_NAME "usp_drv_gpio"
#define USP_DRV_GPIO_DEVICE_MINOR (144)
#define USP_DRV_GPIO_LINUX_DEVICE "/dev/misc/usp_drv_gpio"
#define USP_DRV_GPIO_IRQ_NUMBER (48)

/*
 * GPIO control configuration
 */
#define USP_DRV_GPIO_SND_REG (0x0D1)
#define USP_DRV_GPIO_SND_CPY_REG (0x0)
#define USP_DRV_GPIO_RCV_REG (0x0D2)
#define USP_DRV_GPIO_INT_EVENT_REG (0x001)
#define USP_DRV_GPIO_INT_MASK_REG (0x007D)
#define USP_DRV_GPIO_INT_CLEAR_EXIST (0)
#define USP_DRV_GPIO_INT_CLEAR_REG (0x10)

/*
 * PSAM configuration
 */
#define USP_DRV_PSAM_USE 1

/*
 * PSAM basic configuration
 */
#undef USP_DRV_PSAM_MODE_HARDWARE_USE
#define USP_DRV_PSAM_MODE_SOFTWARE_USE 1
#define USP_DRV_PSAM_NR (0x2)
#define USP_DRV_PSAM_WITH_EPLD 1
#define USP_DRV_PSAM0_USE 1
#define USP_DRV_PSAM1_USE 1
#undef USP_DRV_PSAM2_USE
#undef USP_DRV_PSAM3_USE
#define USP_DRV_PSAM_CLKFLEQ_MAX (15)

/*
 * PSAM linux configuration
 */
#define USP_DRV_PSAM_DEVICE_NAME "usp_drv_psam"
#define USP_DRV_PSAM_DEVICE_MINOR (171)
#define USP_DRV_PSAM0_DEVICE_MINOR ()
#define USP_DRV_PSAM1_DEVICE_MINOR ()
#define USP_DRV_PSAM2_DEVICE_MINOR ()
#define USP_DRV_PSAM3_DEVICE_MINOR ()
#define USP_DRV_PSAM_LINUX_DEVICE "/dev/misc/usp_drv_psam"
#define USP_DRV_PSAM0_LINUX_DEVICE ""
#define USP_DRV_PSAM1_LINUX_DEVICE ""
#define USP_DRV_PSAM2_LINUX_DEVICE ""
#define USP_DRV_PSAM3_LINUX_DEVICE ""

/*
 * PSAM address configuration
 */
#define USP_DRV_PSAM_BASE_ADDR (0xb0000000)
#define USP_DRV_PSAM_ADDR_WIDTH (0x400000)
#define USP_DRV_PSAM0_REG_BASE_ADDR (0x)
#define USP_DRV_PSAM1_REG_BASE_ADDR (0x)
#define USP_DRV_PSAM2_REG_BASE_ADDR (0x)
#define USP_DRV_PSAM3_REG_BASE_ADDR (0x)
#define USP_DRV_PSAM0_FIFO_BASE_ADDR (0x)
#define USP_DRV_PSAM1_FIFO_BASE_ADDR (0x)
#define USP_DRV_PSAM2_FIFO_BASE_ADDR (0x)
#define USP_DRV_PSAM3_FIFO_BASE_ADDR (0x)

/*
 * IOPORT configuration
 */
#define USP_DRV_IOPORT_USE 1

/*
 * IOPORT address configuration
 */
#define USP_DRV_IOPORT_BASE_ADDR (0xFC000000)
#define USP_DRV_IOPORT_ADDR_WIDTH (0x4000)
#define USP_DRV_IOPORT_PORT_WIDTH (0x0020)

/*
 * IOPORT linux configuration
 */
#define USP_DRV_IOPORT_DEVICE_NAME "usp_drv_ioport"
#define USP_DRV_IOPORT_DEVICE_MINOR (150)
#define USP_DRV_IOPORT_LINUX_DEVICE "/dev/misc/usp_drv_ioport"

/*
 * timer configuration
 */
#define USP_DRV_TIMER_USE 1

/*
 * timer address configuration
 */
#define USP_DRV_TIMER_BASE_ADDR (0xE0000000)
#define USP_DRV_TIMER_ADDR_WIDTH (0x100000)
#define USP_DRV_TIMER_PORT_WIDTH (0x0020)

/*
 * timer linux configuration
 */
#define USP_DRV_TIMER_DEVICE_NAME "usp_drv_timer"
#define USP_DRV_TIMER_DEVICE_MINOR (172)
#define USP_DRV_TIMER_LINUX_DEVICE "/dev/misc/usp_drv_timer"

/*
 * get system INFO configuration
 */
#define USP_DRV_GET_SYSTEM_INFO_USE 1

/*
 * timer linux configuration
 */
#define USP_DRV_GET_SYSTEM_INFO_DEVICE_NAME "usp_drv_get_system_info"
#define USP_DRV_GET_SYSTEM_INFO_DEVICE_MINOR (173)
#define USP_DRV_GET_SYSTEM_INFO_DEVICE "/dev/misc/usp_drv_get_system_info"

/*
 * watch dog configuration
 */
#define USP_DRV_WTD_USE 1

/*
 * FREERTOS WTD configuration
 */

/*
 * WST configuration
 */
#define USP_DRV_WTD_WST_DIR_ADDR (0x)
#define USP_DRV_WTD_WST_SET_ADDR (0x)
#define USP_DRV_WTD_WST_CLR_ADDR (0x)
#define USP_DRV_WTD_WST_MASK (0x01)

/*
 * WDI configuration
 */
#define USP_DRV_WTD_WDI_DIR_ADDR (0x)
#define USP_DRV_WTD_WDI_SET_ADDR (0x)
#define USP_DRV_WTD_WDI_CLR_ADDR (0x)
#define USP_DRV_WTD_WDI_MASK (0x01)

/*
 * LINUX and UBOOT WTD configuration
 */

/*
 * basic configuration
 */
#define USP_DRV_WTD_START (0)
#define USP_DRV_WTD_STOP (1)
#define USP_DRV_WTD_FEED_TYPE (1)
#define USP_DRV_WTD_FEED (1)
#define WTD_IOTYPE_EPLD_USE 1
#undef WTD_IOTYPE_IOPORT_USE

/*
 * WST configuration
 */
#define USP_DRV_WTD_WST_DATA_OFFSET (0x5C)
#define USP_DRV_WTD_WST_DIR_OFFSET (0x0)

/*
 * WDI configuration
 */
#define USP_DRV_WTD_WDI_DATA_OFFSET (0x60)
#define USP_DRV_WTD_WDI_DIR_OFFSET (0x0)

/*
 * WMS configuration
 */
#define USP_DRV_WTD_HWFEED (1)
#define USP_DRV_WTD_WMS_DATA_OFFSET (0x5E)
#define USP_DRV_WTD_WMS_MASK (0x01)
#define USP_DRV_WTD_WMS (0x0)
#define USP_DRV_WTD_WMS_DIR_OFFSET (0x0)

/*
 * LED configuration
 */
#define USP_DRV_LED_USE 1
#define USP_DRV_LED_NR (4)

/*
 * FREERTOS LED configuration
 */

/*
 * LED0 configuration
 */
#define USP_DRV_LED_LED0_EXIST (0x01)
#define USP_DRV_LED_LED0_MASK (0x)
#define USP_DRV_LED_LED0_DIR_ADDR (0x)
#define USP_DRV_LED_LED0_SET_ADDR (0x)
#define USP_DRV_LED_LED0_CLR_ADDR (0x)
#define USP_DRV_LED_LED0_STATE (0x0)

/*
 * LED1 configuration
 */
#define USP_DRV_LED_LED1_EXIST (0x01)
#define USP_DRV_LED_LED1_MASK (0x)
#define USP_DRV_LED_LED1_DIR_ADDR (0x)
#define USP_DRV_LED_LED1_SET_ADDR (0x)
#define USP_DRV_LED_LED1_CLR_ADDR (0x)
#define USP_DRV_LED_LED1_STATE (0x0)

/*
 * LED2 configuration
 */
#define USP_DRV_LED_LED2_EXIST (0x01)
#define USP_DRV_LED_LED2_MASK (0x)
#define USP_DRV_LED_LED2_DIR_ADDR (0x)
#define USP_DRV_LED_LED2_SET_ADDR (0x)
#define USP_DRV_LED_LED2_CLR_ADDR (0x)
#define USP_DRV_LED_LED2_STATE (0x0)

/*
 * LED3 configuration
 */
#define USP_DRV_LED_LED3_EXIST (0x01)
#define USP_DRV_LED_LED3_MASK (0x)
#define USP_DRV_LED_LED3_DIR_ADDR (0x)
#define USP_DRV_LED_LED3_SET_ADDR (0x)
#define USP_DRV_LED_LED3_CLR_ADDR (0x)
#define USP_DRV_LED_LED3_STATE (0x0)

/*
 * LINUX and UBOOT LED configuration
 */

/*
 * LED0 configuration
 */
#define USP_DRV_LED_LED0_DATA_MASK (0x01)
#define USP_DRV_LED_LED0_DIR_MASK (0x00)
#define USP_DRV_LED_LED0_DATA_OFFSET (0xC0)
#define USP_DRV_LED_LED0_DIR_OFFSET (0xC0)
#define LED0_IOTYPE_EPLD_USE 1
#undef LED0_IOTYPE_IOPORT_USE
#define USP_DRV_LED_LED0_ADDRTYPE (16)
#define USP_DRV_LED_LED0_RED (0x1)
#define USP_DRV_LED_LED0_GREEN (0x1)
#define USP_DRV_LED_LED0_YELLOW (0x1)
#define USP_DRV_LED_LED0_OFF (0x0)

/*
 * LED1 configuration
 */
#define USP_DRV_LED_LED1_DATA_MASK (0x02)
#define USP_DRV_LED_LED1_DIR_MASK (0x00)
#define USP_DRV_LED_LED1_DATA_OFFSET (0xC0)
#define USP_DRV_LED_LED1_DIR_OFFSET (0xC0)
#define LED1_IOTYPE_EPLD_USE 1
#undef LED1_IOTYPE_IOPORT_USE
#define USP_DRV_LED_LED1_ADDRTYPE (16)
#define USP_DRV_LED_LED1_RED (0x2)
#define USP_DRV_LED_LED1_GREEN (0x2)
#define USP_DRV_LED_LED1_YELLOW (0x2)
#define USP_DRV_LED_LED1_OFF (0x0)

/*
 * LED2 configuration
 */
#define USP_DRV_LED_LED2_DATA_MASK (0x04)
#define USP_DRV_LED_LED2_DIR_MASK (0x04)
#define USP_DRV_LED_LED2_DATA_OFFSET (0xC0)
#define USP_DRV_LED_LED2_DIR_OFFSET (0xC0)
#define LED2_IOTYPE_EPLD_USE 1
#undef LED2_IOTYPE_IOPORT_USE
#define USP_DRV_LED_LED2_ADDRTYPE (16)
#define USP_DRV_LED_LED2_RED (0x4)
#define USP_DRV_LED_LED2_GREEN (0x4)
#define USP_DRV_LED_LED2_YELLOW (0x4)
#define USP_DRV_LED_LED2_OFF (0x0)

/*
 * LED3 configuration
 */
#define USP_DRV_LED_LED3_DATA_MASK (0x08)
#define USP_DRV_LED_LED3_DIR_MASK (0x08)
#define USP_DRV_LED_LED3_DATA_OFFSET (0xC0)
#define USP_DRV_LED_LED3_DIR_OFFSET (0xC0)
#define LED3_IOTYPE_EPLD_USE 1
#undef LED3_IOTYPE_IOPORT_USE
#define USP_DRV_LED_LED3_ADDRTYPE (16)
#define USP_DRV_LED_LED3_RED (0x8)
#define USP_DRV_LED_LED3_GREEN (0x8)
#define USP_DRV_LED_LED3_YELLOW (0x8)
#define USP_DRV_LED_LED3_OFF (0x0)

/*
 * powerid configuration
 */
#undef USP_DRV_POWERID_USE

/*
 * powerid ID0 configuration
 */
#undef ID0_IOTYPE_EPLD_USE
#undef ID0_IOTYPE_IOPORT_USE
#define ID0_PAR_OFFSET (0x)
#define ID0_PAR_MASK (0x)
#define ID0_DIR_OFFSET (0x)
#define ID0_DIR_MASK (0x)
#define ID0_DATA_OFFSET (0x)
#define ID0_DATA_MASK (0x)

/*
 * powerid ID1 configuration
 */
#undef ID1_IOTYPE_EPLD_USE
#undef ID1_IOTYPE_IOPORT_USE
#define ID1_PAR_OFFSET (0x)
#define ID1_PAR_MASK (0x)
#define ID1_DIR_OFFSET (0x)
#define ID1_DIR_MASK (0x)
#define ID1_DATA_OFFSET (0x)
#define ID1_DATA_MASK (0x)

/*
 * powerid ID2 configuration
 */
#undef ID2_IOTYPE_EPLD_USE
#undef ID2_IOTYPE_IOPORT_USE
#define ID2_PAR_OFFSET (0x)
#define ID2_PAR_MASK (0x)
#define ID2_DIR_OFFSET (0x)
#define ID2_DIR_MASK (0x)
#define ID2_DATA_OFFSET (0x)
#define ID2_DATA_MASK (0x)

/*
 * control 485 configuration
 */
#define USP_DRV_CTRL485_USE 1
#define CTRL485_IOTYPE_EPLD_USE 1
#undef CTRL485_IOTYPE_IOPORT_USE
#define USP_DRV_CTRL485_POLARITY (1)
#define USP_DRV_CTRL485_RCVEN_OFFSET (0xE0)
#define USP_DRV_CTRL485_SNDEN_OFFSET (0xE0)
#define USP_DRV_CTRL485_SNDEN_MASK (0x1)
#define USP_DRV_CTRL485_RCVEN_MASK (0x2)

/*
 * FLASH configuration
 */
#define USP_DRV_FLASH_USE 1

/*
 * clockgen configuration
 */
#undef USP_DRV_CLOCKGEN_USE
#undef USP_DRV_AD9516_USE
#undef USP_DRV_LMK04033_USE


#endif

