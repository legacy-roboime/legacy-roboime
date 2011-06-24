#pragma once
#include "Component.h"
namespace Inteligencia {

	class Dribbler : Component {
		friend class Robot;

	private:
		//fields:
		double _speed;//standard dribbling speed

	public:
		Dribbler(void);
		Dribbler(double force);
		~Dribbler(void);

		//methods:
		void speed(double);
		double speed();

	};
}