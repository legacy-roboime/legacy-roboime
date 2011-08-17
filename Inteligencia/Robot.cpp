#include "Robot.h"
#include <sstream>

namespace Inteligencia {

	void Robot::_init(void) {
		id(-1);
		cc(-1);
		x(0.0);
		y(0.0);
		speedx(0.0);
		speedy(0.0);
		angle(0.0);
		_command = new Command(_id);
		_dribbler = new Dribbler();
		_kicker = new Kicker();
		_motor = new Motor();
		_body = new Body(150.0, 90.0);
		_wheel[0] = new Wheel(-1.02260);
		_wheel[1] = new Wheel( 0.96706);
		_wheel[2] = new Wheel( 2.32842);
		_wheel[3] = new Wheel(-2.38397);
	}

	Robot::Robot(void) {
		_init();
	}

	Robot::Robot(int id_, int cc_) {
		_init();
		id(id_);
		cc(cc_);
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
	void Robot::id(int i) {
		_id = i;
	}

	void Robot::cc(int i) {
		_cc = i;
	}

	void Robot::x(real d) {
		_x = d;
	}

	void Robot::y(real d) {
		_y = d;
	}

	void Robot::angle(real d) {
		_angle = d;
	}

	void Robot::speedx(real d) {
		_speedx = d;
	}

	void Robot::speedy(real d) {
		_speedy = d;
	}

	void Robot::place(real _x, real _y) {
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
		QMutexLocker locker(&_mutex);
		_command->kick(_kicker->speed());
	}

	void Robot::kick(real speed) {
		QMutexLocker locker(&_mutex);
		_command->kick(speed);
	}

	void Robot::dribble() {
		QMutexLocker locker(&_mutex);
		_command->dribble(_dribbler->speed());
	}

	void Robot::dribble(real speed) {
		QMutexLocker locker(&_mutex);
		_command->dribble(speed);
	}

	int Robot::id() {
		return _id;
	}

	int Robot::cc() {
		return _cc;
	}

	real Robot::x() {
		return _x;
	}

	real Robot::y() {
		return _y;
	}

	real Robot::angle() {
		return _angle;
	}

	real Robot::speedx() {
		return _speedx;
	}

	real Robot::speedy() {
		return _speedy;
	}

	//real* Robot::place() {
	//	real p[] = {_x, _y};
	//	return p;
	//}

	void Robot::command(Command* c) {
		QMutexLocker locker(&_mutex);
		_command = c;
		c->id(id());
	}

	void Robot::command(real* s) {
		QMutexLocker locker(&_mutex);
		_command->wheels(s);
	}

	void Robot::command(real w0, real w1, real w2, real w3) {
		QMutexLocker locker(&_mutex);
		_command->wheels(w0, w1, w2, w3);
	}
	
	//void Robot::commander(Commander* c) {
	//	c->add(this);
	//}

	//void Robot::updater(Updater* u) {
	//	_updater = u;
	//}

	Command* Robot::command() {
		QMutexLocker locker(&_mutex);
		return _command;
	}

	void Robot::new_command() {
		QMutexLocker locker(&_mutex);
		delete _command;
		_command = new Command(id(),0.,0.,0.,0.,0.,0.);
	}
}