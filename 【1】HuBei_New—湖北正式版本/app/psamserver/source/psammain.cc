#include <unistd.h>
#include<sys/types.h>
#include <zmq.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "stdio.h"
#include "logm.h"
#include "psamserver.h"

using namespace std;



void startPsam(int psamSlot)
{
	PsamServer *psamServer = new PsamServer(psamSlot);

	psamServer->startRun(); 

	delete psamServer;

	return;
}


int main(int argc, char *argv[])
{
	pid_t pid[4];
	int st;

	init_logm("psamserver");

	for(int i=0; i<4; ++i)
	{
		pid[i] = fork();
		if(pid[i] == 0)
		{
			startPsam(i);
		}
	}

	for(int i=0; i<4; ++i)
	{
		waitpid(pid[i], &st, 0);
	}
	
	return 0;
}






