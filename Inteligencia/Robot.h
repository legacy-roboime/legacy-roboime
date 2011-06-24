#pragma once
#include <list>
#include "Component.h"
#include "Dribbler.h"
#include "Kicker.h"
#include "Motor.h"
#include "Wheel.h"
#include "Body.h"
#include "Command.h"

using namespace std;

namespace Inteligencia {	

	class Robot : Component {
		friend class TeamCommand;

	//private:
	public:

		//fields:
		int _yellow_card, _red_card;//counts how many cards of each robot has received
		int _i;//_index is the index, and _i is the internal index
		double _x, _y, _speed, _angle;//position, speed, and orientation
		Command* _command;//command to be executed
		Dribbler* _dribbler;//dribbler component
		Kicker* _kicker;//kicker component
		Motor* _motor;//motor component
		Body* _body;//body component
		Wheel* _wheel[4];//0:front-left, 1:front-right, 2:back-left, 3:back-right wheels

		//methods:
		void _init();//used in the constructors for basic initialization

	public:
		Robot();
		Robot(int index);//constructor
		~Robot();//destructor	

		//methods:
		bool can_kick();//check if the robot has kicker component and it's working
		bool can_dribble();//chekc if the robot has dribbler component and it's working
		bool is_working();//checks if the robot is working
		bool is_broken();//checks if the robot is broken (!working)
		void repair();//fixes all broken parts
		void break_down();//raise an unknow break status
		//void compel(Command);//compel a command = issue an order

		//useful methods:
		void kick();//kick with the standard speed
		void kick(double);//kick with the given speed
		void dribble();//dribble with the standard speed
		void dribble(double);//dribble with the given speed
		void place(double, double);

	};
}