
#include "UDPClient.h"

UDPClient::UDPClient(void)
{
	echoString = "";
	servAddress = "127.0.0.1";
	echoServPort = 9876;
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
	this->echoString = echoString;
	this->servAddress = servAddress;
	this->echoServPort = echoServPort;
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
  echoStringLen = strlen(echoString);

  if (echoStringLen > ECHOMAX) {    // Check input length
    cerr << "Echo string too long" << endl;
    exit(1);
  }
  //unsigned short echoServPort = Socket::resolveService("echo", "udp");

  try {
    UDPSocket sock;
  
    // Send the string to the server
    sock.sendTo(echoString, echoStringLen, servAddress, echoServPort);
  
    // Receive a response
    //char echoBuffer[ECHOMAX + 1];       // Buffer for echoed string + \0
    //int respStringLen;                  // Length of received response
    //if ((respStringLen = sock.recv(echoBuffer, ECHOMAX)) != echoStringLen) {
    //  cerr << "Unable to receive" << endl;
    //  exit(1);
    //}
  
    //echoBuffer[respStringLen] = '\0';             // Terminate the string!
    //cout << "Received: " << echoBuffer << endl;   // Print the echoed arg

    // Destructor closes the socket

  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }
}