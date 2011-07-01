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
		for(unsigned int k=u->robots(); k>0; k--) {
			if(u->robot(k-1)->i()==_i) {
				u->robot(k-1)->x(_x);
				u->robot(k-1)->y(_y);
				u->robot(k-1)->angle(_angle);
			}
		}
	}

}