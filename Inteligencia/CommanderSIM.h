#pragma once
#include <deque>
#include "Commander.h"
#include "UpdaterSIM.h"
#include "UDPClientThread.h"

using namespace std;
namespace Inteligencia {

	class CommanderSIM : public Commander {
		friend class UpdaterSIM;
		
	private:
		static UDPClientThread* _udpclient;//Use the same server as UpdaterSIM when possible
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