#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "Talk.h"
#include "Robot.h"
using namespace Inteligencia;
using namespace Inteligencia::Talk;

int main(int argc, char **argv)
{
	cout << "Modulo Inteligencia" << endl;

	Client* client = new Client(TX);

	Robot* rob = new Robot(2);

	system("pause");
	client->send_string("0 0\n");
	client->send();
	cout << client->last_string() << endl;

	client->send_string("1 0\n");
	client->send();
	cout << client->last_string() << endl;

	system("pause");

	return 0;
}
