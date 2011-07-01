#pragma once
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
		void add(Robot*);
		void del(Robot*);
		virtual void prepare() = 0;
		virtual void send() = 0;
		void step();

	};
}