#include "stdio.h"
#include "Play.h"
namespace Inteligencia {


	//static elements instanciation:
	Stage Play::__stage;
	list<Play*> Play::_play;
	list<int> Play::__i;

	//constructors/destructor:
	Play::Play(void) {
		_init();
	}

	Play::Play(char name[40]) {
		//strcpy(_name, name);
		strcpy_s(_name, name);
	}

	Play::Play(Stage stage) {
		_init();
		_stage = stage;
	}

	Play::~Play(void) {
		_play.remove(this);
		int i = _i;
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