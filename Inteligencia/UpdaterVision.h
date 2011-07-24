#pragma once
#include <deque>
#include "Updater.h"
#include "UDPMulticastReceiverThread.h"

using namespace std;
namespace Inteligencia {

	class UpdaterVision : public Updater {
	private:
		static UDPMulticastReceiver* _udpMulticastReceiver;
		static UDPMulticastReceiverThread* _udpMulticastReceiverThread;
		deque<string> _queue;

	public:
		UpdaterVision();
		UpdaterVision(string address, unsigned short port);
		~UpdaterVision();

		//methods:
		void start();
		void stop();
		void prepare();

	};
}