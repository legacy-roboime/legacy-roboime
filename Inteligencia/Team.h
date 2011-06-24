#pragma once
#include "Robot.h"
namespace Inteligencia {

	class Team {

	private:
		//fields:
		Robot _robot[5];

	public:
		Team(void);
		Team(Robot robot[5]);
		~Team(void);

	};
}