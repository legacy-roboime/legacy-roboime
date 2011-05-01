#include <stdio.h>
#include "Simulation.h"
#include "UDPServerThread.h"

int main(int argc, char **argv)
{
	Thread *udpServerThread = new UDPServerThread("UDPServerThread-Simulacao",9786, "127.0.0.1");
	((UDPServerThread*)udpServerThread)->start();

	if(((UDPServerThread*)udpServerThread)->getLastReceivedString().compare("1")==0)
	{
		Simulation::function(1,argv);//(argc, argv);//(0,NULL);//(argc, argv);
	}
	
	//delete udpServerThread;
	//delete sim;

	getchar();
	return 0;
}