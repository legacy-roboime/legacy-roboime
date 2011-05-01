#include <stdio.h>
#include "Simulation.h"
//#include "UDPServerThread.h"

int main(int argc, char **argv)
{
	printf("Modulo Simulacao");

	Simulation::function(argc, argv);

	//Thread *udpServerThread = new UDPServerThread("UDPServerThread-Simulacao",9786, "127.0.0.1");
	//((UDPServerThread*)udpServerThread)->start();

	//Thread *simulationThread = new Simulation();
	//((Simulation*)simulationThread)->start();
	
	//delete udpServerThread;
	//delete sim;
	return 0;
}