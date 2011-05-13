#pragma once
#include <list>
#include "Component.h"
#include "Dribbler.h"
#include "Kicker.h"
#include "Motor.h"
#include "Wheel.h"
#include "Body.h"
#include "Pose.h"
#include "Command.h"

using namespace std;

class Robot : Component {
	friend class TeamCommand;

private:
	//static fields:
	static list<Robot*> _robot;//Holds all robots of the class
	static list<int> __i;//internal use for internal index

	//fields:
	int _yellow_card, _red_card;//counts how many cards of each robot has received
	int _index, _i;//_index is the index, and _i is the internal index
	Pose _pose;//current pose (position+speed+accel+orientation)
	Command _command;//command to be executed
	Dribbler _dribbler;//dribbler component
	Kicker _kicker;//kicker component
	Motor _motor;//motor component
	Body _body;//body component
	Wheel _wheel[4];//0:front-left, 1:front-right, 2:back-left, 3:back-right wheels

	//methods:
	void _init();//used in the constructor to add robot to static list _robot

public:
	Robot(void);
	Robot(int index, Pose pose);//constructor
	~Robot(void);//destructor	

	//methods:
	bool can_kick(void);//check if the robot has kicker component and it's working
	void kick(void);//compel the robot to kick
	bool can_dribble(void);//chekc if the robot has dribbler component and it's working
	void start_dribbler(void);//compel the robot start dribbling
	void stop_dribbler(void);//compel the robot stop dribbling
	bool is_working(void);//checks if the robot is working
	bool is_broken(void);//checks if the robot is broken (!working)
	void repair(void);//fixes all broken parts
	void break_down(void);//set robot working status to false
	void compel(Command);//compel a command = issue an order

};