#pragma once
#include <string>
#include "Command.h"
#include "UDPClient.h"
#include "Robot.h"
#include "Team.h"
using namespace std;
namespace Inteligencia {
	namespace Talk {

		enum ServerType {TX, SIM, SIMSSL, REFBOX, SSL};//Type of the Server with which the Client will connect

		class Client {

		private:
			//fields:
			ServerType _type;
			UDPClient* _udpclient;
			string _last_string;

			//methods:
			void _clear();
			void _init();
			//seters:
			void last_string(string);

		public:
			Client();
			Client(ServerType);
			~Client();

			//methods:
			//setters:
			void type(ServerType);
			//getters:
			ServerType type();
			//useful:
			void send_string(string);
			string last_string();
			void send();

		};

		//string to_sim(Command command);//translates a command to the simulator syntax

		//void send(int index, Command command);//sends command to single robot
		//void send(int team, TeamCommand teamcommand);//sends command to a team, 0 is ours, 1 is theirs

	}
}