#pragma once
#include "Inteligencia.h"
#include "Component.h"

namespace Inteligencia {

	class Dribbler : Component {
		friend class Robot;

	private:
		//fields:
		real _speed;//standard dribbling speed

	public:
		Dribbler(void);
		Dribbler(real force);
		~Dribbler(void);

		//methods:
		void speed(real);
		real speed();

	};
}