#include "Wheel.h"
namespace Inteligencia {

	Wheel::Wheel() {}

	Wheel::Wheel(double speed) {
		_speed = speed;
	}

	Wheel::~Wheel() {}

	void Wheel::speed(double s) {
		_speed = s;
	}

	double Wheel::speed() {
		return _speed;
	}

}