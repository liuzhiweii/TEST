#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <mtd/mtd-user.h>

int readMtd(int fd, int offset, int readLen, unsigned char* buffer)
{
	int ret;
	
	ret = lseek(fd, offset, SEEK_SET);
	if(ret < 0)
	{
		perror("seek mtd device fail!\n");
		return -1;
	}

	ret = read(fd, buffer, readLen);
	if(ret <0 )
	{
		perror("read mtd device fail!\n");
		return -1;
	}


	return 0;	
}

int getMtdSize(int fd)
{
	mtd_info_t mtd;

	if(ioctl(fd, MEMGETINFO, &mtd) < 0)
	{
		perror("get mtd info fail\n");
		return 0;
	}

	return mtd.size;
}

bool matchSector(int fd, int addr)
{
	int ret;
	unsigned char buffer[32];
	unsigned char pattern[32] = {0};

	for(int i=0; i<256; ++i)
	{
		ret = readMtd(fd, (addr+i*512), 32, buffer);
		if(ret < 0)
		{
			continue;
		}

		if(0 != memcmp(buffer, pattern, 32))
		{
			return false;
		}
		else
		{
			ret = readMtd(fd, (addr+i*512+480), 32, buffer);
			if(ret < 0)
			{
				continue;
			}
			if(0 != memcmp(buffer, pattern, 32))
			{
				return false;
			}			
		}
		
	}

	printf("this sector is bad\n");
	return true;
}

int eraseSector(int fd, int addr)
{
	int ret;
	erase_info_t info;

	info.start = addr;
	info.length = 128*1024;

	ret = ioctl(fd, MEMERASE, &info.start);
	return ret;	
}

void recoveryMtd(const char *name)
{
	int mtdSize;
	int fd;

	fd = open(name, O_RDWR);
	if(fd <0)
	{
		perror("open mtd fail!\n");
		return;
	}

	mtdSize = getMtdSize(fd);
	if(mtdSize <= 0) return;
	
	for(int i=0; i<mtdSize; i+=(128*1024))
	{
		if(matchSector(fd, i))
		{
			eraseSector(fd, i);
		}
	}

	close(fd);
}


int main(int argc, char *argv[])
{
	char mtdName[10];
	
	printf("recovery flash \n");

	for(int i=0; i<11; ++i)
	{
		sprintf(mtdName, "/dev/mtd%d", i);
		recoveryMtd(mtdName);
	}
	
	return 0;
}



