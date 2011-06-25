#pragma once
#include <list>
#include "Robot.h"
using namespace std;
namespace Inteligencia {

	class Team {

	private:
		//fields:
		int _i;
		list<Robot*> _robot;

		//methods:
		void _init();

	public:
		Team(void);
		Team(list<Robot*>);
		~Team(void);

		//methods:
		//setters:
		void i(int);
		//getters:
		int i();
		//useful:
		void add(Robot*);
		void sort();

	};
}