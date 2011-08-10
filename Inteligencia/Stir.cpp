#include "Stir.h"
#include <cmath>
#define M_2PI	6.2831853071795865
#define M_PI	3.1415926535897932

double n(double ang) {return ang > M_PI ? n(ang - M_2PI) : -ang > M_PI ? n(ang + M_2PI) : ang;}
namespace Inteligencia {
	namespace Skills {

		Stir::Stir(Robot* r) : Skill(r) {
			ratio = .05;
			move = new Move(r);
			set(0.0,0.0,0.0);
		}

		Stir::Stir(Robot* r, double sx, double sy, double o) : Skill(r) {
			ratio = .05;
			move = new Move(r);
			set(sx,sy,o);
		}

		Stir::Stir(Robot* r, double sx, double sy, double dx, double dy) : Skill(r) {
			ratio = .05;
			move = new Move(r);
			set(sx,sy,dx,dy);
		}

		Stir::~Stir() {
			delete move;
		}

		void Stir::rate(double d) {
			ratio = d;
		}

		void Stir::robot(Robot* r) {
			move->robot(r);
		}

		void Stir::step() {
			delta = angle - _robot->angle();
			omega = n(delta);
			move->set(speed_x, speed_y, ratio * omega);
			move->step();
		}

		void Stir::set(double sx, double sy) {
			speed_x = sx;
			speed_y = sy;
		}

		void Stir::set(double sx, double sy, double o) {
			speed_x = sx;
			speed_y = sy;
			angle = o;
		}

		void Stir::set(double sx, double sy, double dx, double dy) {
			speed_x = sx;
			speed_y = sy;
			double a = atan2(dy,dx);
			angle = a < 0 ? M_2PI + a : a;
		}
	}
}