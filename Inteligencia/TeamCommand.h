#pragma once
#include "Command.h"
#include "Robot.h"

class TeamCommand {

private:
	//fields:
	Command _command[5];

public:
	TeamCommand(void);
	TeamCommand(Command command[5]);
	TeamCommand(Robot robot[5]);
	~TeamCommand(void);

};