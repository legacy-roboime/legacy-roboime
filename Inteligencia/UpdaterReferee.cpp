#include "UpdaterReferee.h"
#include "Update.h"
#include "UpdateReferee.h"
#include <QMutexLocker>
#include <iostream>

using namespace std;

namespace Inteligencia {

	UpdaterReferee::UpdaterReferee(string address, int port) : Updater() {
		_port = port;
		_net_address = address;
		_net_interface = "";
		in_buffer = new char[MaxDataGramSize];
		_stop = false;
		start();
	}

	UpdaterReferee::~UpdaterReferee() {
		delete[] in_buffer;
	}

	void UpdaterReferee::close() {
		mc.close();
	}

	void UpdaterReferee::stop() {
		QMutexLocker locker(&mutex);
		close();
		_stop = true;
	}

	bool UpdaterReferee::open(bool blocking) {
		close();
		if(!mc.open(_port,true,true,blocking)) {
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

		if(!mc.addMulticast(multiaddr,interface_)) {
			cerr << "Unable to setup UDP multicast" << endl;
			return false;
		}

		return true;
	}

	bool UpdaterReferee::_receive() {
		Net::Address src;
		int r = 0;
		return mc.recv(in_buffer,MaxDataGramSize,src) > 0;
		//TODO: is the code below nescessary?
		r = mc.recv(in_buffer,MaxDataGramSize,src);
		if (r>0) {
			fflush(stdout);
			return true;
		}
		return false;
	}

	void UpdaterReferee::run() {
		open(true);
		while(!_stop) {
			if(_receive()) {
				QMutexLocker locker(&mutex);
				unsigned char cmd_counter = (unsigned char)in_buffer[1];
				static unsigned char cmd_counter_tmp = -1;
				if ( cmd_counter != cmd_counter_tmp ) 
				{ // se nao houver nenhum comando novo, fazer nada
					cmd_counter_tmp = cmd_counter;
					_queue.push_back(in_buffer);
				}
			}
		}
	}

	void UpdaterReferee::receive() {
		if(isFinished()) {
			_stop = false;
			start();
		}
	}


	void UpdaterReferee::prepare() {
		QMutexLocker locker(&mutex);
		while(!_queue.empty()){
			char* packet = _queue.front();
			char cmd_tmp = (char)packet[0];
			unsigned char cmd_counter = (unsigned char)packet[1];
			unsigned char goals_blue = (unsigned char)packet[2];
			unsigned char goals_yellow = (unsigned char)packet[3];
			int time_remaining = ((int)(packet[4]) << 8)  + (int)(packet[5]); //byte mais significativo
			_update.push_back(new UpdateReferee(cmd_tmp, cmd_counter, goals_blue, goals_yellow, time_remaining));
			_queue.pop_front();
		}
	}
}
