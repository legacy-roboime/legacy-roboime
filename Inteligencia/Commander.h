#pragma once
#include "Inteligencia.h"
#include <deque>
#include <string>
#include <sstream>
#include <iostream>
#include "Command.h"
#include "Robot.h"

using namespace std;

namespace Inteligencia {

	class Commander {

	protected:
		//fields:
		deque<Robot*> _robot;
		deque<Command*> _log;
		bool __log;

	public:
		Commander();
		~Commander();

		//methods:
		virtual void add(Robot*);
		virtual void del(Robot*);
		virtual void prepare();
		virtual void send();
		virtual void step();

	};
}