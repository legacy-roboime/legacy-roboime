#include "Ball.h"

namespace Inteligencia {

	Ball::Ball() {}

	Ball::Ball(int ii, real r) {
		i(ii);
		radius(r);
	}

	Ball::~Ball(void) {}

	void Ball::i(int ii) {
		_i = ii;
	}

	void Ball::radius(real d) {
		_radius = d;
	}

	void Ball::x(real d) {
		_x = d;
	}

	void Ball::y(real d) {
		_y = d;
	}

	void Ball::speedx(real d) {
		_speedx = d;
	}

	void Ball::speedy(real d) {
		_speedy = d;
	}

	void Ball::place(real d1, real d2) {
		x(d1);
		y(d2);
	}

	int Ball::i() {
		return _i;
	}

	real Ball::radius() {
		return _radius;
	}

	real Ball::x() {
		return _x;
	}

	real Ball::y() {
		return _y;
	}

	real Ball::speedx() {
		return _speedx;
	}

	real Ball::speedy() {
		return _speedy;
	}

}