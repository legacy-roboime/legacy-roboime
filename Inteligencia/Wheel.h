#pragma once
#include "Inteligencia.h"
#include "Component.h"

namespace Inteligencia {

	class Wheel : Component {
		friend class Robot;

	private:
		//fields:
		static float _radius; 
		real _speed;//current speed
		const real _angle;//wheel angle, it's not supposed to change on runtime

	public:
		//Wheel();
		Wheel(real ang = 0);//Constructor
		~Wheel();//Destructor

		//methods:
		void speed(real);
		real speed();
		real angle();
		static float radius();

	};
}