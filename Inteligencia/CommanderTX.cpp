#include "CommanderTX.h"
#include "Command.h"

using namespace std;

namespace Inteligencia {

	UDPClientThread* CommanderTX::_udpclient = 0;

	CommanderTX::CommanderTX() : Commander() {
		for(size_t n=0; n<5; n++) _robot.push_back(0);
		if(_udpclient==0) {
			_udpclient = new UDPClientThread("_udpclient", 9050, "127.0.0.1");
			_udpclient->start();
		}
	}

	CommanderTX::CommanderTX(string address, unsigned short port) : Commander() {
		for(size_t n=0; n<5; n++) _robot.push_back(0);
		delete _udpclient;
		_udpclient = new UDPClientThread("_udpclient", port, address);
	}

	CommanderTX::~CommanderTX() {}

	void CommanderTX::add(Robot* r) {
		int i = r->i();
		if(i<5) {
			if(_robot[i]!=0) delete _robot[i];
			_robot[i] = r;
		} else {
			fprintf(stderr, "Warning: index greater than 4 not supported\n");
		}
	}

	void CommanderTX::prepare() {
		stringstream out;
		for(size_t n=0; n<5; n++) {
			if(_robot[n]!=0) {
				Robot* r = _robot[n];
				Command* c = r->command();
				//TODO: implement logging
				real* w = c->wheel_speed();
				real  k = c->kick_speed();
				real  d = c->dribble_speed();
				out << w[0] << " " << w[1] << " " << w[2] << " " 
					<< w[3] << " " << d    << " " << k    << " ";
				r->new_command();
			} else {
				out << "0 0 0 0 0 0 ";
			}
		}
		out << endl;
		_queue.push_back(out.str());
	}

	void CommanderTX::send() {
		while(!_queue.empty()) {
			_udpclient->setSendString(_queue.front());
			_udpclient->run();
			_queue.pop_front();
		}
	}

}