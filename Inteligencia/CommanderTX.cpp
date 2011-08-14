#include "CommanderTX.h"
#include "Command.h"
#include <QMutexLocker>
#include <iostream>

using namespace std;

namespace Inteligencia {

	CommanderTX::CommanderTX(string address, int port) : Commander() {
		for(size_t n=0; n<5; n++) _robot.push_back(0);
		_port = port;
		_net_address = address;
		_net_interface = "";
		_stop = false;
		_queue.clear();
		start();
	}

	CommanderTX::~CommanderTX() {}

	void CommanderTX::close() {
		mc.close();
	}

	bool CommanderTX::open() {
		close();

		if(!mc.open(_port,true,true)) {
			cerr << "Unable to open UDP network port: " << _port << endl;
			return false;
		}

		Net::Address multiaddr,interface_;
		multiaddr.setHost(_net_address.c_str(),_port);
		if(_net_interface.length() > 0){
			interface_.setHost(_net_interface.c_str(),_port);
		} else {
			interface_.setAny();
		}

		//if(!mc.addMulticast(multiaddr,interface_)) {
		//	cerr << "Unable to setup UDP multicast" << endl;
		//	return false;
		//}

		return true;
	}

	void CommanderTX::add(Robot* r) {
		int i = r->id();
		if(i<5) {
			if(_robot[i]!=0) delete _robot[i];
			_robot[i] = r;
		} else {
			cerr << "Warning: index greater than 4 not supported" << endl;
		}
	}

	bool CommanderTX::send(string buffer) {
		Net::Address multiaddr;
		multiaddr.setHost(_net_address.c_str(),_port);
		if(mc.send(buffer.c_str(),(int)buffer.length(),multiaddr)) return true;
		else cerr << "UDP Fail sending: " << buffer << endl;
		return false;
	}

	void CommanderTX::send() {
		if(send(_queue.front())) _queue.pop_front();
	}

	void CommanderTX::run() {
		open();
		do {
			prepare();
			send();
		} while(!_queue.empty());
	}

	void CommanderTX::prepare() {
		stringstream out;
		for(size_t n=0; n<5; n++) {
			if(_robot[n]!=0) {
				Robot* r = _robot[n];
				mutex.lock();
				Command* c = new Command(r->command());
				r->new_command();
				mutex.unlock();
				//TODO: implement logging
				real* w = c->wheel_speed();
				real  k = c->kick_speed();
				real  d = c->dribble_speed();
				out << w[0] << " " << w[1] << " " << w[2] << " " 
					<< w[3] << " " << d    << " " << k    << " ";
			} else {
				out << "0 0 0 0 0 0 ";
			}
		}
		out << endl;
		QMutexLocker locker(&mutex);
		_queue.push_back(out.str());
	}

	void CommanderTX::step() {
		if(isFinished()) {
			_stop = false;
			start();
		}
	}

}