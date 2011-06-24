#include "Ball.h"
namespace Inteligencia {

	Ball::Ball(void) {}

	Ball::Ball(double radius, double position[3]) {
		_radius = radius;
		for(int i = 0; i < 3; i++) {
			_position[i] = position[i];
		}
	}

	Ball::Ball(double radius, double position[3], double speed[3]) {
		_radius = radius;
		for(int i = 0; i < 3; i++) {
			_position[i] = position[i];
			_speed[i] = speed[i];
		}
	}

	Ball::Ball(double radius, double position[3], double speed[3], double accel[3]) {
		_radius = radius;
		for(int i = 0; i < 3; i++) {
			_position[i] = position[i];
			_speed[i] = speed[i];
			_accel[i] = accel[i];
		}
	}

	Ball::~Ball(void) {}
}