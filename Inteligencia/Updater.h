#pragma once
#include <deque>
#include <string>
#include <sstream>
#include <iostream>
#include "Base.h"
#include "Update.h"

using namespace std;
namespace Inteligencia {

	class Updater {

	private:
		//fields:
		deque<Ball*> _ball;
		deque<Robot*> _robot;
		deque<Update*> _update;

	public:
		Updater();
		~Updater();

		//methods:
		//add:
		void add(Robot*);
		void add(Ball*);
		void add(Team*);
		void add(Stage*);
		//del:
		void del(Robot*);
		void del(Ball*);
		void del(Team*);
		void del(Stage*);
		//update:
		//void u(SIMStatusSingle*);//FIXME: Refactor this

	};

}