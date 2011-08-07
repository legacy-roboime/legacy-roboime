#pragma once
#include <sstream>
#include <string>
#include <iostream>
#include "Update.h"
#include "Updater.h"

using namespace std;
namespace Inteligencia {

	class UpdateRobot : public Update {

	private:
		int _cc;//color code
		double _x, _y, _angle;
		UpdateRobot();//there's no point on doin this

	public:
		UpdateRobot(int cc, double x, double y, double angle);
		UpdateRobot(int cc, double x, double y, double angle, float confidence, double t_sent, double t_capture);
		~UpdateRobot();
		void apply(Updater*);//go through the updaters list and apply the update

	};
}