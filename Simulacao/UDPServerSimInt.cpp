#include "UDPServerSimInt.h"

UDPServerSimInt::UDPServerSimInt(void) : UDPServer()
{
}

UDPServerSimInt::~UDPServerSimInt(void)
{
}

void UDPServerSimInt::parsing()
{
	string temp; 
	std::stringstream os(this->receiveString);
	os >> temp;
	if(temp.compare("0") == 0) //pacote 0 GET STATIC VALUES (WORLDMODEL TB PASSA ISSO)
	{
		os >> temp;
		int indexScene = atoi(temp.c_str());

		this->sendString = "";
		stringstream out;
		out << Simulation::getFieldExtents(indexScene).x;
		this->sendString.append(out.str());
	}
	else if(temp.compare("1") == 0) //pacote 1 GET DYNAMIC VALUES
	{

	}
	else if(temp.compare("2") == 0) //pacote 2 SET STATIC VALUES
	{

	}
	else if(temp.compare("3") == 0) //pacote 3 SET DYNAMIC VALUES
	{

	}
	else if(temp.compare("4") == 0) //pacote 4 CONTROL
	{

	}
	else if(temp.compare("5") == 0) //pacote 5 SIMULATE
	{

	}
	else if(temp.compare("6") == 0) //pacote 6 GO TO THIS POSE
	{

	}
	else if(temp.compare("7") == 0) //pacote 7 INFINITE PATH
	{

	}
}
