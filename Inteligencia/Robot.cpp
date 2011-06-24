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
		delete command;
		delete dribbler;
		delete kicker;
		delete motor;
		delete body;
		for(int i=0; i<4; i++) delete wheel[i];
	}

	//setters:
	//TODO: low validation of setters
	void Robot::i(int i) {
		_i = i;
	}
	void Robot::yellow_card(int i) {
		_yellow_card = i;
	}
	void Robot::red_card(int i) {
		_red_card = i;
	}
	void Robot::add_yellow_card() {
		_yellow_card++;
	}
	void Robot::add_red_card() {
		_red_card++;
	}
	void Robot::x(double d) {
		_x = d;
	}
	void Robot::y(double d) {
		_y = d;
	}
	void Robot::angle(double d) {
		_angle = d;
	}
	void Robot::speed(double d) {
		_speed = d;
	}

	void Robot::place(double _x, double _y) {
		x(_x);
		y(_y);
	}

	void Robot::_init(void) {
		yellow_card(false);
		red_card(false);
		i(-1);
		x(0.);
		y(0.);
		speed(0.);
		angle(0.);
		command = new Command();
		dribbler = new Dribbler();
		kicker = new Kicker();
		motor = new Motor();
		body = new Body();
		for(int i=0; i<4; i++) wheel[4] = new Wheel();
	}

	bool Robot::can_kick() {
		return kicker->is_active() && kicker->is_working();
	}

	bool Robot::can_dribble() {
		return dribbler->is_active() && dribbler->is_working();
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
		dribbler->repair();
		kicker->repair();
		motor->repair();
		for (int i=0; i<4; i++) wheel[i]->repair();
		body->repair();
		_working = true;
	}

	void Robot::break_down() {
		_working = false;
	}
	
	void Robot::kick() {
		command->kick(kicker->speed());
	}

	void Robot::kick(double speed) {
		command->kick(speed);
	}

	void Robot::dribble() {
		command->dribble(dribbler->speed());
	}

	void Robot::dribble(double speed) {
		command->dribble(speed);
	}

	int Robot::i() {
		return _i;
	}

	int Robot::yellow_card() {
		return _yellow_card;
	}

	int Robot::red_card() {
		return _red_card;
	}

	double Robot::x() {
		return _x;
	}

	double Robot::y() {
		return _y;
	}

	double Robot::angle() {
		return _angle;
	}

	double Robot::speed() {
		return _speed;
	}

	double* Robot::place() {
		double p[] = {_x, _y};
		return p;
	}

}