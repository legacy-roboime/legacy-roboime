#pragma once
#include "Controller.h"
#include "Math.h"
#include "_Skills.h"
namespace Inteligencia {
	Controller::Controller(int id, Robot* r, double speed) : Tactic(){
			controller = new CXBOXController(id);
			move = new Skills::Move(r, 0, 0, 0);
		}
		Controller::~Controller() {
			delete controller;
			delete move;
		}

		void Controller::robot(Robot* r) {
			move->robot(r);
		}

		int Controller::step() {
			if(controller->IsConnected()){
				double x = (double) controller->GetState().Gamepad.sThumbLX;
				double y = (double) controller->GetState().Gamepad.sThumbLY;
				double v = sqrt(x*x + y*y);
				move->set(x*v_max/v, y*v_max/v, 0.0);
				return EXIT_SUCCESS;
			}
			else return EXIT_FAILURE;
		}

	}
