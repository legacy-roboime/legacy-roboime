#pragma once

#include "NxActor.h"

class NxField
{
public:
	int indexScene;
	float widthBorderField;
	float heightBorderField;
	NxActor* actorParedeLateralPositivo;
	NxActor* actorParedeLateralNegativo;
	NxActor* actorParedeFundoNegativo;
	NxActor* actorParedeFundoPositivo;
	NxActor* actorCampo;
	NxActor* actorGolPositivoParedeFundo;
	NxActor* actorGolPositivoParedeNegativo;
	NxActor* actorGolPositivoParedePositivo;
	NxActor* actorGolNegativoParedeFundo;
	NxActor* actorGolNegativoParedePositivo;
	NxActor* actorGolNegativoParedeNegativo;
public:
	NxField(void);
	~NxField(void);

	void cloneField(int indexNewScene);
};
