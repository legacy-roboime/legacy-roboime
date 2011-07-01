#include "CommanderSIM.h"
#include "Command.h"

using namespace std;
namespace Inteligencia {

	UDPClient* CommanderSIM::_udpclient = 0;

	CommanderSIM::CommanderSIM() : Commander() {
		if(_udpclient==0) {
			if(UpdaterSIM::_udpclient!=0) {
				_udpclient = UpdaterSIM::_udpclient;
			} else {
				_udpclient = new UDPClient("127.0.0.1", 9876);
			}
		}
	}

	CommanderSIM::CommanderSIM(string address, unsigned short port) : Commander() {
		delete _udpclient;
		_udpclient = new UDPClient(address, port);
	}

	CommanderSIM::~CommanderSIM() {}

	void CommanderSIM::prepare() {
		for(int n=_robot.size()-1; n>=0; n--) {
			stringstream out;
			Robot* r = _robot[n];
			Command* c = r->command();
			r->new_command();
			//TODO: implement logging
			double* w = c->wheel_speed();
			double  k = c->kick_speed();
			double  d = c->dribble_speed();
			int     i = r->i();
			out <<"13 0 "<<i<<" "<<w[0]<<" "<<w[1]<<" "<<w[2]<<" "<<w[3]<<" "<<d<<" "<<k<<endl;
			_queue.push_back(out.str());
			out.clear();
		}
	}

	void CommanderSIM::send() {
		while(!_queue.empty()) {
			_udpclient->setSendString(_queue.front());
			_udpclient->service();
			_queue.pop_front();
		}
		_udpclient->setSendString("5 0\n");
		_udpclient->service();
	}

}