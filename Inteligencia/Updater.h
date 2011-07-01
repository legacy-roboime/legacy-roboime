#pragma once
#include <deque>
#include <string>
#include <sstream>
#include <iostream>
#include "Robot.h"
#include "Ball.h"
#include "Update.h"

using namespace std;
namespace Inteligencia {

	class Updater {

	private:
		//fields:
		deque<Ball*> _ball;
		deque<Robot*> _robot;

	protected:
		deque<Update*> _update;
		deque<Update*> _log;
		bool __log;

	public:
		Updater();
		~Updater();

		//methods:
		virtual void receive() = 0;//receive the information
		virtual void prepare() = 0;//prepare means parse on most implementations
		void step();//receive and prepare
		void apply();
		int robots();//how many robots?
		Robot* robot(int);//-th robot
		int balls();//how many balls?
		Ball* ball(int);//-th ball
		//add:
		void add(Robot*);
		void add(Ball*);
		//del:
		void del(Robot*);
		void del(Ball*);
		//update:
		

	};
}