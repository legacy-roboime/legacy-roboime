#pragma once
#include <deque>
#include "Updater.h"
#include "UDPMulticastReceiverThread.h"

using namespace std;
namespace Inteligencia {

	class UpdaterReferee : public Updater {
	private:
		static UDPMulticastReceiver* _udpMulticastReceiver;
		static UDPMulticastReceiverThread* _udpMulticastReceiverThread;
		deque<string> _queue;

	public:
		UpdaterReferee();
		UpdaterReferee(string address, unsigned short port);
		~UpdaterReferee();

		//methods:
		void start();
		void stop();
		void prepare();

	};
}