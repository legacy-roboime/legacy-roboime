#include "Tactic.h"

namespace Inteligencia {
	namespace Tactics {

		Tactic::Tactic(Robot* r, Stage* s) {
			robot(r);
			stage(s);
		}

		Tactic::~Tactic() {}

		void Tactic::robot(Robot* r) {
			_robot = r;
		}

		void Tactic::stage(Stage* s) {
			_stage = s;
		}

	}
}