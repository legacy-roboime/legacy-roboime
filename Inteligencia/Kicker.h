#pragma once
#include "Inteligencia.h"
#include "Component.h"

namespace Inteligencia {

	class Kicker : Component {
		friend class Robot;

	private:
		//fields:
		real _speed;//standard kicking speed

	public:
		Kicker(void);
		Kicker(real force);
		~Kicker(void);

		//methods:
		void speed(real);
		real speed();

	};
}