#pragma once
#include "Inteligencia.h"
#include "Skill.h"
#include "Move.h"

namespace Inteligencia {
	namespace Skills {

		class Stir : public Skill {

		private:
			real angle, speed_x, speed_y;//required
			real ratio, omega, delta;//internal
			Move* move;

		public:
			Stir(Robot*);
			Stir(Robot*, real speed_x, real speed_y, real orientation);
			Stir(Robot*, real speed_x, real speed_y, real dx, real dy);
			~Stir();

			//methods:
			void step();//the actual algorithm
			void robot(Robot*);
			void rate(real);
			void set(real orientation);
			void set(real speed_x, real speed_y);
			void set(real speed_x, real speed_y, real orientation);
			void set(real speed_x, real speed_y, real dx, real dy);
		};
	}
}