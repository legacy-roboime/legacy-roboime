#pragma once
#include "Skill.h"

namespace Inteligencia {
	namespace Skills {
		namespace Loops {

			class Circle : public Skill {

			private:
				double cx, cy, r, s;//required
				double dx, dy, d, n, sintheta, costheta;//internal
				Move* move;

			public:
				Circle(Robot* r, double x, double y, double radius, double speed);
				~Circle();
				void set(double x, double y, double radius, double speed);
				void robot(Robot*);
				void step();
			};

		}
	}
}