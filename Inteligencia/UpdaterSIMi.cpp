#include "UpdaterSIMi.h"
#include "Simulation.h"
#include "Update.h"
#include "UpdateBall.h"
#include "UpdateRobot.h"
#include "UpdaterSIM.h"

using namespace std;

namespace Inteligencia {

	UpdaterSIMi::UpdaterSIMi() : Updater() {
		_scene = 0;
	}

	UpdaterSIMi::UpdaterSIMi(int i) : Updater() {
		_scene = i;
	}

	UpdaterSIMi::~UpdaterSIMi() {}

	void UpdaterSIMi::receive() {
		//TODO: implement
	}

}