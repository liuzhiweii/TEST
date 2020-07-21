

unsigned int  drvtest_ledrun(unsigned int dwState)
{
    if (0 != dwState)
    {
        dwState = 1;
    }

    (void)bsp_epld_init();
    (void)bsp_led_initl();

    (void)bsp_led_run_ctl(dwState);

    return 0;
}
unsigned int  drvtest_ledalarm(unsigned int dwState)
{

    if (0 != dwState)
    {
        dwState = 1;
    }

    (void)bsp_epld_init();
    (void)bsp_led_initl();

    (void)bsp_led_alarm_ctl(dwState);

    return 0;

}
unsigned int  drvtest_ledpsam(unsigned int dwState)
{

    if (0 != dwState)
    {
        dwState = 1;
    }

    (void)bsp_epld_init();
    (void)bsp_led_initl();

    (void)bsp_led_psam_ctl(dwState);

    return 0;


}

