#pragma once
#include "Inteligencia.h"
#include "Team.h"
#include "Ball.h"
#include "Goal.h"

namespace Inteligencia {

	class Stage {

	private:
		//fields:
		Ball* _ball;
		Goal* _our_goal;
		Goal* _their_goal;//our_goal must be defended their_goal must be attacked
		//Team t;
		Team* _our_team;
		Team* _their_team;

	public:
		Stage();
		Stage(Ball* ball, Goal* our_goal, Goal* their_goal, Team* our_team, Team* their_team);
		~Stage();

	};
}