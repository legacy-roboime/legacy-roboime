#pragma once
#include <iostream>
#include <cstdlib>
#include "Robot.h"
#include "_Skills.h"
#include "CommanderSIM.h"
#include "CommanderTX.h"
#include "UpdaterSIM.h"

#include "UDPServerThread.h"
#include "UDPMulticastSenderThread.h"
#include "UDPMulticastSenderSSLVision.h"
#include "SimpleThread.h"
#include "SimulationView.h"
#include "UDPServerSimInt.h"

using namespace Inteligencia;
using namespace Inteligencia::Skills;

int main(int argc, char *argv[])
{
	cout << "Modulo Inteligencia" << endl;

	UDPMulticastSenderSSLVision* udpMulticastSenderSSLVision = new UDPMulticastSenderSSLVision();
	Thread* udpMulticastSenderThread = new UDPMulticastSenderThread(udpMulticastSenderSSLVision);
	udpMulticastSenderThread->start();

	UDPServerSimInt* udpServerSimInt = new UDPServerSimInt();
	Thread* udpServerThread = new UDPServerThread((UDPServer*)udpServerSimInt);
	udpServerThread->start();

	Thread* simpleThread = new SimpleThread(SimulationView::mainLoop, argc, argv);
	simpleThread->start();

	//SimulationView::mainLoop(argc, argv);

	Robot* rob = new Robot(4);
	Commander* com = new CommanderSIM();
	Updater* upd = new UpdaterSIM();
	com->add(rob);
	upd->add(rob);


	system("pause");

	Skill* mov = new Loops::Circle(rob, 1500, 1500, 600, 20);
	while(true) {
		upd->step();
		mov->step();
		com->step();
	}

	system("pause");

	return 0;
}
