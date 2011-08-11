#include "Wheel.h"

namespace Inteligencia {

	/*Wheel::Wheel() {
		_angle = 0;
	}*/

	Wheel::Wheel(real d) : _angle(d) {}

	Wheel::~Wheel() {}

	void Wheel::speed(real d) {
		_speed = d;
	}

	real Wheel::speed() {
		return _speed;
	}

	real Wheel::angle() {
		return _angle;
	}

}