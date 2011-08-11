#pragma once
#include "Inteligencia.h"
#include <deque>
#include "Robot.h"

using namespace std;

namespace Inteligencia {

	class Team {

	private:
		//fields:
		int _i;
		deque<Robot*> _robot;

		//methods:
		void _init();

	public:
		Team();
		Team(deque<Robot*> team);
		~Team();

		//methods:
		//setters:
		void i(int);
		//getters:
		int i();
		//useful:
		void add(Robot*);
		//void sort();

	};
}