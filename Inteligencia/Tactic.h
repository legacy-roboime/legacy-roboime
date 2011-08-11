#pragma once
#include "Inteligencia.h"
#include "Skill.h"
#include "Robot.h"
#include "Stage.h"

namespace Inteligencia {
	namespace Tactics {

		class Tactic {
		protected:
			Robot* _robot;
			Stage* _stage;

		public:
			Tactic(Robot*,Stage*);
			~Tactic();

			//methods:
			virtual void step() = 0;
			//setters:
			virtual void robot(Robot*);
			virtual void stage(Stage*);

		};
	}
}