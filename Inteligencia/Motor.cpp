#include "Motor.h"

namespace Inteligencia {

	Motor::Motor() {}

	Motor::Motor(real speed) {
		_speed = speed;
	}

	Motor::~Motor() {}

	void Motor::speed(real s) {
		_speed = s;
	}

	real Motor::speed() {
		return _speed;
	}

}