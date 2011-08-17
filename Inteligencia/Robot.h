#pragma once
#include "Inteligencia.h"
#include <string>
#include <QMutex>
#include "Body.h"
#include "Component.h"
#include "Dribbler.h"
#include "Kicker.h"
#include "Motor.h"
#include "Wheel.h"
//out of base dependencies:
#include "Commander.h"
#include "Updater.h"

using namespace std;

namespace Inteligencia {

	class Robot : Component {
		friend class UpdateRobot;

	private:
		QMutex _mutex;

		//components:
		Dribbler* _dribbler;//dribbler component
		Kicker* _kicker;//kicker component
		Motor* _motor;//motor component
		Body* _body;//body component
		Wheel* _wheel[4];//0:front-left, 1:front-right, 2:back-left, 3:back-right wheels

		//fields:
		int _id;//_index is the index, and _i is the internal index
		int _cc;//color code//TODO: implement
		real _x, _y, _speedx, _speedy, _angle;//position, speed, and orientation
		Command* _command;//the one to dispatch its commands

		//methods:
		void _init();//used in the constructors for basic initialization
		string _summary();
		//modifiers:
		void repair();//fixes all broken parts
		void break_down();//raise an unknow break status
		void id(int);
		void cc(int);
		void x(real);
		void y(real);
		void angle(real);
		void speedx(real);//this has to be estimated somehow
		void speedy(real);//this has to be estimated somehow
		void place(real, real);

	public:
		Robot();
		Robot(int id, int cc);//constructor
		~Robot();//destructor

		//components:
		Dribbler* dribbler();//access dribbler
		Kicker* kicker();//access kicker
		Motor* motor();//access motor
		Body* body();//access body
		Wheel** wheel();//access wheels
		size_t wheels();//number of wheels

		//methods:
		bool can_kick();//check if the robot has kicker component and it's working
		bool can_dribble();//chekc if the robot has dribbler component and it's working
		bool is_working();//checks if the robot is working
		bool is_broken();//checks if the robot is broken (!working)
		void new_command();//creates a new blank command
		void command(Command*);//adds a command to be executed
		void command(real speed[4]);//
		void command(real, real, real, real);//
		//void commander(Commander*);//sets its commander
		//void updater(Updater*);//sets its updater//NOTE: this generates circular dependency, stop!
		string summary();
		void kick();//kick with the standard speed
		void kick(real);//kick with the given speed
		void dribble();//dribble with the standard speed
		void dribble(real);//dribble with the given speed
		//getters:
		int id();
		int cc();
		real x();
		real y();
		real angle();
		real speedx();
		real speedy();
		//real* place();//returns {x,y}//TODO: think about it
		Command* command();
	};
}