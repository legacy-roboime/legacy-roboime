#pragma once

#include "stdio.h"
#include "stdlib.h"
#include <iostream>

#include "UDPClientThread.h"
#include "UDPClientIntSim.h"

#include "Simulation.h"

using namespace Inteligencia;

int main(int argc, char **argv)
{
	printf("Modulo Inteligencia"); 

	UDPClientIntSim* udpClientIntSim = new UDPClientIntSim();

	while(true)
	{
		udpClientIntSim->setSendString("7 0\n");
		udpClientIntSim->service();

		udpClientIntSim->setSendString("5 0\n");
		udpClientIntSim->service();
	}

	return 0;
}