#include "UpdaterSIM.h"
#include "Update.h"
#include "UpdateBall.h"
#include "UpdateRobot.h"
#include "UpdaterSIM.h"

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
		_udpClientThread = new UDPClientThread(_udpclient);
	}

	UpdaterSIM::UpdaterSIM(string address, unsigned short port) : Updater() {
		delete _udpclient;
		_udpclient = new UDPClient(address, port);
	}

	UpdaterSIM::~UpdaterSIM() {
		delete _udpclient;
		delete _udpClientThread;
	}

	void UpdaterSIM::receive() {
		_udpclient->setSendString("1 0\n");
		_udpclient->service();
		//_udpClientThread->sttttttttart();
		_queue.push_back(_udpclient->getLastReceivedString());
	}

	void UpdaterSIM::prepare() {
		while(!_queue.empty()){
			stringstream in = stringstream(_queue.front());
			//TODO: validation
			double x, y, a;
			in >> x;
			in >> y;
			_update.push_back(new UpdateBall(1,x,y));
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