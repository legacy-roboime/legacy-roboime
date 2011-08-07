#pragma once
#include <string>
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
		//fields:
		int _yellow_card, _red_card;//counts how many cards of each robot has received
		int _i;//_index is the index, and _i is the internal index
		int _color_code;//color code//TODO: implement
		double _x, _y, _speedx, _speedy, _angle;//position, speed, and orientation
		Command* _command;//the one to dispatch its commands

		//methods:
		void _init();//used in the constructors for basic initialization
		string _summary();
		//modifiers:
		void repair();//fixes all broken parts
		void break_down();//raise an unknow break status
		void i(int);
		void yellow_card(int);
		void red_card(int);
		void add_yellow_card();
		void add_red_card();
		void x(double);
		void y(double);
		void angle(double);
		void speedx(double);//this has to be estimated somehow
		void speedy(double);//this has to be estimated somehow
		void place(double, double);

	public:
		Robot();
		Robot(int index);//constructor
		~Robot();//destructor

		//components:
		Dribbler* dribbler;//dribbler component
		Kicker* kicker;//kicker component
		Motor* motor;//motor component
		Body* body;//body component
		Wheel* wheel[4];//0:front-left, 1:front-right, 2:back-left, 3:back-right wheels

		//methods:
		bool can_kick();//check if the robot has kicker component and it's working
		bool can_dribble();//chekc if the robot has dribbler component and it's working
		bool is_working();//checks if the robot is working
		bool is_broken();//checks if the robot is broken (!working)
		void new_command();//creates a new blank command
		void command(Command*);//adds a command to be executed
		void command(double speed[4]);//
		void command(double, double, double, double);//
		//void commander(Commander*);//sets its commander
		//void updater(Updater*);//sets its updater//NOTE: this generates circular dependency, stop!
		string summary();
		void kick();//kick with the standard speed
		void kick(double);//kick with the given speed
		void dribble();//dribble with the standard speed
		void dribble(double);//dribble with the given speed
		//getters:
		int i();
		int yellow_card();
		int red_card();
		double x();
		double y();
		double angle();
		double speedx();
		double speedy();
		//double* place();//returns {x,y}//TODO: think about it
		Command* command();
	};
}