#pragma once
#include "Inteligencia.h"
#include <sstream>
#include <string>
#include <iostream>
#include "Update.h"
#include "Updater.h"

namespace Inteligencia {

	class UpdateRobot : public Update {

	private:
		int _cc;//color code
		real _x, _y, _angle;
		UpdateRobot();//there's no point on doin this

	public:
		UpdateRobot(int cc, real x, real y, real angle);
		UpdateRobot(int cc, real x, real y, real angle, float confidence, double t_sent, double t_capture);
		~UpdateRobot();
		void apply(Updater*);//go through the updaters list and apply the update

	};
}