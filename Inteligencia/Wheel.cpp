#include "Wheel.h"
namespace Inteligencia {

	/*Wheel::Wheel() {
		_angle = 0;
	}*/

	Wheel::Wheel(double d) : _angle(d) {}

	Wheel::~Wheel() {}

	void Wheel::speed(double d) {
		_speed = d;
	}

	double Wheel::speed() {
		return _speed;
	}

	double Wheel::angle() {
		return _angle;
	}

}