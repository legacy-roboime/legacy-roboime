#include "Command.h"
namespace Inteligencia {

	//Command::Command(Command command) {
	//	reset();
	//	set_wheel_speed(command.wheels[i]);
	//	force_kick = command.force_kick;
	//	force_dribble = command.force_dribble;
	//}

	Command::Command(double speed[4]) {
		reset();
		wheel_speed(speed);
	}

	Command::Command(double w0, double w1, double w2, double w3) {
		reset();
		_wheel_speed[0] = w0;
		_wheel_speed[2] = w1;
		_wheel_speed[2] = w2;
		_wheel_speed[3] = w3;
	}

	Command::Command() {
		reset();
	}

	Command::~Command() {}

	void Command::reset() {
		//FIXME: what's wrong?
		//_wheel_speed = {.0, .0, .0, .0};
		for(int i=0; i<4; i++) _wheel_speed[i] = 0.;
		_old = false;
		_force_kick = false;
		_force_dribble = false;
	}
	
	//methods:
	//setters:
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
	double Command::kick_speed() {
		return _kick_speed;
	}

	double Command::dribble_speed() {
		return _dribble_speed;
	}

	double* Command::wheel_speed() {
		double speed[4] = {_wheel_speed[0], _wheel_speed[1], _wheel_speed[2], _wheel_speed[3]};
		return speed;
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