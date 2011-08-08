#include "Controller.h"

namespace Inteligencia {
	namespace Tactics {
		Controller::Controller(int id, Robot* r, Stage* s, double speed) : Tactic(r,s){
			_controller = new CXBOXController(id);
			_move = new Skills::Move(r, 0.0, 0.0, 0.0);
			_speed = speed;
		}
		Controller::~Controller() {
			delete _controller;
			delete _move;
		}

		void Controller::robot(Robot* r) {
			_move->robot(r);
		}

		void Controller::step() {
			if(_controller->IsConnected()){
				double x = ((double)_controller->GetState().Gamepad.sThumbLX)/32768.0;
				double y = ((double)_controller->GetState().Gamepad.sThumbLY)/32768.0;
				//cout << "x: " << x << endl;
				//cout << "y: " << y << endl;
				//double v = sqrt(x*x + y*y);
				_move->set(x*_speed, y*_speed, 0.0);
				_move->step();
			}
		}
	}
}
