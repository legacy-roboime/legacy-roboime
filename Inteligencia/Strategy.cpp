#include "Strategy.h"
#include "stdio.h"

//static elements instanciation:
Stage Strategy::__stage;
list<Strategy*> Strategy::_strategy;
list<int> Strategy::__i;

//constructors/destructor:
Strategy::Strategy(void) {
	_init();
}

Strategy::Strategy(char name[40]) {
	strcpy(_name, name);
}

Strategy::Strategy(Stage stage) {
	_init();
	_stage = stage;
}

Strategy::~Strategy(void) {
	_strategy.remove(this);
	int i = _i;
	__i.push_back(i);
	__i.sort();
	//puts("DESTROYED!!!!!");
}

//methods:
void Strategy::_init(void) {
	if(__i.size() > 0) {
		_i = __i.front();
		__i.pop_front();
	} else {
		_i = _strategy.size();
	}
	_strategy.push_back(this);
	_stage;
	_steps = 0;
	_active = true;
	_team_command;
}

void Strategy::_take_step() {
	//TODO: implement
}

void Strategy::change_stage(Stage stage) {
	//TODO: implement
}

void Strategy::set_global_stage(void) {
	//TODO: implement
}
void Strategy::take_step(void) {
	//TODO: implement
}