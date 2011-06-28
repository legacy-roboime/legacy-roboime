#include "Commander.h"

using namespace std;
namespace Inteligencia {

	Commander::Commander() {
		__log = true;
		//TODO: implement?
	}

	Commander::~Commander() {
		//TODO: implement
	}

	//methods:
	void Commander::add(Command* c) {
		_command.push_back(c);
	}

	void Commander::del(Command* c) {
		//TODO: implement
	}

	void Commander::step() {
		prepare();
		send();
	}

}