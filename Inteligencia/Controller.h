#pragma once
#include "CXBOXController.h"
#include "Tactic.h"
#include "Stir.h"

namespace Inteligencia {
	namespace Tactics {

		class Controller : public Tactic {
		private:
			int _id;
			double _sx, _sy, _dx, _dy;//internal
			double _bspeed, _bang;//boosts(internal)
			double _speed;//base speed
			CXBOXController* _controller;
			Robot* _robot;
			Skills::Stir* _stir;
				
		public:
			Controller(int controller_id, Robot*, Stage*, double speed);
			~Controller();
			void robot(Robot*);
			void step();
		};

	}	
}