#pragma once
#include "Component.h"
namespace Inteligencia {

	class Kicker : Component {
		friend class Robot;

	private:
		//fields:
		double _speed;//standard kicking speed

	public:
		Kicker(void);
		Kicker(double force);
		~Kicker(void);

		//methods:
		void speed(double);
		double speed();

	};
}