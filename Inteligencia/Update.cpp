#include "Update.h"
//#include "timer.h"

namespace Inteligencia {

	Update::Update() {}

	Update::Update(float conf, double t_sent, double t_capture) {
		_confidence = conf;
		//_time_received = GetTimeSec();//TODO: fix this
		_time_sent = t_sent;
		_time_capture = t_capture;
	}

	Update::~Update() {
		//_time_received = GetTimeSec();//and this
	}

	double Update::time_received() {
		return _time_received;
	}

	double Update::time_sent() {
		return _time_sent;
	}

	double Update::time_capture() {
		return _time_capture;
	}

}