#pragma once
#include "TeamCommand.h"
#include "UDPClientThread.h"
#include "UDPClientIntSim.h"
#include <string>
#include <sstream>

using namespace std;

namespace Inteligencia {
	namespace Talk {

		string to_sim(Command command);//translates a command to the simulator syntax

		void send(int index, Command command);//sends command to single robot
		void send(int team, TeamCommand teamcommand);//sends command to a team, 0 is ours, 1 is theirs

	}
}