#pragma once
#include "Inteligencia.h"

namespace Inteligencia {

	class Ball {
		friend class UpdateBall;

	private:
		//fields:
		int _i;
		real _radius, _x, _y, _speedx, _speedy;

		//modifiers:
		void i(int);
		void radius(real);
		void x(real);
		void y(real);
		void speedx(real);//this has to be estimated somehow
		void speedy(real);//this has to be estimated somehow
		void place(real, real);//set x and y at once

	public:
		Ball();
		Ball(int, real r);
		//TODO: other constructors needed?
		~Ball();

		//getters:
		int i();
		real radius();
		real x();
		real y();
		real speedx();
		real speedy();

	};
}