#pragma once
#include "Inteligencia.h"
#include <deque>
#include <QThread>
#include <QMutex>
#include "Commander.h"
#include "netraw.h"

namespace Inteligencia {

	class CommanderTX : public Commander, public QThread {
		
	private:
		Net::UDP mc; // multicast server
		QMutex mutex;
		int _port;
		string _net_address;
		string _net_interface;
		deque<string> _queue;
		bool _stop;
		//methods:
		void run();
		bool open();
		void close();
		bool send(string buffer);

	public:
		CommanderTX(string address="127.0.0.1", int port=9050);
		~CommanderTX();
		//methods:
		void add(Robot*);
		void stop();
		void prepare();
		void step();
		void send();
	};
}