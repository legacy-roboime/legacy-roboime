#include "UpdaterReferee.h"
#include "Update.h"
#include "UpdateBall.h"
#include "UpdateRobot.h"

using namespace std;

namespace Inteligencia {

	UpdaterReferee::UpdaterReferee() : Updater() {
		_stop = false;
	}

	UpdaterReferee::UpdaterReferee(string address, unsigned short port) : Updater() {
	}

	UpdaterReferee::~UpdaterReferee() {
	}

	void UpdaterReferee::start() {
	}
	
	void UpdaterReferee::stop() {
	}

	void UpdaterReferee::prepare() {

	}

	void UpdaterReferee::run() {
		_client.open(true);
		SSL_WrapperPacket packet;
		while(!_stop) {
			if(_client.receive(packet)) {
				QMutexLocker locker(&_mutex);
				_packet.push_back(packet);
			}
		}
	}

	void UpdaterReferee::receive() {
		if(!isRunning()) {
			_stop = false;
			start();
		}
	}
}