#pragma once
#include <QThread>
#include <QMutex>
#include <QMutexLocker>

//#include "timer.h"//TODO: make this work
#include "robocup_ssl_server.h"
#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"

using namespace std;
namespace Simulation {

	class SSLServer : public QThread {
	private:
		RoboCupSSLServer _server;
		QMutex _mutex;
		bool _stop;

		//methods:
		void run();

	public:
		SSLServer();
		SSLServer(string address, int port);
		~SSLServer();

		//methods:
		void stop();
		void prepare();
		void send();

	};
}