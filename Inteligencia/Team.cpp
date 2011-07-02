#include "Team.h"

namespace Inteligencia {

	void Team::_init() {
		_i = 0;
	}

	Team::Team() {
		_init();
	}

	Team::Team(deque<Robot*> team) {
		_init();
		_robot = team;
	}

	Team::~Team() {
		//delete _robot;//TODO: think about it
	}

	//setters:
	void Team::i(int i) {
		_i = i;
	}

	//getters:
	int Team::i() {
		return _i;
	}

	//useful:
	void Team::add(Robot* r) {
		_robot.push_back(r);
	}

	//used on sort
	bool comp(Robot* r1, Robot* r2) {return r1->i() < r2->i();}

	//void Team::sort() {
		//_robot.sort(comp);
		//TODO: consider removing this method.
	//}

}