#include "Play.h"

namespace Inteligencia {

	//static elements instanciation:
	Stage Play::__stage;
	list<Play*> Play::_play;
	list<unsigned int> Play::__i;

	//constructors/destructor:
	Play::Play(void) {
		_init();
	}

	Play::Play(string name) {
		_name = name;
	}

	Play::Play(Stage stage) {
		_init();
		_stage = stage;
	}

	Play::~Play(void) {
		//FIXME: this is wrong
		_play.remove(this);
		unsigned int i = _i;
		__i.push_back(i);
		__i.sort();
		//puts("DESTROYED!!!!!");
	}

	//methods:
	void Play::_init(void) {
		if(__i.size() > 0) {
			_i = __i.front();
			__i.pop_front();
		} else {
			_i = _play.size();
		}
		_play.push_back(this);
		_stage;
		_steps = 0;
		_active = true;
	}

	void Play::_take_step() {
		//TODO: implement
	}

	void Play::change_stage(Stage stage) {
		//TODO: implement
	}

	void Play::set_global_stage(void) {
		//TODO: implement
	}
	void Play::take_step(void) {
		//TODO: implement
	}
}