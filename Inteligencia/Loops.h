#pragma once
#include "Inteligencia.h"
#include "Skill.h"

namespace Inteligencia {
	namespace Skills {
		namespace Loops {

			class Circle : public Skill {

			private:
				real cx, cy, r, s;//required
				real dx, dy, d, n, sintheta, costheta;//internal
				Move* move;

			public:
				Circle(Robot* r, real x, real y, real radius, real speed);
				~Circle();
				void set(real x, real y, real radius, real speed);
				void robot(Robot*);
				void step();
			};

		}
	}
}