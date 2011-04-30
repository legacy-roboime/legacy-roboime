#include <list>
#include "Stage.h"

public class Strategy {

private:
	//fields:
	static Stage _stage;
	static list<Strategy> child;
	static void init();//must be included on the constructor

public:
	//fields:
	int steps;
	bool active;
	Stage stage;

	//methods:
	bool update_stage(Stage);
	bool reset_stage();
	bool take_step();

};