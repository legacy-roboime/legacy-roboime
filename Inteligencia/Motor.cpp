#include "Motor.h"
namespace Inteligencia {

	Motor::Motor() {}

	Motor::Motor(double speed) {
		_speed = speed;
	}

	Motor::~Motor() {}

	void Motor::speed(double s) {
		_speed = s;
	}

	double Motor::speed() {
		return _speed;
	}

}