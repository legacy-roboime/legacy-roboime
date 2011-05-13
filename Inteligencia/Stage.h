#pragma once
#include "Ball.h"
#include "Goal.h"
#include "Team.h"

class Stage {

private:
	//fields:
	Ball _ball;
	Goal _our_goal, _their_goal;//our_goal must be defended their_goal must be attacked
	Team _our_team, _their_team;

public:
	Stage(void);
	Stage(Ball ball, Goal our_goal, Goal their_goal, Team our_team, Team their_team);
	~Stage(void);

};