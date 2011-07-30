#pragma once
#include <deque>
#include "Commander.h"
#include "UpdaterSIM.h"
#include "UDPClientThread.h"

using namespace std;
namespace Inteligencia {

	class CommanderTX : public Commander {
		friend class UpdaterSIM;
		
	private:
		static UDPClientThread* _udpclient;//Use the same server as UpdaterSIM when possible
		deque<string> _queue;

	public:
		CommanderTX();
		CommanderTX(string address, unsigned short port);//this will change static udpclient
		~CommanderTX();

		//methods:
		void prepare();
		void send();
	};
}