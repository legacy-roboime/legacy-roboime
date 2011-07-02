#include "_Skills.h"

namespace Inteligencia {
	namespace Skills {

		Move::Move(Robot* r) : Skill(r) {}

		Move::Move(Robot* r, double sx, double sy, double sa) : Skill(r) {
			set(sx, sy, sa);
		}

		Move::~Move() {}

		void Move::set(double sx, double sy, double sa) {
			speed_x = sx; speed_y = sy; speed_ang = sa;
		}

		void Move::step() {
			theta = _robot->angle();
			//NOTE this is made for a 4 wheels robot, different number of wheels need some restructuring
			for(int i=0; i<4; i++) {
				alpha = _robot->wheel[i]->angle();
				speed[i] = cos(alpha)*(speed_y*cos(theta) - speed_x*sin(theta))
						 - sin(alpha)*(speed_x*cos(theta) + speed_y*sin(theta))
						 + speed_ang*_robot->body->radius();
			}
			//TODO: implement speed limit to smoothen movement
			_robot->command(speed);
		}

	}
}