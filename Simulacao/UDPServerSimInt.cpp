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

		//Parametros de Simulacao
		out << Simulation::timeStep;
		out << " ";
		//out << Simulation::timeStep; //identificador da cena que esta sendo renderizada
		//out << " ";
		//out << Simulation::timeStep; //quantidade de cenas existentes
		//out << " ";
		//Campo
		out << Simulation::getFieldExtents(indexScene).x; //largura
		out << " ";
		out << Simulation::getFieldExtents(indexScene).y; //altura
		out << " ";
		out << Simulation::widthBorderField; //largura do campo interno (delimitado pelas linhas brancas)
		out << " ";
		out << Simulation::heightBorderField; //altura do campo interno (delimitado pelas linhas brancas)
		//Robo
		//out << " ";
		//out << Simulation::getFieldExtents(indexScene).y; //quantidade de robos teammates
		//out << " ";
		//out << Simulation::getFieldExtents(indexScene).y; //quantidade de robos opponents
		//Chutador
		//Driblador
		//Roda
		//Motor
		//Engrenagem
		//Bola

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

		//Bola
		NxVec3 ballPos = Simulation::getBallGlobalPos(indexScene);
		out << ballPos.x;
		out << " ";
		out << ballPos.y;
		//Robo
		for(int indexRobot=1; indexRobot<=10; indexRobot++)
		{
			NxVec3 robotPos = Simulation::getRobotGlobalPos(indexRobot, indexScene);
			NxReal robotAngle = Simulation::getAngle2DFromRobot(indexRobot, indexScene);
			out << " ";
			out << robotPos.x;
			out << " ";
			out << robotPos.y;
			out << " ";
			out << robotAngle;
		}
		//Motor
		//Driblador
		//Chutador


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
	else if(temp.compare("4") == 0) //pacote 4 CONTROL ALL ROBOTS
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		//Lendo argumentos do robo e controlando
		for(int indexRobot=1; indexRobot<=10; indexRobot++)
		{
			os >> temp;
			float speedX = atof(temp.c_str());
			os >> temp;
			float speedY = atof(temp.c_str());
			os >> temp;
			float speedAng = atof(temp.c_str());
			os >> temp;
			float dribblerSpeed = atof(temp.c_str());
			os >> temp;
			float kickerSpeed = atof(temp.c_str());

			Simulation::controlRobot(speedX, speedY, speedAng, dribblerSpeed, kickerSpeed, indexRobot, indexScene);
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

		Simulation::simulate(indexScene);

		//Mutex
		//Simulation::flagRender = true;
		//while(Simulation::flagRender){};

		out << "ACK 5\n"; // confirmando pacote 5

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("6") == 0) //pacote 6 GO TO THIS POSE FOR ALL ROBOTS
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

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

		//Lendo argumentos e executando InfinePath
		for(int indexRobot=1; indexRobot<=10; indexRobot++)
		{
			Simulation::infinitePath(indexRobot);
		}

		out << "ACK 7\n"; // confirmando pacote 7

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("8") == 0) //pacote 8 CONTROL DRIBBLER AND KICKER ALL ROBOTS
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		//Lendo argumentos do robo e controlando
		for(int indexRobot=1; indexRobot<=10; indexRobot++)
		{
			os >> temp;
			float dribblerSpeed = atof(temp.c_str());
			os >> temp;
			float kickerSpeed = atof(temp.c_str());

			Simulation::controlDribbler( dribblerSpeed, indexRobot, indexScene );
			Simulation::executeKicker( kickerSpeed, indexRobot, indexScene );
		}

		out << "ACK 8\n"; // confirmando pacote 8

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("9") == 0) //pacote 9 GO TO THIS POSE ONE ROBOT
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());
		os >> temp;
		int indexRobot = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		//Lendo argumentos e executando goToThisPose
		os >> temp;
		float x = atof(temp.c_str());
		os >> temp;
		float y = atof(temp.c_str());
		os >> temp;
		float angle = atof(temp.c_str());
		Simulation::goToThisPose(x, y, angle, indexRobot, indexScene);

		out << "ACK 9\n"; // confirmando pacote 9

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("10") == 0) //pacote 10 SIMULATE THE INDEXSCENE WITH DT TIME
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());
		os >> temp;
		float dt = atof(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		Simulation::simulate(indexScene, dt);

		//Mutex
		//Simulation::flagRender = true;
		//while(Simulation::flagRender){};

		out << "ACK 10\n"; // confirmando pacote 10

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("11") == 0) //pacote 11 CONTROL ONE ROBOT
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		//Lendo argumentos do robo e controlando
		os >> temp;
		int indexRobot = atoi(temp.c_str());

		os >> temp;
		float speedX = atof(temp.c_str());
		os >> temp;
		float speedY = atof(temp.c_str());
		os >> temp;
		float speedAng = atof(temp.c_str());
		os >> temp;
		float dribblerSpeed = atof(temp.c_str());
		os >> temp;
		float kickerSpeed = atof(temp.c_str());

		Simulation::controlRobot(speedX, speedY, speedAng, dribblerSpeed, kickerSpeed, indexRobot, indexScene);

		out << "ACK 11\n"; // confirmando pacote 11

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("12") == 0) //pacote 12 CONTROL DRIBBLER AND KICKER ONE ROBOT
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		//Lendo argumentos do robo e controlando
		os >> temp;
		int indexRobot = atoi(temp.c_str());
		os >> temp;
		float dribblerSpeed = atof(temp.c_str());
		os >> temp;
		float kickerSpeed = atof(temp.c_str());

		Simulation::controlDribbler( dribblerSpeed, indexRobot, indexScene );
		Simulation::executeKicker( kickerSpeed, indexRobot, indexScene );

		out << "ACK 12\n"; // confirmando pacote 12

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("13") == 0) //pacote 13 CONTROL ONE ROBOT (CONTROL WHEELS)
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		//Lendo argumentos do robo e controlando
		os >> temp;
		int indexRobot = atoi(temp.c_str());

		os >> temp;
		float speedWheel1 = atof(temp.c_str());
		os >> temp;
		float speedWheel2 = atof(temp.c_str());
		os >> temp;
		float speedWheel3 = atof(temp.c_str());
		os >> temp;
		float speedWheel4 = atof(temp.c_str());
		os >> temp;
		float dribblerSpeed = atof(temp.c_str());
		os >> temp;
		float kickerSpeed = atof(temp.c_str());

		Simulation::controlRobotByWheels(speedWheel1, speedWheel2, speedWheel3, speedWheel4, dribblerSpeed, kickerSpeed, indexRobot, indexScene);

		out << "ACK 13\n"; // confirmando pacote 13

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else if(temp.compare("14") == 0) //pacote 14 CONTROL ALL ROBOTS (CONTROL WHEELS)
	{
		//Lendo argumentos
		os >> temp;
		int indexScene = atoi(temp.c_str());

		//Limpando string para enviar
		this->sendString = "";

		//Definindo string para enviar
		stringstream out;

		//Lendo argumentos do robo e controlando
		for(int indexRobot=0; indexRobot<10; indexRobot++)
		{
			os >> temp;
			float speedWheel1 = atof(temp.c_str());
			os >> temp;
			float speedWheel2 = atof(temp.c_str());
			os >> temp;
			float speedWheel3 = atof(temp.c_str());
			os >> temp;
			float speedWheel4 = atof(temp.c_str());
			os >> temp;
			float dribblerSpeed = atof(temp.c_str());
			os >> temp;
			float kickerSpeed = atof(temp.c_str());

			Simulation::controlRobotByWheels(speedWheel1, speedWheel2, speedWheel3, speedWheel4, dribblerSpeed, kickerSpeed, indexRobot, indexScene);
		}

		out << "ACK 14\n"; // confirmando pacote 14

		//Construindo string para enviar
		this->sendString.append(out.str());
	}
	else
	{
		this->sendString = "NACK";
	}
}
