#pragma once
#include <iostream>
#include <QCoreApplication>
#include <QMutex>

#include "UDPServerThread.h"
#include "UDPMulticastSenderThread.h"
#include "UDPMulticastSenderSSLVision.h"
#include "SimpleThread.h"
#include "SimulationView.h"
#include "UDPServerSimInt.h"

int main(int argc, char* argv[]) {
	QCoreApplication app(argc, argv);
	cout << "Modulo Simulacao" << endl;

	UDPMulticastSenderSSLVision* udpMulticastSenderSSLVision = new UDPMulticastSenderSSLVision();
	Thread* udpMulticastSenderThread = new UDPMulticastSenderThread(udpMulticastSenderSSLVision);
	udpMulticastSenderThread->start();

	UDPServerSimInt* udpServerSimInt = new UDPServerSimInt();
	Thread* udpServerThread = new UDPServerThread((UDPServer*)udpServerSimInt);
	udpServerThread->start();

	/*Thread* simpleThread = new SimpleThread(SimulationView::mainLoop, argc, argv);
	simpleThread->start();


	while(true) {
		Simulation::simulate(0);
		Sleep(1000/60);
	}*/

	SimulationView::mainSimulationLoop(argc, argv);

	return app.exec();
}