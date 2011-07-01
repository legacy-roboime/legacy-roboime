#pragma once
#include "Component.h"
namespace Inteligencia {

	class Wheel : Component {
		friend class Robot;

	private:
		//fields:
		double _speed;//current speed
		const double _angle;//wheel angle, it's not supposed to change on runtime

	public:
		//Wheel();
		Wheel(double ang = 0);//Constructor
		~Wheel();//Destructor

		//methods:
		void speed(double);
		double speed();
		double angle();

	};
}