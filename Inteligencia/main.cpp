#pragma once
#include <iostream>
#include <cstdlib>
#include "Robot.h"
#include "_Skills.h"
#include "CommanderSIM.h"
#include "UpdaterSIM.h"

using namespace Inteligencia;
using namespace Inteligencia::Skills;

int main(int argc, char *argv[])
{
	cout << "Modulo Inteligencia" << endl;

	Robot* rob = new Robot(4);
	Commander* com = new CommanderSIM();
	Updater* upd = new UpdaterSIM();
	com->add(rob);
	upd->add(rob);


	system("pause");

	Skill* mov = new Loops::Circle(rob, 1500, 1500, 600, 10);
	while(true) {
		upd->step();
		mov->step();
		com->step();
	}

	system("pause");

	return 0;
}
