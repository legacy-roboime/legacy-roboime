#pragma once
#include "Inteligencia.h"
#include "Tactic.h"
#include "Stir.h"

namespace Inteligencia {
	namespace Tactics {

		class Goalkeeper : public Tactic {
		private:
			real _sx, _sy, _dx, _dy;//internal
			real _bspeed, _bang;//boosts(internal)
			real _speed;//base speed
			CXBOXController* _controller;
			Skills::Stir* _stir;
				
		public:
			Controller(Robot*, Stage*);
			~Controller();
			void robot(Robot*);
			void step();
		};

	}	
}