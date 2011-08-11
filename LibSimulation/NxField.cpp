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

void NxField::setDimensions(float fieldLength, float fieldWidth, float linesLength, float linesWidth, float goalLength, float goalWidth, float goalHeigth){
	//Medidas do 3ds max width (.x), length (.y), heigth (.z)
	//Obs getDimensions retorna metade das dimensoes totais
	NxShape* const * shapesCampo = this->actorCampo->getShapes();
	NxBoxShape* boxCampo = shapesCampo[0]->isBox();
	NxVec3 dimensionsCampo = boxCampo->getDimensions();

	NxShape* const * shapesParedeFundoNegativo = this->actorParedeFundoNegativo->getShapes();
	NxBoxShape* boxParedeFundoNegativo = shapesParedeFundoNegativo[0]->isBox();
	NxVec3 dimensionsParedeFundoNegativo = boxParedeFundoNegativo->getDimensions();

	NxShape* const * shapesParedeFundoPositivo = this->actorParedeFundoPositivo->getShapes();
	NxBoxShape* boxParedeFundoPositivo = shapesParedeFundoPositivo[0]->isBox();
	NxVec3 dimensionsParedeFundoPositivo = boxParedeFundoPositivo->getDimensions();

	NxShape* const * shapesParedeLateralNegativo = this->actorParedeLateralNegativo->getShapes();
	NxBoxShape* boxParedeLateralNegativo = shapesParedeLateralNegativo[0]->isBox();
	NxVec3 dimensionsParedeLateralNegativo = boxParedeLateralNegativo->getDimensions();

	NxShape* const * shapesParedeLateralPositivo = this->actorParedeLateralPositivo->getShapes();
	NxBoxShape* boxParedeLateralPositivo = shapesParedeLateralPositivo[0]->isBox();
	NxVec3 dimensionsParedeLateralPositivo = boxParedeLateralPositivo->getDimensions();

	//Referencial obj: obj.x = global.y, obj.y = global.x
	boxCampo->setDimensions(NxVec3(fieldWidth/2. + 2.*dimensionsParedeLateralNegativo.x, fieldLength/2. + 2.*dimensionsParedeFundoNegativo.y, dimensionsCampo.z)); //padrao de eixos diferente do global
	NxVec3 posCampo = boxCampo->getGlobalPosition();

	//Referencial obj: obj.x = global.y, obj.y = global.x
	boxParedeFundoNegativo->setDimensions(NxVec3(fieldWidth/2. + 2.*dimensionsParedeLateralNegativo.x, dimensionsParedeFundoNegativo.y, dimensionsParedeFundoNegativo.z)); //padrao de eixos diferente do global
	NxVec3 posParedeFundoNegativo = boxParedeFundoNegativo->getGlobalPosition(); 
	boxParedeFundoNegativo->setGlobalPosition(NxVec3(-fieldLength/2. + posCampo.x - dimensionsParedeFundoNegativo.y, posParedeFundoNegativo.y, posParedeFundoNegativo.z));

	boxParedeFundoPositivo->setDimensions(NxVec3(fieldWidth/2. + 2.*dimensionsParedeLateralNegativo.x, dimensionsParedeFundoPositivo.y, dimensionsParedeFundoPositivo.z)); //padrao de eixos diferente do global
	NxVec3 posParedeFundoPositivo = boxParedeFundoPositivo->getGlobalPosition(); 
	boxParedeFundoPositivo->setGlobalPosition(NxVec3( fieldLength/2. - posCampo.x + dimensionsParedeFundoPositivo.y, posParedeFundoPositivo.y, posParedeFundoPositivo.z));

	boxParedeLateralNegativo->setDimensions(NxVec3(dimensionsParedeLateralNegativo.x, fieldLength/2. + 2.*dimensionsParedeFundoNegativo.y, dimensionsParedeLateralNegativo.z)); //padrao de eixos diferente do global
	NxVec3 posParedeLateralNegativo = boxParedeLateralNegativo->getGlobalPosition(); 
	boxParedeLateralNegativo->setGlobalPosition(NxVec3(posParedeLateralNegativo.x, -fieldWidth/2. + posCampo.y - dimensionsParedeLateralNegativo.x, posParedeLateralNegativo.z));

	boxParedeLateralPositivo->setDimensions(NxVec3(dimensionsParedeLateralPositivo.x, fieldLength/2. + 2.*dimensionsParedeFundoNegativo.y, dimensionsParedeLateralPositivo.z)); //padrao de eixos diferente do global
	NxVec3 posParedeLateralPositivo = boxParedeLateralPositivo->getGlobalPosition(); 
	boxParedeLateralPositivo->setGlobalPosition(NxVec3(posParedeLateralPositivo.x,  fieldWidth/2. - posCampo.y + dimensionsParedeLateralPositivo.x, posParedeLateralPositivo.z));

	//goals position and dimensions
	NxShape* const * shapesGolPositivoParedeFundo = this->actorGolPositivoParedeFundo->getShapes();
	NxBoxShape* boxGolPositivoParedeFundo = shapesGolPositivoParedeFundo[0]->isBox();
	NxVec3 dimensionsGolPositivoParedeFundo = boxGolPositivoParedeFundo->getDimensions();
	boxGolPositivoParedeFundo->setDimensions(NxVec3(goalWidth/2., dimensionsGolPositivoParedeFundo.y, goalHeigth/2.));
	dimensionsGolPositivoParedeFundo = boxGolPositivoParedeFundo->getDimensions();
	NxVec3 posGolPositivoParedeFundo = boxGolPositivoParedeFundo->getGlobalPosition();

	NxShape* const * shapesGolPositivoParedeNegativo = this->actorGolPositivoParedeNegativo->getShapes();
	NxBoxShape* boxGolPositivoParedeNegativo = shapesGolPositivoParedeNegativo[0]->isBox();
	NxVec3 dimensionsGolPositivoParedeNegativo = boxGolPositivoParedeNegativo->getDimensions();
	boxGolPositivoParedeNegativo->setDimensions(NxVec3(goalLength/2., dimensionsGolPositivoParedeNegativo.y, dimensionsGolPositivoParedeNegativo.z));
	dimensionsGolPositivoParedeNegativo = boxGolPositivoParedeNegativo->getDimensions();
	NxVec3 posGolPositivoParedeNegativo = boxGolPositivoParedeNegativo->getGlobalPosition();

	NxShape* const * shapesGolPositivoParedePositivo = this->actorGolPositivoParedePositivo->getShapes();
	NxBoxShape* boxGolPositivoParedePositivo = shapesGolPositivoParedePositivo[0]->isBox();
	NxVec3 dimensionsGolPositivoParedePositivo = boxGolPositivoParedePositivo->getDimensions();
	boxGolPositivoParedePositivo->setDimensions(NxVec3(goalLength/2., dimensionsGolPositivoParedePositivo.y, dimensionsGolPositivoParedePositivo.z));
	dimensionsGolPositivoParedePositivo = boxGolPositivoParedePositivo->getDimensions();
	NxVec3 posGolPositivoParedePositivo = boxGolPositivoParedePositivo->getGlobalPosition();

	boxGolPositivoParedeFundo->setGlobalPosition(NxVec3( linesLength/2. + 2.*dimensionsGolPositivoParedeNegativo.x, posGolPositivoParedeFundo.y, posGolPositivoParedeFundo.z ));
	boxGolPositivoParedeNegativo->setGlobalPosition(NxVec3( linesLength/2. + dimensionsGolPositivoParedeNegativo.x, -dimensionsGolPositivoParedeFundo.x, posGolPositivoParedeNegativo.z ));
	boxGolPositivoParedePositivo->setGlobalPosition(NxVec3( linesLength/2. + dimensionsGolPositivoParedeNegativo.x, +dimensionsGolPositivoParedeFundo.x, posGolPositivoParedePositivo.z ));

	NxShape* const * shapesGolNegativoParedeFundo = this->actorGolNegativoParedeFundo->getShapes();
	NxBoxShape* boxGolNegativoParedeFundo = shapesGolNegativoParedeFundo[0]->isBox();
	NxVec3 dimensionsGolNegativoParedeFundo = boxGolNegativoParedeFundo->getDimensions();
	boxGolNegativoParedeFundo->setDimensions(NxVec3(goalWidth/2., dimensionsGolNegativoParedeFundo.y, dimensionsGolNegativoParedeFundo.z));
	dimensionsGolNegativoParedeFundo = boxGolNegativoParedeFundo->getDimensions();
	NxVec3 posGolNegativoParedeFundo = boxGolNegativoParedeFundo->getGlobalPosition();

	NxShape* const * shapesGolNegativoParedeNegativo = this->actorGolNegativoParedeNegativo->getShapes();
	NxBoxShape* boxGolNegativoParedeNegativo = shapesGolNegativoParedeNegativo[0]->isBox();
	NxVec3 dimensionsGolNegativoParedeNegativo = boxGolNegativoParedeNegativo->getDimensions();
	boxGolNegativoParedeNegativo->setDimensions(NxVec3(goalLength/2., dimensionsGolNegativoParedeNegativo.y, dimensionsGolNegativoParedeNegativo.z));
	dimensionsGolNegativoParedeNegativo = boxGolNegativoParedeNegativo->getDimensions();
	NxVec3 posGolNegativoParedeNegativo = boxGolNegativoParedeNegativo->getGlobalPosition();

	NxShape* const * shapesGolNegativoParedePositivo = this->actorGolNegativoParedePositivo->getShapes();
	NxBoxShape* boxGolNegativoParedePositivo = shapesGolNegativoParedePositivo[0]->isBox();
	NxVec3 dimensionsGolNegativoParedePositivo = boxGolNegativoParedePositivo->getDimensions();
	boxGolNegativoParedePositivo->setDimensions(NxVec3(goalLength/2., dimensionsGolNegativoParedePositivo.y, dimensionsGolNegativoParedePositivo.z));
	dimensionsGolNegativoParedePositivo = boxGolNegativoParedePositivo->getDimensions();
	NxVec3 posGolNegativoParedePositivo = boxGolNegativoParedePositivo->getGlobalPosition();

	boxGolNegativoParedeFundo->setGlobalPosition(NxVec3( -linesLength/2. - 2.*dimensionsGolNegativoParedeNegativo.x, posGolNegativoParedeFundo.y, posGolNegativoParedeFundo.z ));
	boxGolNegativoParedeNegativo->setGlobalPosition(NxVec3( -linesLength/2. - dimensionsGolNegativoParedeNegativo.x, -dimensionsGolNegativoParedeFundo.x, posGolNegativoParedeNegativo.z ));
	boxGolNegativoParedePositivo->setGlobalPosition(NxVec3( -linesLength/2. - dimensionsGolNegativoParedeNegativo.x, +dimensionsGolNegativoParedeFundo.x, posGolNegativoParedePositivo.z ));
}
