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
	//TODO: Executar apenas para cena que contem o pair
	for(int i=0; i<Simulation::gScenes.size(); i++){
		Simulation::gScenes[i]->allRobots->handlePair(pair, events);	
	}
}