#pragma once
#include <deque>
#include "Commander.h"
#include "UpdaterSIM.h"
#include "UDPClient.h"

using namespace std;
namespace Inteligencia {

	class CommanderSIM : public Commander {
		friend class UpdaterSIM;
		
	private:
		static UDPClient* _udpclient;//Use the same server as UpdaterSIM when possible
		deque<string> _queue;

	public:
		CommanderSIM();
		CommanderSIM(string address, unsigned short port);//this will change static udpclient
		~CommanderSIM();

		//methods:
		void prepare();
		void send();
	};
}