#include "UpdateBall.h"

namespace Inteligencia {

	UpdateBall::UpdateBall() : Update() {}

	UpdateBall::UpdateBall(int i, double x, double y) : Update() {
		_i = i;
		_x = x;
		_y = y;
	}

	UpdateBall::~UpdateBall() {}

	void UpdateBall::apply(Updater* u) {
		//for(int k=u->
	}

}