#pragma once

class Command {

private:
	//fields:
	bool _kick, _dribble;
	double _orientation, _speed;

public:
	Command(double orientation, double speed);
	Command(double orientation, double speed, bool kick, bool drible);
	Command(void);//Constructor
	~Command(void);//Destructor

	//methods:
	void kick();
	void start_dribbler();
	void stop_dribbler();

};