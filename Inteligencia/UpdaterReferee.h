#pragma once
#include "Inteligencia.h"
#include <deque>
#include <QThread>
#include <QMutex>
#include "Updater.h"
#include "netraw.h"
#include <sstream>

namespace Inteligencia {

	class UpdaterReferee : public Updater, public QThread {
	private:
		//SSL CLIENT
		static const int MaxDataGramSize = 6;//Each UDP packet contains 6 Bytes
		char* in_buffer;
		Net::UDP mc; // multicast client
		QMutex mutex;
		int _port;
		string _net_address;
		string _net_interface;
		//UpdaterReferee
		deque<char*> _queue;
		bool _stop;
		//methods:
		bool open(bool blocking=false);
		void close();
		void run();
		bool _receive();

	public:
		UpdaterReferee(string address="224.5.23.1", int port=10001);
		~UpdaterReferee();
		//methods:
		void stop();
		void prepare();
		void receive();

	};
}