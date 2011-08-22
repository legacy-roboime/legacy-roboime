#include "MyContactReport.h"
#include "Simulation.h"
//#include "NxAllRobots.h"

MyContactReport::MyContactReport(void)
{
}

MyContactReport::~MyContactReport(void)
{
}

void  MyContactReport::onContactNotify(NxContactPair& pair, NxU32 events)
{
	NxI32 robotIndex = -1;
	Simulation::allRobots.handlePair(pair, events);	
}