#pragma once
#include <iostream>
#include <cstdlib>
#include <QCoreApplication>

#include "Robot.h"
#include "_Skills.h"
#include "CommanderSIM.h"
#include "CommanderTX.h"
#include "UpdaterSIM.h"
#include "UpdaterVision.h"

using namespace Inteligencia;
using namespace Inteligencia::Skills;

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);
	cout << "Modulo Inteligencia" << endl;

	Robot* rob = new Robot(4);
	Commander* com = new CommanderTX();
	Updater* upd = new UpdaterVision();
	com->add(rob);
	upd->add(rob);

	system("pause");
	Skill* mov = new Loops::Circle(rob, -1200, 1500, 600, 16);
	while(true) {
		upd->step();
		mov->step();
		com->step();
		//Sleep(30);
	}

	return app.exec();
}
