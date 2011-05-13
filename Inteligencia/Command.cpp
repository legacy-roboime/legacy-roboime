#include "Command.h"

Command::Command() {}

Command::Command(double orientation, double speed) {
}

Command::Command(double orientation, double speed, bool kick, bool drible) {
}

Command::~Command() {}

void Command::kick() {
	_kick = true;
}

void Command::start_dribbler() {
	_dribble = true;
}

void Command::stop_dribbler() {
	_dribble = false;
}