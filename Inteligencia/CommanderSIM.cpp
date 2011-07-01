#include "CommanderSIM.h"
#include "Command.h"

using namespace std;
namespace Inteligencia {

	CommanderSIM::CommanderSIM() : Commander() {
		_udpclient = new UDPClient("127.0.0.1", 9876);
	}

	CommanderSIM::CommanderSIM(string address) : Commander() {
		_udpclient = new UDPClient(address, 9876);
	}

	CommanderSIM::CommanderSIM(string address, unsigned short port) : Commander() {
		_udpclient = new UDPClient(address, port);
	}

	CommanderSIM::CommanderSIM(unsigned short port) : Commander() {
		_udpclient = new UDPClient("127.0.0.1", port);
	}

	CommanderSIM::CommanderSIM(UDPClient* udpclient) {
		_udpclient = udpclient;
	}

	CommanderSIM::~CommanderSIM() {
		delete _udpclient;
	}

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