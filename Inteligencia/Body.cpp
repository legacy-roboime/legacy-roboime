#include "Body.h"
namespace Inteligencia {

	Body::Body() {}

	Body::Body(double height, double radius) {
		_height = height;
		_radius = radius;
	}

	Body::~Body() {}

	void Body::height(double h) {
		_height = h;
	}

	double Body::height() {
		return _height;
	}

	void Body::radius(double r) {
		_radius = r;
	}

	double Body::radius() {
		return _radius;
	}

}