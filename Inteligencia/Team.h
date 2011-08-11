#pragma once
#include "Inteligencia.h"
#include <deque>
#include "Robot.h"

using namespace std;

namespace Inteligencia {

	class Team {

	private:
		//fields:
		Color _color;
		int _goals;
		int _yellow_card, _red_card;//counts how many cards the team has received
		deque<Robot*> _robot;

		//methods:
		void _init();
		void yellow_card(int);
		void red_card(int);
		void add_yellow_card();
		void add_red_card();

	public:
		Team(Color);
		Team(Color, deque<Robot*>);
		~Team();

		//methods:
		int yellow_card();
		int red_card();
		//setters:
		void color(Color);
		//getters:
		Color color();
		//useful:
		void add(Robot*);
		void add(deque<Robot*>);
		//void sort();

	};
}