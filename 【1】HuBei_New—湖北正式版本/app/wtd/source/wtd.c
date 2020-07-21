#include <stdio.h>
#include <unistd.h>
#include "wtd_epld_driver.h"
#include "wtd_driver.h"

int main(void)
{
	(void)bsp_epld_init();

	while(1)
	{		
		bsp_wtd_feed();
		sleep(1);
	}
	
	return 0;
}

