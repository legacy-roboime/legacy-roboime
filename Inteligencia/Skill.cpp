#include "Skill.h"
namespace Inteligencia {
	namespace Skills {

		Skill::Skill(Robot* r) {
			robot(r);
		}

		Skill::~Skill() {}

		void Skill::robot(Robot* r) {
			_robot = r;
		}

	}
}