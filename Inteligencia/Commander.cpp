#include "Commander.h"

using namespace std;

namespace Inteligencia {

	Commander::Commander() {
		__log = false;
		//TODO: implement?
	}

	Commander::~Commander() {
		//TODO: implement
	}

	//methods:
	void Commander::add(Robot* r) {
		_robot.push_back(r);
	}

	void Commander::del(Robot* r) {
		//TODO: implement
	}

	void Commander::prepare() {}

	void Commander::send() {}

	void Commander::step() {
		prepare();
		send();
	}

}