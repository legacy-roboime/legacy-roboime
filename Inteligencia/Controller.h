#pragma once
#include "CXBOXController.h"
#include "Tactic.h"
#include "Move.h"

namespace Inteligencia {
	class Controller : public Tactic{
		private:
			int id;
			CXBOXController* controller;
			Robot* r;
			Skills::Move * move;
			double v_max;
			

		public:
			Controller(int id, Robot* r, double speed);
			~Controller();
			void robot(Robot*);
			int step();
		};
	
}