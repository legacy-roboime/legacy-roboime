#include "Controller.h"
#include <cmath>

namespace Inteligencia {
	namespace Tactics {
		Controller::Controller(int id, Robot* r, Stage* s, double speed) : Tactic(r,s){
			_id = id;
			_x = 0;
			_y = 0;
			_controller = new CXBOXController(id);
			 //_kick = new Skills::Kick(r);
			//_dribble = new Skills::Dribble(r);
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

		double Controller::set_x() {
			_x = ((double)_controller->GetState().Gamepad.sThumbLX)/32768.0;
			return _x;
		}
		double Controller::set_y() {
			_y = ((double)_controller->GetState().Gamepad.sThumbLY)/32768.0;
			return _y;
		}
		double Controller::set_ang() {
			double x = ((double)_controller->GetState().Gamepad.sThumbRX)/32768.0;
			double y = ((double)_controller->GetState().Gamepad.sThumbRY)/32768.0;
			_ang = atan2(y, x);
			return _ang;
		}
		bool Controller::should_kick() {
			if(_controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				return true;
			}
			else return false;
		}

		void Controller::trigger_kick()
		{
			double strength = _controller->GetState().Gamepad.bRightTrigger/255;
			//TODO: Botar o kick aqui				
		}

		bool Controller::should_dribble(){
			if(_controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				return true;
			}
			else return false;
		}
		void Controller::trigger_dribble(){
			double strength = _controller->GetState().Gamepad.bLeftTrigger/255;
			//TODO: Botar o drible aqui
		}
		void Controller::step() {
			if(_controller->IsConnected()){
				set_x();	
				set_y();
				_move->set(_x*_speed, _y*_speed, 0.0);
				if(should_kick()){
				}
				if(should_dribble()){
				}
				_move->step();
			}
		}
	}
}
