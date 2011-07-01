#pragma once
#include <iostream>
#include <cstdlib>
#include "Robot.h"
#include "_Skills.h"
#include "CommanderSIM.h"
#include "UpdaterSIM.h"

using namespace Inteligencia;

int main(int argc, char *argv[])
{
	cout << "Modulo Inteligencia" << endl;

	Robot* rob = new Robot(4);
	Commander* com = new CommanderSIM();
	Updater* upd = new UpdaterSIM();
	com->add(rob);
	upd->add(rob);


	system("pause");

	while(true) {
		upd->step();
		Skills::move(rob, 3.5, 3.5, 0);
		com->step();
	}

	system("pause");

	return 0;
}
