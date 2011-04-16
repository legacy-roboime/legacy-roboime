
#include "NxScene1.h"

NxScene1::NxScene1(void):NxScene()
{
}

NxScene1::~NxScene1(void)//:~NxScene()
{
}

NxActor* NxScene1::getActorWheel(int robotNumber, int wheelNumber)
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

					if(strcmp(actorName,arrayLabel)==0) break;
					else actor = NULL;
				}
			}
			else continue;
		}
	}
	return actor;
}