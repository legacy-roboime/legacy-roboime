#include "Kicker.h"

namespace Inteligencia {

	Kicker::Kicker() {}

	Kicker::Kicker(real speed) {
		_speed = speed;
	}

	Kicker::~Kicker() {}

	void Kicker::speed(real s) {
		_speed = s;
	}

	real Kicker::speed() {
		return _speed;
	}

}