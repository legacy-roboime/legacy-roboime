#pragma once
#include "Inteligencia.h"
#include <deque>
#include <QThread>
#include <QMutex>
#include "Updater.h"

namespace Inteligencia {

	class UpdaterReferee : public Updater, public QThread {
	private:
		deque<string> _queue;
		QMutex _mutex;

		//methods:
		void run();

	public:
		UpdaterReferee();
		UpdaterReferee(string address, unsigned short port);
		~UpdaterReferee();

		//methods:
		void start();
		void stop();
		void prepare();
		void receive();
	};
}