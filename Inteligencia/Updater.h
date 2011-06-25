#pragma once
#include "Robot.h"
#include "Team.h"
#include "Ball.h"
#include "Stage.h"
namespace Inteligencia {

	public class Updater {

	private:
		int type;
		Robot* robot;
		Ball* ball;
		Team* team;
		Stage* stage;

	};

}