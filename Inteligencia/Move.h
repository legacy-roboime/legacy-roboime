#pragma once
#include "Inteligencia.h"
#include "Skill.h"

namespace Inteligencia {
	namespace Skills {

		class Move : public Skill {

		private:
			real speed_x, speed_y, speed_ang;//required
			real speed[4], theta, alpha;//internal

		public:
			//Move(Robot*);
			Move(Robot*,real speed_x=0.0, real speed_y=0.0, real speed_ang=0.0);
			~Move();

			//methods:
			void step();//the actual algorithm
			void set(real speed_x=0.0, real speed_y=0.0, real speed_ang=0.0);
		};
	}
}