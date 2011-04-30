#include "Simulation.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char **argv)
{
	printf("Modulo Inteligencia");	
	Simulation* simulation = new Simulation();
	simulation->function(1,argv);//(argc, argv);//(0,NULL);//(argc, argv);
	return 0;
}