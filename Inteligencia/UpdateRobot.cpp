#include "UpdateRobot.h"

namespace Inteligencia {

	UpdateRobot::UpdateRobot() {}

	UpdateRobot::UpdateRobot(int i, double x, double y, double a) {
		_i = i;
		_x = x;
		_y = y;
		_angle = a;
	}

	UpdateRobot::~UpdateRobot() {}

	void UpdateRobot::apply(Updater* u) {
		//for(int i=
	}

}