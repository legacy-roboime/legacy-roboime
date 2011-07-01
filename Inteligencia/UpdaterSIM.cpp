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
		//TODO: implement
	}

	void UpdaterSIM::prepare() {
		//TODO: implement
	}
}