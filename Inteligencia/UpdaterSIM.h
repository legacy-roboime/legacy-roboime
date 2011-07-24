#pragma once
#include <deque>
#include "Updater.h"
#include "CommanderSIM.h"
#include "UDPClientThread.h"

using namespace std;
namespace Inteligencia {

	class UpdaterSIM : public Updater {
		friend class CommanderSIM;

	private:
		static UDPClient* _udpclient;//Use the same server as CommanderSIM when possible
		UDPClientThread* _udpClientThread;
		deque<string> _queue;

	public:
		UpdaterSIM();
		UpdaterSIM(string address, unsigned short port);
		~UpdaterSIM();

		//methods:
		void receive();
		void prepare();

	};
}