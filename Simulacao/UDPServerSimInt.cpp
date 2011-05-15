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
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;
		out << "0 "; //identificador de resposta do pacote 0

		//Parametros de Simulacao
		out << Simulation::timeStep;
		out << " ";
		//Campo
		out << Simulation::getFieldExtents(indexScene).x;
		out << " ";
		out << Simulation::getFieldExtents(indexScene).y;

		out << "\n";

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("1") == 0) //pacote 1 GET DYNAMIC VALUES
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		out << "1 "; //identificador de resposta do pacote 1

		//Ball
		NxVec3 ballPos = Simulation::getBallGlobalPos(indexScene);
		out << ballPos.x;
		out << " ";
		out << ballPos.y;
		//Robot
		for(int indexRobot=1; indexRobot<=10; indexRobot++)
		{
			NxVec3 robotPos = Simulation::getRobotGlobalPos(indexRobot, indexScene);
			NxReal robotAngle = Simulation::getAngle2DFromRobot(indexRobot, indexScene);
			out << robotPos.x;
			out << " ";
			out << robotPos.y;
			out << " ";
			out << robotAngle;
		}

		out << "\n";

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("2") == 0) //pacote 2 SET STATIC VALUES
	{

	}
	else if(temp.compare("3") == 0) //pacote 3 SET DYNAMIC VALUES
	{

	}
	else if(temp.compare("4") == 0) //pacote 4 CONTROL
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		out << "4 "; //identificador de resposta do pacote 4

		//Lendo argumentos do robo e controlando
		for(int indexRobot=1; indexRobot<=10; indexRobot++)
		{
			NxReal* robotWheelSpeed = new NxReal[4];
			for(int indexWheel=0; indexWheel<4; indexWheel++)
			{
				os >> temp;
				robotWheelSpeed[indexWheel] = atof(temp.c_str());
			}

			os >> temp;
			float robotdribblerSpeed = atof(temp.c_str());

			Simulation::controlRobot(robotWheelSpeed, robotdribblerSpeed, indexScene, indexRobot);
		}

		out << "ACK 4\n"; // confirmando pacote 4

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("5") == 0) //pacote 5 SIMULATE
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		out << "5 "; //identificador de resposta do pacote 5

		Simulation::simulate(indexScene);
		//Simulation::RenderCallback();
		//Simulation::flagRender = true;
		//while(Simulation::flagRender){};
		//Simulation::IdleCallback();

		out << "ACK 5\n"; // confirmando pacote 5

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("6") == 0) //pacote 6 GO TO THIS POSE
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		out << "6 "; //identificador de resposta do pacote 6

		//Lendo argumentos e executando goToThisPose
		for(int indexRobot=1; indexRobot<=10; indexRobot++)
		{
			os >> temp;
			float x = atof(temp.c_str());
			os >> temp;
			float y = atof(temp.c_str());
			os >> temp;
			float angle = atof(temp.c_str());
			Simulation::goToThisPose(x, y, angle, indexRobot, indexScene);
		}

		out << "ACK 6\n"; // confirmando pacote 6

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("7") == 0) //pacote 7 INFINITE PATH
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		out << "7 "; //identificador de resposta do pacote 7

		//Lendo argumentos e executando InfinePath
		for(int indexRobot=1; indexRobot<=10; indexRobot++)
		{
			Simulation::infinitePath(indexRobot);
		}

		out << "ACK 7\n"; // confirmando pacote 7

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("8") == 0) //pacote 8 RENDER
	{
		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		out << "8 "; //identificador de resposta do pacote 8

		//Simulation::RenderCallback();
		//glutSwapBuffers();
		//Simulation::RenderCallback();
		//Simulation::ReshapeCallback();
		Simulation::IdleCallback();

		out << "ACK 8\n"; // confirmando pacote 8

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else
	{
		this->sendString = "NACK";
	}
}
