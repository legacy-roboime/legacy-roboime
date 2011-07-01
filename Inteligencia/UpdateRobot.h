#pragma once
#include <sstream>
#include <string>
#include <iostream>
#include "Update.h"

using namespace std;
namespace Inteligencia {

	class UpdateRobot : public Update {

	private:
		int _i;
		double _x, _y, _angle;
		UpdateRobot();//there's no point on doin this

	public:
		UpdateRobot(int, double, double, double);
		~UpdateRobot();
		void apply(Updater*);//go through the updaters list and apply the update
	};
}