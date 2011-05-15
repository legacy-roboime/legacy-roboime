
#include "UDPClient.h"

UDPClient::UDPClient(void)
{
	//echoString = "";
	servAddress = "127.0.0.1";
	echoServPort = 9876;
	sendString = "";
	//echoServPort = 9876;
	//sourcePort = 0;
	//sourceAddress = "127.0.0.1";
	//for (int i=0; i<ECHOMAX; i++)  echoBuffer[i] = 0;
	//recvMsgSize = 0;
	//ballRadius = 21.5;
	//ptrDataBaseVision = -1;	
	//for (int i=0; i<sizeDataBaseVision; i++) dataBaseVision[i] = DataBaseVision();
}

UDPClient::UDPClient(string servAddress, char* echoString, unsigned short echoServPort)
{
	//this->echoString = echoString;
	this->servAddress = servAddress;
	this->echoServPort = echoServPort;
	sendString = "";
	//for (int i=0; i<ECHOMAX; i++)  echoBuffer[i] = 0;
	//recvMsgSize = 0;
	//ballRadius = 21.5;
	//ptrDataBaseVision = -1;	
	//for (int i=0; i<sizeDataBaseVision; i++) dataBaseVision[i] = DataBaseVision();
	//echoServPort = port;
	//sourcePort = port;
	//sourceAddress = address;
}

UDPClient::~UDPClient(void)
{
}

void UDPClient::func1()
{
  echoStringLen = strlen(sendBuffer);

  if (echoStringLen > ECHOMAX) {    // Check input length
    cerr << "Echo string too long" << endl;
    exit(1);
  }
  //unsigned short echoServPort = Socket::resolveService("echo", "udp");

  try {
    UDPSocket sock;
  
	this->sendString.copy(sendBuffer, sendString.length(), 0);
    // Send the string to the server
    sock.sendTo(sendBuffer, echoStringLen, servAddress, echoServPort);
  
    // Receive a response
    respStringLen = sock.recv(echoBuffer, ECHOMAX); // Length of received response

	echoBuffer[respStringLen] = '\0';             // Terminate the string!
    //cout << "Received: " << echoBuffer << endl;   // Print the echoed arg
  
	if(respStringLen > 0)
	{
		response = echoBuffer;
		parsing();
		//string temp; 
		//std::stringstream os(response);
		//os >> temp;
	}

    // Destructor closes the socket
	//sock.disconnect();
	//sock.cleanUp();

  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }
}

void UDPClient::parsing()
{
	//printf("PARSING SUPER UDPClient");
}

string UDPClient::getLastReceivedString()
{
	return response;
}

void UDPClient::setSendString(string sendString)
{
	this->sendString = sendString;
}