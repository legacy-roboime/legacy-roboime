#include "UpdaterReferee.h"
#include "Update.h"
#include "UpdateBall.h"
#include "UpdateRobot.h"

using namespace std;
namespace Inteligencia {

	UDPMulticastReceiver* UpdaterReferee::_udpMulticastReceiver = 0;
	UDPMulticastReceiverThread* UpdaterReferee::_udpMulticastReceiverThread = 0;

	UpdaterReferee::UpdaterReferee() : Updater() {
		if(_udpMulticastReceiver==0) {
			_udpMulticastReceiver = new UDPMulticastReceiver();
		}
		if(_udpMulticastReceiverThread==0) {
			_udpMulticastReceiverThread = new UDPMulticastReceiverThread(_udpMulticastReceiver);
		}
	}

	UpdaterReferee::UpdaterReferee(string address, unsigned short port) : Updater() {
		_udpMulticastReceiver = new UDPMulticastReceiver(address, port);
		_udpMulticastReceiverThread = new UDPMulticastReceiverThread(_udpMulticastReceiver);
	}

	UpdaterReferee::~UpdaterReferee() {
		delete _udpMulticastReceiver;
		delete _udpMulticastReceiverThread;
	}

	void UpdaterReferee::start() {
		_udpMulticastReceiverThread->start();
		//_queue.push_back(_udpclient->getLastReceivedString());
	}
	
	void UpdaterReferee::stop() {
		_udpMulticastReceiverThread->stop();
	}

	void UpdaterReferee::prepare() {
		while(!_queue.empty()){
			stringstream in = stringstream(_queue.front());
			//TODO: validation
			double x, y, a;
			in >> x;
			in >> y;
			_update.push_back(new UpdateBall(x,y));
			for(int k=1; k<=10; k++) {
				in >> x;
				in >> y;
				in >> a;
				_update.push_back(new UpdateRobot(k,x,y,a));
			}
			_queue.pop_front();
		}
	}
}