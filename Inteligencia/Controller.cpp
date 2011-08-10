#include "Controller.h"
#include <cmath>

using namespace Inteligencia::Skills;

namespace Inteligencia {
	namespace Tactics {
		Controller::Controller(int id, Robot* r, Stage* s, double speed) : Tactic(r,s){
			_controller = new CXBOXController(id);
			_stir = new Stir(r);
			robot(r);
			_id = id;
			_sx = 0.0;
			_sy = 0.0;
			_dx = 0.0;
			_dy = 0.0;
			_bspeed = 1.0;
			_bang = 1.0;
			//_dribble = new Skills::Dribble(r);
			_speed = speed;
		}
		Controller::~Controller() {
			delete _controller;
			delete _stir;
		}

		void Controller::robot(Robot* r) {
			_robot = r;
			_stir->robot(r);
		}

		void Controller::step() {
			if(_controller->IsConnected()){
				//right thumb:
				_sx = _controller->ThumbLX();
				_sy = _controller->ThumbLY();
				//left thumb:
				double t_dx = _controller->ThumbRX();
				double t_dy = _controller->ThumbRY();
				//left thumb considerable?
				if(sqrt(t_dx * t_dx + t_dy * t_dy) > .3) {
					_dx = t_dx; _dy = t_dy;
				}
				if(_controller->ButtonPressed(XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
					_robot->kick(_controller->TriggerR());
				}
				if(_controller->ButtonPressed(XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
					_robot->dribble(_controller->TriggerL());
				}
				if(_controller->ButtonPressed(XINPUT_GAMEPAD_LEFT_THUMB)) {
					_bang = 2.0;
				} else {
					_bang = 1.0;
				}
				if(_controller->ButtonPressed(XINPUT_GAMEPAD_RIGHT_THUMB)) {
					_bspeed = 2.0;
				} else {
					_bspeed = 1.0;
				}
				_stir->rate(0.06 * _bang);
				_stir->set(_sx * _bspeed * _speed, _sy * _bspeed * _speed, _dx, _dy);
				_stir->step();
			}
		}
	}
}
