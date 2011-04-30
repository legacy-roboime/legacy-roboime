#include <list>
#include "Stage.h"

public class Strategy {

private:
	//fields:
	static Stage _stage;
	static list<Strategy> child;
	static void init();//must always be called on the constructor

public:
	//fields:
	int steps;
	bool active;
	Stage stage;
	TeamPose team_pose;

	//methods:
	bool update_stage(Stage);
	bool reset_stage();
	bool take_step();

};