#pragma once
#include "Skill.h"
#include "Move.h"

namespace Inteligencia {
	namespace Skills {

		class Stir : public Skill {

		private:
			double angle;//required
			double r, omega;//internal
			Move* move;

		public:
			Stir(Robot*);
			Stir(Robot*, double speed_x=0.0, double speed_y=0.0, double orientation=0.0);
			Stir(Robot*, double speed_x=0.0, double speed_y=0.0, double dx=0.0, double dy=0.0);
			~Stir();

			//methods:
			void step();//the actual algorithm
			void rate(double);
			void set(double speed_x=0.0, double speed_y=0.0);
			void set(double speed_x=0.0, double speed_y=0.0, double orientation=0.0);
		};
	}
}