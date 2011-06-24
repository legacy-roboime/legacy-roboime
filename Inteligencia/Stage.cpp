#include "Stage.h"
namespace Inteligencia {

	Stage::Stage(void) {}

	Stage::Stage(Ball ball, Goal our_goal, Goal their_goal, Team our_team, Team their_team) {
		_ball = ball;
		_our_goal = our_goal;
		_their_goal = their_goal;
		_our_team = our_team;
		_their_team = their_team;
	}

	Stage::~Stage(void){}
}