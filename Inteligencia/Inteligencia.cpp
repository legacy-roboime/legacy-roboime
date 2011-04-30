#include "Simulation.h"
#include "UDPServerThread.h"
#include "UDPServer.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>

int main(int argc, char **argv)
{
	printf("Modulo Inteligencia");

	//Thread* ut = new UDPServerThread("UDPServerThread",9786, "127.0.0.1");		
	//((UDPServerThread*)ut)->start();

	//Simulation* simulation = new Simulation();
	/*simulation->*/Simulation::function(1,argv);//(argc, argv);//(0,NULL);//(argc, argv);
	return 0;
}