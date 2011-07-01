#include "UpdateRobot.h"

namespace Inteligencia {

	UpdateRobot::UpdateRobot() : Update() {}

	UpdateRobot::UpdateRobot(int i, double x, double y, double a) : Update() {
		_i = i;
		_x = x;
		_y = y;
		_angle = a;
	}

	UpdateRobot::~UpdateRobot() {}

	void UpdateRobot::apply(Updater* u) {
		for(int k=u->robots()-1; k>=0; k--) {
			if(u->robot(k)->i()==_i) {
				u->robot(k)->x(_x);
				u->robot(k)->y(_y);
				u->robot(k)->angle(_angle);
			}
		}
	}

}