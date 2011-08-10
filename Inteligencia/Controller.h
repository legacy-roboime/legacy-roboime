#pragma once
#include "CXBOXController.h"
#include "Tactic.h"
#include "Move.h"

namespace Inteligencia {
	namespace Tactics {

		class Controller : public Tactic{
		private:
			int _id;
			double _x;
			double _y;
			double _ang;
			CXBOXController* _controller;
			Robot* _robot;
			Skills::Move * _move;
//		Skills::Kick * _kick;
//		Skills::Dribble * _dribble;
			double _speed;
				
		public:
			double set_x();
			double set_y();
			double set_ang();
			bool should_kick();
			void trigger_kick();
			bool should_dribble();
			void trigger_dribble();
			Controller(int controller_id, Robot*, Stage*, double speed);
			~Controller();
			void robot(Robot*);
			void step();
		};

	}	
}