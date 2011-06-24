//#include "Component.h"
#include "Kicker.h"
namespace Inteligencia {

	Kicker::Kicker() {}

	Kicker::Kicker(double speed) {
		_speed = speed;
	}

	Kicker::~Kicker() {}

	void Kicker::speed(double s) {
		_speed = s;
	}

	double Kicker::speed() {
		return _speed;
	}

}