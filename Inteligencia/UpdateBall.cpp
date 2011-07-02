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
		for(size_t k=u->balls(); k>0; k--) {
			if(u->ball(k-1)->i()==_i) {
				u->ball(k-1)->x(_x);
				u->ball(k-1)->y(_y);
			}
		}
	}

}