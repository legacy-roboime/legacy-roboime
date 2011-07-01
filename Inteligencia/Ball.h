#pragma once

namespace Inteligencia {

	class Ball {
		friend class UpdateBall;

	private:
		//fields:
		int _i;
		double _radius, _x, _y, _speedx, _speedy;

		//modifiers:
		void i(int);
		void radius(double);
		void x(double);
		void y(double);
		void speedx(double);//this has to be estimated somehow
		void speedy(double);//this has to be estimated somehow
		void place(double, double);//set x and y at once

	public:
		Ball();
		Ball(int, double r);
		//TODO: other constructors needed?
		~Ball();

		//getters:
		int i();
		double radius();
		double x();
		double y();
		double speedx();
		double speedy();

	};
}