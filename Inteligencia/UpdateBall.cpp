#include "UpdateBall.h"

namespace Inteligencia {

	UpdateBall::UpdateBall() : Update() {}

	UpdateBall::UpdateBall(real x, real y) : Update() {
		_x = x;
		_y = y;
	}

	UpdateBall::UpdateBall(real x, real y, float c, double t1, double t2) : Update(c,t1,t2) {
		_x = x;
		_y = y;
	}

	UpdateBall::~UpdateBall() {}

	void UpdateBall::apply(Updater* u) {
		for(size_t k=u->balls(); k>0; k--) {
			//TODO: identify which ball is which
			//if(u->ball(k-1)->i()==_i) {
				u->ball(k-1)->x(_x);
				u->ball(k-1)->y(_y);
			//}
		}
	}

}