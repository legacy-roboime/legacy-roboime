#include "CommanderTX.h"
#include "Command.h"

using namespace std;
namespace Inteligencia {

	UDPClientThread* CommanderTX::_udpclient = 0;

	CommanderTX::CommanderTX() : Commander() {
		if(_udpclient==0) {
			_udpclient = new UDPClientThread("_udpclient", 9050, "127.0.0.1");
			_udpclient->start();
		}
	}

	CommanderTX::CommanderTX(string address, unsigned short port) : Commander() {
		delete _udpclient;
		_udpclient = new UDPClientThread("_udpclient", port, address);
	}

	CommanderTX::~CommanderTX() {}

	void CommanderTX::prepare() {
		for(size_t n=_robot.size(); n>0; n--) {
			stringstream out;
			Robot* r = _robot[n-1];
			Command* c = r->command();
			r->new_command();
			//TODO: implement logging
			double* w = c->wheel_speed();
			double  k = c->kick_speed();
			double  d = c->dribble_speed();
			int     i = r->i();
			out <<i<<" "<<w[0]<<" "<<w[1]<<" "<<w[2]<<" "<<w[3]<<" "<<d<<" "<<k<<endl;
			_queue.push_back(out.str());
			out.clear();
		}
	}

	void CommanderTX::send() {
		while(!_queue.empty()) {
			_udpclient->setSendString(_queue.front());
			_udpclient->run();
			_queue.pop_front();
		}
		_udpclient->setSendString("5 0\n");
		_udpclient->run();
	}

}