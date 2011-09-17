#include "UpdateRobot.h"
#include <iostream>

namespace Inteligencia {

	UpdateRobot::UpdateRobot() : Update() {}

	UpdateRobot::UpdateRobot(int i, real x, real y, real a) : Update() {
		_cc = i;
		_x = x;
		_y = y;
		_angle = a;
	}

	UpdateRobot::UpdateRobot(int cc, real x, real y, real a, float c, double t1, double t2) : Update(c,t1,t2) {
		_cc = cc;
		_x = x;
		_y = y;
		_angle = a;
	}

	UpdateRobot::~UpdateRobot() {}

	void UpdateRobot::apply(Updater* u) {
		//cout << to_string() << endl;//test
		for(size_t k=u->robots(); k>0; k--) {
			if(u->robot(k-1)->cc()==_cc) {
				u->robot(k-1)->x(_x);
				u->robot(k-1)->y(_y);
				u->robot(k-1)->angle(_angle);
			}
		}
	}

	string UpdateRobot::to_string() {
		stringstream out;
		out << "UpdateRobot: [" << _cc << _x << _y << _angle << "]";
		return out.str();
	}

}