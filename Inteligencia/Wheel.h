#pragma once
#include "Component.h"
namespace Inteligencia {

	class Wheel : Component {
		friend class Robot;

	private:
		//fields:
		double _speed;//current speed

	public:
		Wheel();
		Wheel(double);//Constructor
		~Wheel();//Destructor

		//methods:
		void speed(double);
		double speed();

	};
}