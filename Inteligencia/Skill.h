#pragma once
#include "Inteligencia.h"
#include "Robot.h"

namespace Inteligencia {
	namespace Skills {

		class Skill {
		protected:
			Robot* _robot;

		public:
			Skill(Robot*);
			~Skill();

			//methods:
			virtual void step() = 0;
			//setters:
			virtual void robot(Robot*);

		};
	}
}