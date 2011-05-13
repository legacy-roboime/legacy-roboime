#include "TeamCommand.h"

TeamCommand::TeamCommand(void) {}

TeamCommand::TeamCommand(Command command[5]) {
	for(int i = 0; i < 5; i++) _command[i] = command[i];
}

TeamCommand::TeamCommand(Robot robot[5]) {
	for(int i = 0; i < 5; i++) _command[i] = robot[i]._command;
}

TeamCommand::~TeamCommand(void) {}