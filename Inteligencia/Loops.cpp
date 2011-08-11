#include "_Skills.h"

namespace Inteligencia {
	namespace Skills {
		namespace Loops {

			Circle::Circle(Robot* r, real x, real y, real radius, real speed) : Skill(r) {
				set(x,y,radius,speed);
				move = new Move(r,speed);
			}

			Circle::~Circle() {
				delete move;
			}

			void Circle::set(real x, real y, real radius, real speed) {
				cx = x; cy = y; r = radius; s = speed;
			}

			void Circle::robot(Robot* r) {
				move->robot(r);
			}

			void Circle::step() {
				dx = cx - _robot->x();
				dy = cy - _robot->y();
				n = dx*dx + dy*dy;
				if(n>=r*r) {
					d = sqrt(n - r*r);
					costheta = (dx*d + dy*r)/n;
					sintheta = (dy*d - dx*r)/n;
					move->set(abs(s)*costheta, abs(s)*sintheta);
				}
				move->step();
			}

		}
	}
}