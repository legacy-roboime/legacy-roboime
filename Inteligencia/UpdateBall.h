#pragma once
#include "Inteligencia.h"
#include <sstream>
#include <string>
#include <iostream>
#include "Update.h"
#include "Updater.h"

namespace Inteligencia {

	class UpdateBall : public Update {

	private:
		real _x, _y;
		UpdateBall();//there's no point on doin this

	public:
		UpdateBall(real x, real y);
		UpdateBall(real x, real y, float confidence, double t_sent, double t_capture);
		~UpdateBall();
		void apply(Updater*);//go through the updaters list and apply the update
	};
}