#pragma once

#include "NxActor.h"

class NxField
{
private:
	NxActor* actorParedeLateralPositive;
	NxActor* actorParedeLateralNegative;
	NxActor* actorParedeFundoNegative;
	NxActor* actorParedeFundoPositive;
	NxActor* actorCampo;
	NxActor* actorGolPositiveParedeFundo;
	NxActor* actorGolPositiveParedeNegative;
	NxActor* actorGolPositiveParedePositive;
	NxActor* actorGolNegativeParedeFundo;
	NxActor* actorGolNegativeParedePositive;
	NxActor* actorGolNegativeParedeNegative;
public:
	NxField(void);
	~NxField(void);
};
