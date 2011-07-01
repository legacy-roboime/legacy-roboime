#pragma once

namespace Inteligencia {

	class Ball {

	private:
		//fields:
		double _radius, _position[3], _speed[3], _accel[3];

	public:
		Ball();
		Ball(double radius, double position[3]);
		Ball(double radius, double position[3], double speed[3]);
		Ball(double radius, double position[3], double speed[3], double accel[3]);
		~Ball();

	};
}