#pragma once

#include <stdio.h>
#include "SimulationView.h"
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

	//UDPServerIntSim* udpServerSimInt = new UDPServerIntSim(); 
	//Thread* udpServerThread = new UDPServerThread(udpServerSimInt);
	//udpServerThread->start();

	SimulationView::mainSimulationLoop(argc, argv);
	
	//TODO: FAZER CHEGAR NESSE TRECHO DE CODIGO
	//((UDPServerThread*)udpServerThread)->stop();

	//delete udpServerThread;
	//delete udpServerSimInt;
	return 0;
}