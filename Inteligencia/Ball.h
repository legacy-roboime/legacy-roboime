#pragma once

namespace Inteligencia {

	class Ball {
		friend class UpdateBall;

	private:
		//fields:
		double _radius, _x, _y, _speedx, _speedy;

		//modifiers:
		void radius(double);
		void x(double);
		void y(double);
		void speedx(double);//this has to be estimated somehow
		void speedy(double);//this has to be estimated somehow
		void place(double, double);//set x and y at once

	public:
		Ball();
		Ball(double r);
		//TODO: other constructors needed?
		~Ball();

		//getters:
		double radius();
		double x();
		double y();
		double speedx();
		double speedy();

	};
}