#pragma once
#include "c:\program files (x86)\nvidia corporation\nvidia physx sdk\v2.8.4_win\sdks\physics\include\nxscene.h"
//#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include "NxPhysics.h"

using namespace std;

class NxScene1 :
	public NxScene
{
public:
	friend class NxScene;

	NxScene1(void);
	~NxScene1(void);
	NxActor* getActorWheel(int robotNumber, int wheelNumber);
};
