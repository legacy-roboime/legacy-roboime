#include "Robot.h"
#include <sstream>

namespace Inteligencia {

	void Robot::_init(void) {
		yellow_card(false);
		red_card(false);
		i(-1);
		_command = new Command(_i);
		_dribbler = new Dribbler();
		_kicker = new Kicker();
		_motor = new Motor();
		_body = new Body(150, 90);
		_wheel[0] = new Wheel(-1.02260);
		_wheel[1] = new Wheel( 0.96706);
		_wheel[2] = new Wheel( 2.32842);
		_wheel[3] = new Wheel(-2.38397);
	}

	Robot::Robot(void) {
		_init();
	}

	Robot::Robot(int index) {
		_init();
		_i = index;
	}

	Robot::~Robot() {
		//TODO: think about commander memory allocation
		delete _command;
		delete _dribbler;
		delete _kicker;
		delete _motor;
		delete _body;
		for(int i=0; i<4; i++) delete _wheel[i];
	}

	Dribbler* Robot::dribbler() {
		return _dribbler;
	}

	Kicker* Robot::kicker() {
		return _kicker;
	}

	Motor* Robot::motor() {
		return _motor;
	}

	Body* Robot::body() {
		return _body;
	}

	Wheel** Robot::wheel() {
		return _wheel;
	}

	size_t Robot::wheels() {
		return (size_t) 4;//TODO: make this flexible
	}
	//setters:
	//TODO: validation
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

	void Robot::speedx(double d) {
		_speedx = d;
	}

	void Robot::speedy(double d) {
		_speedy = d;
	}

	void Robot::place(double _x, double _y) {
		x(_x);
		y(_y);
	}

	string Robot::_summary() {
		stringstream out;
		out << "x: " << x() << endl;
		out << "y: " << y() << endl;
		out << "angle: " << angle() << endl;
		return out.str();
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
		for (int i=0; i<4; i++) _wheel[i]->repair();
		_body->repair();
		_working = true;
	}

	void Robot::break_down() {
		_working = false;
	}

	string Robot::summary() {
		stringstream out;
		out << "Summary:" << endl;
		out << _summary() << endl;
		return out.str();
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

	double Robot::speedx() {
		return _speedx;
	}

	double Robot::speedy() {
		return _speedy;
	}

	//double* Robot::place() {
	//	double p[] = {_x, _y};
	//	return p;
	//}

	void Robot::command(Command* c) {
		_command = c;
		c->i(i());
	}

	void Robot::command(double s[4]) {
		_command->wheels(s);
	}

	void Robot::command(double w0, double w1, double w2, double w3) {
		_command->wheels(w0, w1, w2, w3);
	}
	
	//void Robot::commander(Commander* c) {
	//	c->add(this);
	//}

	//void Robot::updater(Updater* u) {
	//	_updater = u;
	//}

	Command* Robot::command() {
		return _command;
	}

	void Robot::new_command() {
		delete _command;
		_command = new Command(i(),0.,0.,0.,0.,0.,0.);
	}
}