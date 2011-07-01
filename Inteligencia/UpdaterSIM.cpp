#include "UpdaterSIM.h"
#include "Update.h"

using namespace std;
namespace Inteligencia {

	UDPClient* UpdaterSIM::_udpclient = 0;

	UpdaterSIM::UpdaterSIM() : Updater() {
		if(_udpclient==0) {
			if(CommanderSIM::_udpclient!=0) {
				_udpclient = CommanderSIM::_udpclient;
			} else {
				_udpclient = new UDPClient("127.0.0.1", 9876);
			}
		}
	}

	UpdaterSIM::UpdaterSIM(string address, unsigned short port) : Updater() {
		delete _udpclient;
		_udpclient = new UDPClient(address, port);
	}

	UpdaterSIM::~UpdaterSIM() {}

	void UpdaterSIM::receive() {
		_udpclient->setSendString("1 0\n");
		_udpclient->service();
		_queue.push_back(_udpclient->getLastReceivedString());
	}

	void UpdaterSIM::prepare() {
		while(!_queue.empty()){
			stringstream in = stringstream(_queue.front());
			//TODO: parsing
			_queue.pop_front();
		}
	}
}