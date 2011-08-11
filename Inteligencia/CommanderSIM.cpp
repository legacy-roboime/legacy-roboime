#include "CommanderSIM.h"
#include "Command.h"

using namespace std;

namespace Inteligencia {

	UDPClientThread* CommanderSIM::_udpclient = 0;

	CommanderSIM::CommanderSIM() : Commander() {
		if(_udpclient==0) {
			if(UpdaterSIM::_udpclient!=0) {
				_udpclient = UpdaterSIM::_udpclient;
			} else {
				_udpclient = new UDPClientThread("_udpclient", 9876, "127.0.0.1");
				_udpclient->start();
			}
		}
	}

	CommanderSIM::CommanderSIM(string address, unsigned short port) : Commander() {
		delete _udpclient;
		_udpclient = new UDPClientThread("_udpclient", port, address);
	}

	CommanderSIM::~CommanderSIM() {}

	void CommanderSIM::prepare() {
		for(size_t n=_robot.size(); n>0; n--) {
			stringstream out;
			Robot* r = _robot[n-1];
			Command* c = r->command();
			r->new_command();
			//TODO: implement logging
			real* w = c->wheel_speed();
			real  k = c->kick_speed();
			real  d = c->dribble_speed();
			int   i = r->id();
			out <<"13 0 "<<i<<" "<<w[0]<<" "<<w[1]<<" "<<w[2]<<" "<<w[3]<<" "<<d<<" "<<k<<endl;
			_queue.push_back(out.str());
			out.clear();
		}
	}

	void CommanderSIM::send() {
		while(!_queue.empty()) {
			_udpclient->setSendString(_queue.front());
			_udpclient->run();
			_queue.pop_front();
		}
		_udpclient->setSendString("5 0\n");
		_udpclient->run();
	}

}