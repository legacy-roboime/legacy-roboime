#pragma once

#include <stdio.h>
#include "SimulationView.h"
#include "UDPServerThread.h"
#include "UDPMulticastSenderThread.h"
#include "UDPMulticastSenderSSLVision.h"
#include "SimpleThread.h"

int main(int argc, char **argv)
{
	printf("Modulo Planejador\n");
	
	UDPMulticastSenderSSLVision* udpMulticastSenderSSLVision = new UDPMulticastSenderSSLVision();
	Thread* udpMulticastSenderThread = new UDPMulticastSenderThread(udpMulticastSenderSSLVision);
	udpMulticastSenderThread->start();

	UDPServerSimInt* udpServerSimInt = new UDPServerSimInt();
	Thread* udpServerThread = new UDPServerThread((UDPServer*)udpServerSimInt);
	udpServerThread->start();

	SimulationView::mainLoop(argc, argv);

	//TODO: FAZER CHEGAR NESSE TRECHO DE CODIGO
	//((UDPServerThread*)udpServerThread)->stop();
	//delete udpServerThread;
	//delete udpServerSimInt;

	return 0;
}