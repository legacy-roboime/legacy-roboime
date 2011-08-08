#pragma once
#include <deque>
#include "_Plays.h"
#include "Stage.h"

namespace Inteligencia
{
	class Minmax {

	private:
		deque<Play*> _plays;
		Stage* _current_state;
		
	public:
		Minmax();
		~Minmax();
		update_sim();

		find_best_play();
		

	}
}