//#include "Simulation.h"
#include "UDPServerThread.h"
#include "UDPClient.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>

int main(int argc, char **argv)
{
	printf("Modulo Inteligencia");

	//Simulation::function(1,argv);

	Thread* ut = new UDPServerThread("UDPServerThread-Inteligencia",9787, "127.0.0.1");		
	((UDPServerThread*)ut)->start();

	UDPClient* udpClient = new UDPClient("127.0.0.1", "1", 9786);
	/*for(int i=0; i<1000000; i++)*/ udpClient->func1();

	return 0;
}