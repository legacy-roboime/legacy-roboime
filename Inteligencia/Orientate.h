#pragma once
#include "Skill.h"

namespace Inteligencia {
	namespace Skills {

		class OMove : public Skill {

		private:
			double _angle;//required
			double //internal
			Move* move;

		public:
			OMove(Robot*);
			OMove(Robot*, double orientation);
			OMove(Robot*, double dx, double dy);
			~Move();

			//methods:
			void step();//the actual algorithm
			void set(double speed_x=0.0, double speed_y=0.0, double orientation=0.0);
		};
	}
}