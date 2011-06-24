#include "Team.h"
namespace Inteligencia {

	Team::Team(void) {}

	Team::Team(Robot robot[5]) {
		for(int i = 0; i < 5; i++) _robot[i] = robot[i];
	}

	Team::~Team(void) {}
}