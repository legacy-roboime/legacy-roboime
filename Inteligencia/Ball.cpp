#include "Ball.h"
namespace Inteligencia {

	Ball::Ball() {}

	Ball::Ball(int ii, double r) {
		i(ii);
		radius(r);
	}

	Ball::~Ball(void) {}

	void Ball::i(int ii) {
		_i = ii;
	}

	void Ball::radius(double d) {
		_radius = d;
	}

	void Ball::x(double d) {
		_x = d;
	}

	void Ball::y(double d) {
		_y = d;
	}

	void Ball::speedx(double d) {
		_speedx = d;
	}

	void Ball::speedy(double d) {
		_speedy = d;
	}

	void Ball::place(double d1, double d2) {
		x(d1);
		y(d2);
	}

	int Ball::i() {
		return _i;
	}

	double Ball::radius() {
		return _radius;
	}

	double Ball::x() {
		return _x;
	}

	double Ball::y() {
		return _y;
	}

	double Ball::speedx() {
		return _speedx;
	}

	double Ball::speedy() {
		return _speedy;
	}

}