#include <stdio.h>
#include <unistd.h>

extern volatile unsigned short *p_epld_start_addr;


void start_download(void)
{
	unsigned short download_ctrl;
	int cnt = 0;
	
    download_ctrl = p_epld_start_addr[0x92];	
    p_epld_start_addr[0x92] = download_ctrl&0xfffe;

	do
	{
		cnt++;
    	download_ctrl = p_epld_start_addr[0x92];	
    }while(((download_ctrl&0x04) != 0)&&(cnt<1000));

    
	download_ctrl = p_epld_start_addr[0x92];	
	p_epld_start_addr[0x92] = download_ctrl|0x01;

	usleep(5);

	cnt = 0;
	do
	{
		cnt++;
    	download_ctrl = p_epld_start_addr[0x92];	
    	usleep(1);
    }while(((download_ctrl&0x02) != 0x02)&&(cnt<1000));

    usleep(5);

    return;
}


void load_fpga_file(char *name)
{
    FILE *pf = NULL;
    unsigned char buf[10240];

    pf = fopen(name, "rb");
    if(NULL == pf)
    {
        printf("fpga file %s not exist\n", name);
        return;
    }

    while(!feof(pf))
    {
    	int size;
	    int i;
	    size = fread(buf, 1, 10240,pf);
	    if(size < 0)
	    {
	    	perror("\n");
	    	fclose(pf);
			return;
	    }
	    
	    for(i=0; i<size; ++i)
	    {
	        p_epld_start_addr[0x94] = buf[i];
	        if (i%10000 == 0)
	        {
	            printf(".");
	        }	        
	    }
    }
    
	printf("\n");
	fclose(pf);
	return;    
}

void end_download(void)
{
    p_epld_start_addr[0xa2] = 0;
    usleep(1000);
    p_epld_start_addr[0xa2] = 1;

    return;
}

int download_done(void)
{
    unsigned int doneFlag = 0;
    
    doneFlag = p_epld_start_addr[0x92];

    printf("usage: loda fpge done = %x\n", doneFlag);

    if (doneFlag & 0x04)
    {
        return 0;
    }
    else
    {
        return 1;

    }
}

void get_fpga_name(char *pFileName)
{
    unsigned int verflag = 0;

    verflag = p_epld_start_addr[0x06];

    if (verflag == 0x00)
    {
        strcpy(pFileName, "/opt/rbf/RSDB0_FPGA_55.rbf");
    }
    else if (verflag == 0x01)
    {
        strcpy(pFileName, "/opt/rbf/RSDB0_FPGA_115.rbf");
    }
    else
    {
        strcpy(pFileName, "/opt/rbf/RSDB0_FPGA_115.rbf");
    }
    return;
}

void download_fpga(char *name)
{
	start_download();

	load_fpga_file(name);

	end_download();
}

int main(int argc, char *argv[])
{
    char *fpga_file;
    char filename[256];

    if(argc < 2)
	{
	     printf("usage: load_fpga  fpga_file_name.rbf\n");
	     return;
	}
	
	bsp_epld_init();

	get_fpga_name(filename);

    printf("start download  %s \n", filename);

    download_fpga(filename);
    
    if (0 == download_done())
    {
        printf("download finish \n");
    }
    else
    {
        strcpy(filename, "/opt/rbf/RSDB0_FPGA_40.rbf");
        printf("start download again %s \n", filename);
        download_fpga(filename);

        if (0 == download_done())
        {
            printf("download finish \n");
        }
        else
        {
            printf("download fail \n");
        }

    }
    
	return;
}


