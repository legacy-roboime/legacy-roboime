//#include "Component.h"
#include "Dribbler.h"
namespace Inteligencia {

	Dribbler::Dribbler() {}

	Dribbler::Dribbler(double speed) {
		_speed = speed;
	}

	Dribbler::~Dribbler() {}

	void Dribbler::speed(double s) {
		_speed = s;
	}

	double Dribbler::speed() {
		return _speed;
	}

}