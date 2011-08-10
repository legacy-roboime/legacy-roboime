#pragma once
#include "CXBOXController.h"
#include "Tactic.h"
#include "Move.h"

namespace Inteligencia {
	namespace Tactics {

		class Controller : public Tactic{
		private:
			int id;
			CXBOXController* _controller;
			Robot* _robot;
			Skills::Move * _move;
			double _speed;
				
		public:
			Controller(int controller_id, Robot*, Stage*, double speed);
			~Controller();
			void robot(Robot*);
			void step();
		};

	}	
}