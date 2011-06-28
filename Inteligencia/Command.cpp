#include "Command.h"
namespace Inteligencia {

	Command::Command(Command* command) {
		reset();
		i(command->i());
		wheel_speed(command->wheel_speed());
		force_kick(command->force_kick());
		force_dribble(command->force_dribble());
	}

	Command::Command(int ii, double speed[4]) {
		reset();
		i(ii);
		wheel_speed(speed);
	}

	Command::Command(int ii, double speed[4], double d, double k) {
		reset();
		i(ii);
		wheel_speed(speed);
		dribble_speed(d);
		kick_speed(k);
	}

	Command::Command(int ii, double w0, double w1, double w2, double w3) {
		reset();
		i(ii);
		wheels(w0, w1, w2, w3);
	}

	Command::Command(int ii, double w0, double w1, double w2, double w3, double d, double k) {
		reset();
		i(ii);
		wheels(w0, w1, w2, w3);
		dribble_speed(d);
		kick_speed(k);
	}

	Command::Command() {
		reset();
	}

	Command::~Command() {}

	void Command::reset() {
		for(int i=0; i<4; i++) _wheel_speed[i] = 0.;
		_kick_speed = 0.;
		_dribble_speed = 0.;
		_i = -1;
		_old = false;
		_force_kick = false;
		_force_dribble = false;
	}

	void Command::_init() {
		//TODO: is this really necessary?
	}
	
	//methods:
	//setters:
	void Command::i(int ii) {
		_i=ii;
	}

	void Command::kick_speed(double speed) {
		_kick_speed = speed;
	}

	void Command::dribble_speed(double speed) {
		_dribble_speed = speed;
	}

	void Command::wheel_speed(double speed[4]) {
		for(int i=0; i<4; i++) _wheel_speed[i] = speed[i];
	}

	void Command::force_kick(bool b) {
		_force_kick = b;
	}

	void Command::force_dribble(bool b) {
		_force_dribble = b;
	}

	//getters:
	int Command::i() {
		return _i;
	}
	double Command::kick_speed() {
		return _kick_speed;
	}

	double Command::dribble_speed() {
		return _dribble_speed;
	}

	double* Command::wheel_speed() {
		//double* speed = {_wheel_speed[0], _wheel_speed[1], _wheel_speed[2], _wheel_speed[3]};
		return _wheel_speed;
	}

	bool Command::force_kick() {
		return _force_kick;
	}

	bool Command::force_dribble() {
		return _force_dribble;
	}

	//useful shorthands:
	void Command::wheels(double w0, double w1, double w2, double w3) {
		double speed[] = {w0, w1, w2, w3};
		wheel_speed(speed);
	}

	void Command::wheels(double speed[4]) {
		wheel_speed(speed);
	}

	void Command::kick(double speed) {
		kick_speed(speed);
		//if(speed==0) force_kick = false;
	}

	void Command::force_kick(double speed) {
		kick_speed(speed);
		force_kick(true);
	}

	void Command::dribble(double speed) {
		dribble_speed(speed);
		//if(speed==0) force_dribble = false;
	}
	
	void Command::force_dribble(double speed) {
		dribble_speed(speed);
		force_dribble(true);
	}

}