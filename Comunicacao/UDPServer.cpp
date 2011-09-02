
#include "UDPServer.h"
#include <windows.h>          // For ::Sleep()

UDPServer::UDPServer(void)
{
	echoServPort = 9876;
	sourcePort = 0;
	sourceAddress = "127.0.0.1";
	for (int i=0; i<ECHOMAX; i++)  echoBuffer[i] = 0;
	recvMsgSize = 0;
	this->receiveString = "";
	this->sendString = "";
	//ballRadius = 21.5;
	//ptrDataBaseVision = -1;	
	//for (int i=0; i<sizeDataBaseVision; i++) dataBaseVision[i] = DataBaseVision();
}

UDPServer::UDPServer(unsigned short port, string address)
{
	for (int i=0; i<ECHOMAX; i++)  echoBuffer[i] = 0;
	recvMsgSize = 0;
	this->receiveString = "";
	this->sendString = "";
	//ballRadius = 21.5;
	//ptrDataBaseVision = -1;	
	//for (int i=0; i<sizeDataBaseVision; i++) dataBaseVision[i] = DataBaseVision();
	echoServPort = port;
	sourcePort = port;
	sourceAddress = address;
}

UDPServer::~UDPServer(void)
{
}

void UDPServer::func1()
{
  try {
	Sleep(7000); //Wait the Simulation Start
    UDPSocket sock(echoServPort);                
    for (;;) {  // Run forever
      // Block until receive message from a client
      recvMsgSize = sock.recvFrom(echoBuffer, ECHOMAX, sourceAddress, sourcePort);
  
	  if (recvMsgSize>0)
	  {
		  receiveString = echoBuffer;
		  parsing();
		  //string temp; 
		  //std::stringstream os(s);
		  //os >> temp;
		  /*if(temp.compare("1") == 0)//pacote 1
		  {
			float robots[numRobots][numInfo];
			float ballRadius;
			float ballX;
			float ballY;
			float ballSpeedX;
			float ballSpeedY;
		    //Bola X
			os >> temp;
			istringstream a(temp);
			a >> ballX;
			//Bola Y
			os >> temp;
			istringstream b(temp);
			b >> ballY;
			//Velocidade Bola X
			os >> temp;
			istringstream c(temp);
			c >> ballSpeedX;
			//Velocidade Bola Y
			os >> temp;
			istringstream d(temp);
			d >> ballSpeedY;
			//Robos ID, X, Y, ANGULO
			for(int i=0; i<numRobots; i++)
			{
				//ID
				os >> temp;
				istringstream e(temp);
				e >> robots[i][0];
				//X
				os >> temp;
				istringstream f(temp);
				f >> robots[i][1];
				//Y
				os >> temp;
				istringstream g(temp);
				g >> robots[i][2];
				//ANGULO
				os >> temp;
				istringstream h(temp);
				h >> robots[i][3];
			}
			//ptrDataBaseVision++;
			//ptrDataBaseVision = ptrDataBaseVision%sizeDataBaseVision;
			dataBaseVision[ptrDataBaseVision].ballX = ballX;
			dataBaseVision[ptrDataBaseVision].ballY = ballY;
			dataBaseVision[ptrDataBaseVision].ballSpeedX = ballSpeedX;
			dataBaseVision[ptrDataBaseVision].ballSpeedY = ballSpeedY;
			for(int i=0; i< numRobots; i++)
			{
				dataBaseVision[ptrDataBaseVision].robots[i][1] = robots[i][1];
				dataBaseVision[ptrDataBaseVision].robots[i][2] = robots[i][2];
				dataBaseVision[ptrDataBaseVision].robots[i][3] = robots[i][3];
			}
		  }*/

		  //cout << "Received packet from " << sourceAddress << ":" << sourcePort << endl;
		  this->sendString.copy(echoBuffer, sendString.length(), 0);
		  recvMsgSize = sendString.length();//FIXED
		  sock.sendTo(echoBuffer, recvMsgSize, sourceAddress, sourcePort);
	  }
    }
  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }
}

void UDPServer::parsing()
{
	printf("PARSING SUPER UDPServer");
}

string UDPServer::getLastReceivedString()
{
	return receiveString;
}

