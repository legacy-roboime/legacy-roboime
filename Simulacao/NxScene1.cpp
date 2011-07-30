
#include "NxScene1.h"
#include "Simulation.h"

NxScene1::NxScene1(void):NxScene()
{
	//indexScene = new int;
	//allRobots = new NxAllRobots();
	//field = new NxField();
	//balls = new NxArray<NxBall>();
}

NxScene1::~NxScene1(void)//:~NxScene()
{
}

/*void NxScene1::initNxScene1(){
	indexScene = new int;
	allRobots = new NxAllRobots();
	field = new NxField();
	//balls = new NxArray<NxBall>();
}*/

/*NxActor* NxScene1::getActorWheel(int robotNumber, int wheelNumber)
{
	NxActor* actor = NULL;
	const char* actorName = NULL;
	if(this!=NULL)
	{
		for(unsigned int j=0;j<this->getNbActors();j++)
		{
			actor = this->getActors()[j];
			if(actor != NULL)
			{
				actorName = actor->getName();
				if(actorName != NULL)
				{
					string label;
					string plabel = "Roda";
					stringstream out;
					out << robotNumber;
					out << wheelNumber;
					label.append(plabel);
					label.append(out.str());
					char* arrayLabel = new char[label.size()+1];
					arrayLabel[label.size()]=0;
					memcpy(arrayLabel, label.c_str(), label.size());

					if(strcmp(actorName,arrayLabel)==0)
					{
						delete arrayLabel;
						break;
					}
					else
					{
						actor = NULL;
						delete arrayLabel;
					}
				}
			}
			else continue;
		}
	}
	return actor;
}*/