#include "Command.h"

namespace Inteligencia {

	Command::Command(Command* command) {
		reset();
		id(command->id());
		wheel_speed(command->wheel_speed());
		kick_speed(command->kick_speed());
		dribble_speed(command->dribble_speed());
		force_kick(command->force_kick());
		force_dribble(command->force_dribble());
		timestamp(command->timestamp());
	}

	Command::Command(int ii, real speed[4], real d, real k) {
		reset();
		id(ii);
		wheel_speed(speed);
		dribble_speed(d);
		kick_speed(k);
	}

	Command::Command(int ii, real w0, real w1, real w2, real w3, real d, real k) {
		reset();
		id(ii);
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
		_id = -1;
		_old = false;
		_force_kick = false;
		_force_dribble = false;
	}

	void Command::_init() {
		//TODO: is this really necessary?
	}
	
	//methods:
	//setters:
	void Command::id(int i) {
		_id = i;
	}

	void Command::kick_speed(real speed) {
		_kick_speed = speed;
	}

	void Command::dribble_speed(real speed) {
		_dribble_speed = speed;
	}

	void Command::wheel_speed(real speed[4]) {
		for(int i=0; i<4; i++) _wheel_speed[i] = speed[i];
	}

	void Command::force_kick(bool b) {
		_force_kick = b;
	}

	void Command::force_dribble(bool b) {
		_force_dribble = b;
	}

	void Command::timestamp_now() {
		//TODO: implement timestamping here
	}

	void Command::timestamp(double t) {
		_timestamp = t;
	}

	//getters:
	int Command::id() {
		return _id;
	}
	real Command::kick_speed() {
		return _kick_speed;
	}

	real Command::dribble_speed() {
		return _dribble_speed;
	}

	real* Command::wheel_speed() {
		//real* speed = {_wheel_speed[0], _wheel_speed[1], _wheel_speed[2], _wheel_speed[3]};
		return _wheel_speed;
	}

	bool Command::force_kick() {
		return _force_kick;
	}

	bool Command::force_dribble() {
		return _force_dribble;
	}

	double Command::timestamp() {
		return _timestamp;
	}

	//useful shorthands:
	void Command::wheels(real w0, real w1, real w2, real w3) {
		real speed[] = {w0, w1, w2, w3};
		wheel_speed(speed);
	}

	void Command::wheels(real* speed) {
		wheel_speed(speed);
	}

	void Command::kick(real speed) {
		kick_speed(speed);
		//if(speed==0) force_kick = false;
	}

	void Command::force_kick(real speed) {
		kick_speed(speed);
		force_kick(true);
	}

	void Command::dribble(real speed) {
		dribble_speed(speed);
		//if(speed==0) force_dribble = false;
	}
	
	void Command::force_dribble(real speed) {
		dribble_speed(speed);
		force_dribble(true);
	}

}