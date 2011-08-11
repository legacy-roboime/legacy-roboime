#pragma once
#include "Inteligencia.h"
#include "Component.h"

namespace Inteligencia {

	class Motor : Component {
		friend class Robot;

	private:
		//fields:
		real _speed;//max speed of a wheel

	public:
		Motor(void);
		Motor(real);
		~Motor(void);

		//methods:
		void speed(real);
		real speed();

	};
}