#pragma once
#define NOMINMAX
#include <QThread>
#include <QMutex>
#include <QMutexLocker>

//#include "timer.h"//TODO: make this work
#include "robocup_ssl_server.h"
#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"

using namespace std;
//namespace LibSimulation {

	class SSLServer : public QThread {
	private:
		SSL_WrapperPacket wrapperPacket;
		RoboCupSSLServer server;
		QMutex mutex;
		bool withDetection, withGeometry;

		//methods:
		void run();

	public:
		SSLServer();
		SSLServer(string address, int port);
		~SSLServer();

		//methods:
		void prepare();
		void send();
		void refresh();

	};
//}