#include "UpdaterReferee.h"
#include "Update.h"
#include "UpdateReferee.h"

using namespace std;

namespace Inteligencia {

	UpdaterReferee::UpdaterReferee() : Updater() {
		_port=10001;
		_net_address="224.5.23.1";
		_net_interface="";
		in_buffer=new char[MaxDataGramSize];
		_stop = false;
	}

	UpdaterReferee::UpdaterReferee(string address, unsigned short port) : Updater() {
		_port=port;
		_net_address=address;
		_net_interface="";
		in_buffer=new char[MaxDataGramSize];
		_stop = false;
	}

	UpdaterReferee::~UpdaterReferee() {
		delete[] in_buffer;
	}

	void UpdaterReferee::close() {
		mc.close();
	}

	bool UpdaterReferee::open(bool blocking) {
		close();
		if(!mc.open(_port,true,true,blocking)) {
			fprintf(stderr,"Unable to open UDP network port: %d\n",_port);
			fflush(stderr);
			return(false);
		}

		Net::Address multiaddr,interface_;
		multiaddr.setHost(_net_address.c_str(),_port);
		if(_net_interface.length() > 0){
			interface_.setHost(_net_interface.c_str(),_port);
		}else{
			interface_.setAny();
		}

		if(!mc.addMulticast(multiaddr,interface_)) {
			fprintf(stderr,"Unable to setup UDP multicast\n");
			fflush(stderr);
			return(false);
		}

		return(true);
	}

	bool UpdaterReferee::receive2() {
		Net::Address src;
		int r=0;
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
			if(receive2()) {
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
		if(!isRunning()) {
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

	//void UpdaterReferee::stop() {
	//}
}