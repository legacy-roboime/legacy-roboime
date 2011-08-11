#include "Body.h"

namespace Inteligencia {

	Body::Body() {}

	Body::Body(real height, real radius) {
		_height = height;
		_radius = radius;
	}

	Body::~Body() {}

	void Body::height(real h) {
		_height = h;
	}

	real Body::height() {
		return _height;
	}

	void Body::radius(real r) {
		_radius = r;
	}

	real Body::radius() {
		return _radius;
	}

}