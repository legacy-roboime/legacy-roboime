#include "NxField.h"
#include "Simulation.h"

NxField::NxField(void)
{
	widthBorderField = 6050;
	heightBorderField = 4050;
}

NxField::~NxField(void)
{
}

void Simulation::buildModelField(int indexScene)
{
	NxField field;
	field.actorParedeLateralPositivo = Simulation::getActorByLabel(Simulation::gBaseScene, "ParedeLateral+");
	field.actorParedeLateralNegativo = Simulation::getActorByLabel(Simulation::gBaseScene, "ParedeLateral-");
	field.actorParedeFundoNegativo = Simulation::getActorByLabel(Simulation::gBaseScene, "ParedeFundo-");
	field.actorParedeFundoPositivo = Simulation::getActorByLabel(Simulation::gBaseScene, "ParedeFundo+");
	field.actorCampo = Simulation::getActorByLabel(Simulation::gBaseScene, "Campo");
	field.actorGolPositivoParedeFundo = Simulation::getActorByLabel(Simulation::gBaseScene, "Gol+ParedeFundo");
	field.actorGolPositivoParedeNegativo = Simulation::getActorByLabel(Simulation::gBaseScene, "Gol+Parede-");
	field.actorGolPositivoParedePositivo = Simulation::getActorByLabel(Simulation::gBaseScene, "Gol+Parede+");
	field.actorGolNegativoParedeFundo = Simulation::getActorByLabel(Simulation::gBaseScene, "Gol-ParedeFundo");
	field.actorGolNegativoParedePositivo = Simulation::getActorByLabel(Simulation::gBaseScene, "Gol-Parede+");
	field.actorGolNegativoParedeNegativo = Simulation::getActorByLabel(Simulation::gBaseScene, "Gol-Parede-");
	field.indexScene = indexScene;
	Simulation::allFields.fields.push_back(field);
}

void NxField::cloneField(int indexNewScene){
	NxField field;
	field.actorCampo = Simulation::cloneActor(this->actorCampo, indexNewScene);
	field.actorGolNegativoParedeFundo = Simulation::cloneActor(this->actorGolNegativoParedeFundo, indexNewScene);
	field.actorGolNegativoParedeNegativo = Simulation::cloneActor(this->actorGolNegativoParedeNegativo, indexNewScene);
	field.actorGolNegativoParedePositivo = Simulation::cloneActor(this->actorGolNegativoParedePositivo, indexNewScene);
	field.actorGolPositivoParedeFundo = Simulation::cloneActor(this->actorGolPositivoParedeFundo, indexNewScene);
	field.actorGolPositivoParedeNegativo = Simulation::cloneActor(this->actorGolPositivoParedeNegativo, indexNewScene);
	field.actorGolPositivoParedePositivo = Simulation::cloneActor(this->actorGolPositivoParedePositivo, indexNewScene);
	field.actorParedeFundoNegativo = Simulation::cloneActor(this->actorParedeFundoNegativo, indexNewScene);
	field.actorParedeFundoPositivo = Simulation::cloneActor(this->actorParedeFundoPositivo, indexNewScene);
	field.actorParedeLateralNegativo = Simulation::cloneActor(this->actorParedeLateralNegativo, indexNewScene);
	field.actorParedeLateralPositivo = Simulation::cloneActor(this->actorParedeLateralPositivo, indexNewScene);
	field.indexScene = indexNewScene;
	Simulation::allFields.fields.push_back(field);
}
