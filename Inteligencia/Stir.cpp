#include "Stir.h"
#include <cmath>
#define M_2PI	6.2831853071795865
#define M_PI	3.1415926535897932
#define __q(x)	((x) > M_PI ? (x) - M_2PI : -(x) > M_PI ? (x) + M_2PI : (x))
real __n(real ang) {return ang > M_PI ? __n(ang - M_2PI) : -ang > M_PI ? __n(ang + M_2PI) : ang;}

namespace Inteligencia {
	namespace Skills {

		Stir::Stir(Robot* r) : Skill(r) {
			ratio = .05;
			move = new Move(r);
			set(0.0,0.0,0.0);
		}

		Stir::Stir(Robot* r, real sx, real sy, real o) : Skill(r) {
			ratio = .05;
			move = new Move(r);
			set(sx,sy,o);
		}

		Stir::Stir(Robot* r, real sx, real sy, real dx, real dy) : Skill(r) {
			ratio = .05;
			move = new Move(r);
			set(sx,sy,dx,dy);
		}

		Stir::~Stir() {
			delete move;
		}

		void Stir::rate(real d) {
			ratio = d;
		}

		void Stir::robot(Robot* r) {
			move->robot(r);
		}

		void Stir::step() {
			omega = __q(angle - _robot->angle());
			move->set(speed_x, speed_y, ratio * omega);
			move->step();
		}

		void Stir::set(real sx, real sy) {
			speed_x = sx;
			speed_y = sy;
		}

		void Stir::set(real sx, real sy, real o) {
			speed_x = sx;
			speed_y = sy;
			angle = o;
		}

		void Stir::set(real sx, real sy, real dx, real dy) {
			speed_x = sx;
			speed_y = sy;
			real a = atan2(dy,dx);
			angle = a < 0 ? M_2PI + a : a;
		}
	}
}