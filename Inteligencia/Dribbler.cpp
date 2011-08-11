#include "Dribbler.h"

namespace Inteligencia {

	Dribbler::Dribbler() {}

	Dribbler::Dribbler(real speed) {
		_speed = speed;
	}

	Dribbler::~Dribbler() {}

	void Dribbler::speed(real s) {
		_speed = s;
	}

	real Dribbler::speed() {
		return _speed;
	}

}