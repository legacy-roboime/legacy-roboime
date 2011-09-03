#include "Wheel.h"

namespace Inteligencia {
	float Wheel::_radius = 27.6;

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

	float Wheel::radius() {
		return _radius;
	}

}