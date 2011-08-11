#include "Controller.h"
#include <iostream>
#include <cmath>

using namespace Inteligencia::Skills;

namespace Inteligencia {
	namespace Tactics {
		Controller::Controller(int id, Robot* r, Stage* s, real speed) : Tactic(r,s){
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
				//rotation
				real t_dx = _controller->ThumbRX();
				real t_dy = _controller->ThumbRY();
				if(sqrt(t_dx * t_dx + t_dy * t_dy) > .3) {
					_dx = t_dx; _dy = t_dy;
				}
				if(_controller->ButtonPressed(XINPUT_GAMEPAD_RIGHT_THUMB)) {
					_bang = 2.0;
				} else {
					_bang = 1.0;
				}
				_stir->rate(0.06 * _bang);
				//movement
				_sx = _controller->ThumbLX();
				_sy = _controller->ThumbLY();
				if(_controller->ButtonPressed(XINPUT_GAMEPAD_LEFT_THUMB)) {
					_bspeed = 2.0;
				} else {
					_bspeed = 1.0;
				}
				_stir->set(_sx * _bspeed * _speed, _sy * _bspeed * _speed, _dx, _dy);
				//dribbler
				if(_controller->ButtonPressed(XINPUT_GAMEPAD_LEFT_SHOULDER)) {
					_dribs = -1;
				} else {
					_dribs = 1;
				}
				_robot->dribble(_dribs * _controller->TriggerL());
				//kicker
				if(_controller->ButtonPressed(XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
					_robot->kick(_controller->TriggerR());
				}
				_stir->step();
			}
		}
	}
}
