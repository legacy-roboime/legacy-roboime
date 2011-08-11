#include "Updater.h"

using namespace std;

namespace Inteligencia {

	Updater::Updater() {
		__log = true;
	}

	Updater::~Updater() {}

	void Updater::step() {
		receive();
		prepare();
		apply();
	}

	void Updater::apply() {
		while(!_update.empty()) {
			_update.front()->apply(this);
			//TODO: implement logging
			_update.pop_front();
		}
	}

	void Updater::add(Robot* r) {
		_robot.push_back(r);
	}

	void Updater::add(Ball* b) {
		_ball.push_back(b);
	}

	void Updater::del(Robot* r) {
		//TODO: implement
	}

	void Updater::del(Ball* b) {
		//TODO: implement
	}

	size_t Updater::robots() {
		return _robot.size();
	}

	Robot* Updater::robot(size_t i) {
		return _robot[i];
	}

	size_t Updater::balls() {
		return _ball.size();
	}

	Ball* Updater::ball(size_t i) {
		return _ball[i];
	}

	void Updater::prepare() {}

}