#pragma once
#include <sstream>
#include <string>
#include <iostream>
#include "Update.h"
#include "Updater.h"

using namespace std;
namespace Inteligencia {

	class UpdateBall : public Update {

	private:
		int _i;
		double _x, _y;
		UpdateBall();//there's no point on doin this

	public:
		UpdateBall(int, double, double);
		~UpdateBall();
		void apply(Updater*);//go through the updaters list and apply the update
	};
}