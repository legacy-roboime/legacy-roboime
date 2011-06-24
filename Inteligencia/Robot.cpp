#include "Robot.h"
namespace Inteligencia {

	//constructors/destructor:
	Robot::Robot(void) {
		_init();
	}

	Robot::Robot(int index) {
		_init();
		_i = index;
	}

	Robot::~Robot() {
		delete _command;
		delete _dribbler;
		delete _kicker;
		delete _motor;
		delete _body;
		for(int i=0; i<4; i++) delete _wheel[i];
	}

	//methods:
	void Robot::_init(void) {
		_yellow_card = false;
		_red_card = false;
		_i = -1;
		_x = 0.;
		_y = 0.;
		_speed = 0.;
		_angle = 0.;
		_command = new Command();
		_dribbler = new Dribbler();
		_kicker = new Kicker();
		_motor = new Motor();
		_body = new Body();
		for(int i=0; i<4; i++) _wheel[4] = new Wheel();
	}

	bool Robot::can_kick() {
		return _kicker->is_active() && _kicker->is_working();
	}

	bool Robot::can_dribble() {
		return _dribbler->is_active() && _dribbler->is_working();
	}

	bool Robot::is_working() {
		//TODO: implement
		return true;
	}

	bool Robot::is_broken() {
		//TODO: implement
		return false;
	}

	void Robot::repair() {
		_dribbler->repair();
		_kicker->repair();
		_motor->repair();
		for (int i = 0; i < 4; i++)
			_wheel[i]->repair();
		_body->repair();
		_working = true;
	}

	void Robot::break_down() {
		_working = false;
	}
	
	void Robot::kick() {
		_command->kick(_kicker->speed());
	}

	void Robot::kick(double speed) {
		_command->kick(speed);
	}

	void Robot::dribble() {
		_command->dribble(_dribbler->speed());
	}

	void Robot::dribble(double speed) {
		_command->dribble(speed);
	}

	void Robot::place(double x, double y) {
		_x = x;
		_y = y;
	}
}