#pragma once
#include "Component.h"
namespace Inteligencia {

	class Motor : Component {
		friend class Robot;

	private:
		//fields:
		double _speed;//max speed of a wheel

	public:
		Motor(void);
		Motor(double);
		~Motor(void);

		//methods:
		void speed(double);
		double speed();

	};
}