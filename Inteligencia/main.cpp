#include "Inteligencia.h"
#include "_Skills.h"
#include "CommanderSIM.h"

using namespace Inteligencia;
using namespace Inteligencia::Skills;

int main(int argc, char *argv[])
{
	cout << "Modulo Inteligencia" << endl;

	Robot* rob = new Robot(4);
	Commander* com = new CommanderSIM();
	com->add(rob);
	

	system("pause");

	while(true) {
		move(rob, 1.5, 1.5, 0);
		//rob->command(30, 30, 20, 20);
		com->step();
	}

	system("pause");

	return 0;
}
