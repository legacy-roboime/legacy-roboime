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
		friend class Update;//do not remove this

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
		virtual void prepare();//prepare means parse on most implementations
		virtual void step();//receive, prepare and apply
		void apply();
		size_t robots();//how many robots?
		Robot* robot(size_t);//-th robot
		size_t balls();//how many balls?
		Ball* ball(size_t);//-th ball
		//add:
		void add(Robot*);
		void add(Ball*);
		//del:
		void del(Robot*);
		void del(Ball*);
		//update:
		

	};
}