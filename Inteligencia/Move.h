#pragma once
#include "Skill.h"

namespace Inteligencia {
	namespace Skills {

		class Move : public Skill {

		private:
			double speed_x, speed_y, speed_ang;//required
			double speed[4], theta, alpha;//internal

		public:
			//Move(Robot*);
			Move(Robot*,double speed_x=0.0, double speed_y=0.0, double speed_ang=0.0);
			~Move();

			//methods:
			void step();//the actual algorithm
			void set(double speed_x=0.0, double speed_y=0.0, double speed_ang=0.0);
		};
	}
}