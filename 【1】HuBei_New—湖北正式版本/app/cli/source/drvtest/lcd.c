
unsigned int  drvtest_lcdclear(void)
{
    unsigned int dwRet = 0;

    (void)bsp_lcd_init();

    (void)bsp_lcd_ctrl(0x0);

    return 0;
}

unsigned int  drvtest_lcdlight(void)
{
    unsigned int dwRet = 0;

    (void)bsp_lcd_init();

    (void)bsp_lcd_ctrl(0x01);

    return 0;
}

unsigned int  drvtest_lcd_showstr(void)
{
    unsigned int dwRet = 0;

    (void)bsp_lcd_init();

    (void)bsp_lcd_show_string(0, 0, "<*上海华虹集成电路有限责任公司*>");
    (void)bsp_lcd_show_string(48, 16, "SHHIC-TJ-2015-03-15");
    (void)bsp_lcd_show_string(40, 32, "version 01.12.34.56.78");
    (void)bsp_lcd_show_string(40, 48, "!#$%^&*,.?()<>-+:'[]{}|");
    return 0;
}



