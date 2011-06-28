#pragma once
#include <deque>
#include "Commander.h"
#include "UDPClient.h"

using namespace std;
namespace Inteligencia {

	class CommanderSIM : public Commander {
		
	private:
		UDPClient* _udpclient;
		deque<string> _queue;

	public:
		CommanderSIM();
		CommanderSIM(string address);
		CommanderSIM(string address, unsigned short port);
		CommanderSIM(unsigned short port);
		CommanderSIM(UDPClient* udpclient);
		~CommanderSIM();

		//methods:
		void prepare();
		void send();
	};
}