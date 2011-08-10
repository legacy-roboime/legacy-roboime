#include "Stir.h"
#include <cmath>

namespace Inteligencia {
	namespace Skills {

		Stir::Stir(Robot* r) : Skill(r) {
			angle = 0;
		}

		Stir::Stir(Robot* r, double sx, double sy, double o) : Skill(r) {
			move->set(sx,sy,o);

		}

		Stir::Stir(Robot* r, double sx, double sy, double dx, double dy) : Skill(r) {
		}

		Stir::~Stir() {
			delete move;
		}

		void Stir::rate(double d) {
			r = d;
		}

		void Stir::step() {
			//2*PI
		}

		void Stir::set(double sx, double sy){}

		void Stir::set(double sx, double sy, double o){}
	}
}