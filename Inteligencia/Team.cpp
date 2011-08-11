#include "Team.h"

namespace Inteligencia {

	void Team::_init() {
		yellow_card(0);
		red_card(0);
	}

	Team::Team(Color c) {
		_init();
		color(c);
	}

	Team::Team(Color c, deque<Robot*> t) {
		_init();
		add(t);
		color(c);
	}

	Team::~Team() {
		//delete _robot;//TODO: think about it
	}

	void Team::color(Color c) {
		_color = c;
	}

	void Team::yellow_card(int i) {
		_yellow_card = i;
	}

	void Team::red_card(int i) {
		_red_card = i;
	}

	void Team::add_yellow_card() {
		_yellow_card++;
	}

	void Team::add_red_card() {
		_red_card++;
	}

	int Team::yellow_card() {
		return _yellow_card;
	}

	int Team::red_card() {
		return _red_card;
	}

	Color Team::color() {
		return _color;
	}

	void Team::add(Robot* r) {
		_robot.push_back(r);
	}

	void Team::add(deque<Robot*> d) {
		while(!d.empty()) {
			_robot.push_back(d.back());
			d.pop_back();
		}
	}

	//used on sort
	bool comp(Robot* r1, Robot* r2) {return r1->id() < r2->id();}

	//void Team::sort() {
		//_robot.sort(comp);
		//TODO: consider removing this method.
	//}

}