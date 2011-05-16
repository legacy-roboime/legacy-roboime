#include <stdio.h>
#include "Simulation.h"
#include "UDPServerThread.h"
#include "UDPServerSimInt.h"

int main(int argc, char **argv)
{
	printf("Modulo Simulacao\n");

	UDPServerSimInt* udpServerSimInt = new UDPServerSimInt(); 

	Thread *udpServerThread = new UDPServerThread((UDPServer*)udpServerSimInt);
	((UDPServerThread*)udpServerThread)->start();

	Simulation::function(argc, argv);

	((UDPServerThread*)udpServerThread)->stop();
	
	delete udpServerThread;
	delete udpServerSimInt;
	return 0;
}