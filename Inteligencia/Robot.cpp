#include "Robot.h"

//static elements instanciation:
list<Robot*> Robot::_robot;
list<int> Robot::__i;

//constructors/destructor:
Robot::Robot(void) {
	_init();
}

Robot::Robot(int index, Pose pose) {
	_init();
	_index = index;
	_pose = pose;
}

Robot::~Robot() {
	_robot.remove(this);
	int i = _i;
	__i.push_back(i);
	__i.sort();
}

//methods:
void Robot::_init(void) {
	if(__i.size() > 0) {
		_i = __i.front();
		__i.pop_front();
	} else {
		_i = _robot.size();
	}
	_robot.push_back(this);
	_yellow_card = false;
	_red_card = false;
	_index = -1;
	for(int i = 0; i < 4; i++) _wheel[i];
	_pose;
	_command;
	_dribbler;
	_kicker;
	_motor;
	_body;
}

bool Robot::can_kick() {
	return _kicker.is_active() && _kicker.is_working();
}

void Robot::kick() {
	int a = 0;
}

bool Robot::can_dribble() {
	return _dribbler.is_active() && _dribbler.is_working();
}

void Robot::start_dribbler() {
	_command.start_dribbler();
}

void Robot::stop_dribbler() {
	int a = 0;
}

bool Robot::is_working() {
	//if(dribbler.is_broken() ||
	return true;
}

bool Robot::is_broken() {
	return true;
}

void Robot::repair() {
	_dribbler.repair();
	_kicker.repair();
	_motor.repair();
	for (int i = 0; i < 4; i++)
		_wheel[i].repair();
	_body.repair();
	_working = true;
}

void Robot::break_down() {
	_working = false;
}