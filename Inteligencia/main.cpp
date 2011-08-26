#pragma once
#include <iostream>
#include <cstdlib>
#include <QCoreApplication>

#include "Robot.h"
#include "Stage.h"
#include "_Skills.h"
#include "_Tactics.h"
#include "CommanderSIM.h"
#include "CommanderTX.h"
#include "UpdaterSIM.h"
#include "UpdaterReferee.h"
#include "UpdaterVision.h"

using namespace Inteligencia;
using namespace Inteligencia::Skills;
using namespace Inteligencia::Tactics;

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);
	cout << "Modulo Inteligencia" << endl;

	Stage* sta = new Stage();
	Robot* rob = new Robot(4, 3);
	//Robot* robb = new Robot(3, 2);
	Commander* com = new CommanderTX();
	Updater* upd = new UpdaterVision();
	Updater* updReferee = new UpdaterReferee();
	com->add(rob);
	upd->add(rob);

	//system("pause");
	//Skill* test = new Loops::Circle(rob, -1200, 1500, 600, 16);
	Tactic* test = new Controller(1, rob, sta, 50);
	//Tactic* testb = new Controller(2, robb, sta, 20);
	while(true) {
		upd->step();
		updReferee->step();
		test->step();
		//testb->step();
		com->step();
		Sleep(1000/60);
	}

	return app.exec();
}
