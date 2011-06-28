#pragma once
#include <deque>
#include <string>
#include <sstream>
#include <iostream>
#include "Command.h"

using namespace std;
namespace Inteligencia {

	class Commander {

	protected:
		//fields:
		deque<Command*> _command;
		deque<Command*> _log;
		bool __log;

	public:
		Commander();
		~Commander();

		//methods:
		void add(Command*);
		void del(Command*);
		virtual void prepare() = 0;
		virtual void send() = 0;
		void step();

	};
}