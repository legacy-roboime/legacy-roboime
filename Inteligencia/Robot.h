#include "Component.h"
#include "Dribbler.h"
#include "Kicker.h"
#include "Motor.h"
#include "Wheel.h"
#include "Body.h"

public class Robot : Component{

private:
	//fields:
	bool yellow_card, red_card;

public:
	//fields:
	int index;
	Dribbler dribbler;
	Kicker kicker;
	Motor motor;
	Wheel wheel[4];
	Body body;
	Pose pose;
	double accel[3];

	//methods:
	bool can_kick();
	bool kick();
	bool can_dribble();
	bool dribble();

};