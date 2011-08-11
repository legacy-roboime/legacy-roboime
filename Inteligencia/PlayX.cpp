#include "PlayX.h"

namespace Inteligencia {

	PlayX::PlayX(void) : Play() {}

	PlayX::PlayX(char name[40]) : Play(name) {}

	PlayX::PlayX(Stage stage) : Play(stage) {}

	PlayX::~PlayX(void) {}
	//{puts("DESTROYEDX!!!!!");}
}