#pragma once
#include "Inteligencia.h"
#include <deque>
#include <QThread>
#include <QMutex>
#include "Updater.h"

#include "robocup_ssl_client.h"
#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"

namespace Inteligencia {

	class UpdaterVision : public Updater, public QThread {
	private:
		RoboCupSSLClient _client;
		deque<SSL_WrapperPacket> _packet;
		QMutex _mutex;
		bool _stop;

		//methods:
		void run();

	public:
		UpdaterVision();
		UpdaterVision(string address, int port);
		~UpdaterVision();

		//methods:
		void stop();
		void prepare();
		void receive();

	};
}