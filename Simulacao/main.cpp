#include <stdio.h>
#include "Simulation.h"
#include "UDPServerThread.h"

int main(int argc, char **argv)
{
	printf("Modulo Simulacao");

	UDPServerSimInt* udpServerSimInt = new UDPServerSimInt(); 

	Thread *udpServerThread = new UDPServerThread((UDPServer*)udpServerSimInt);
	((UDPServerThread*)udpServerThread)->start();

	Simulation::function(argc, argv);

	//Thread *simulationThread = new Simulation();
	//((Simulation*)simulationThread)->start();
	
	//delete udpServerThread;
	//delete sim;
	return 0;
}