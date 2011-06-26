#pragma once

#include <stdio.h>
#include "Simulation.h"
#include "UDPServerThread.h"
#include "UDPServerSimInt.h"
#include "UDPMulticastSenderThread.h"
#include "UDPMulticastSenderSSLVision.h"

int main(int argc, char **argv)
{
	printf("Modulo Simulacao\n");

	UDPMulticastSenderSSLVision* udpMulticastSenderSSLVision = new UDPMulticastSenderSSLVision();
	Thread* udpMulticastSenderThread = new UDPMulticastSenderThread(udpMulticastSenderSSLVision);
	udpMulticastSenderThread->start();

	UDPServerSimInt* udpServerSimInt = new UDPServerSimInt(); 
	Thread* udpServerThread = new UDPServerThread(udpServerSimInt);
	udpServerThread->start();

	Simulation::function(argc, argv);
	
	//TODO: FAZER CHEGAR NESSE TRECHO DE CODIGO
	((UDPServerThread*)udpServerThread)->stop();

	delete udpServerThread;
	delete udpServerSimInt;
	return 0;
}