#pragma once
#include "Skill.h"
#include "Move.h"

namespace Inteligencia {
	namespace Skills {

		class Stir : public Skill {

		private:
			double angle, speed_x, speed_y;//required
			double ratio, omega, delta;//internal
			Move* move;

		public:
			Stir(Robot*);
			Stir(Robot*, double speed_x, double speed_y, double orientation);
			Stir(Robot*, double speed_x, double speed_y, double dx, double dy);
			~Stir();

			//methods:
			void step();//the actual algorithm
			void robot(Robot*);
			void rate(double);
			void set(double orientation);
			void set(double speed_x, double speed_y);
			void set(double speed_x, double speed_y, double orientation);
			void set(double speed_x, double speed_y, double dx, double dy);
		};
	}
}