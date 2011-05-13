#pragma once
#include <list>
#include <string.h>
#include "Stage.h"
#include "TeamCommand.h"

using namespace std;

class Strategy {

private:
	//static fields:
	static list<int> __i;//internal use for internal index

	//fields:
	int _i;

protected:
	Strategy(void);//must always be called on the constructor

	//static fields:
	static Stage __stage;
	static list<Strategy*> _strategy;

	//fields:
	TeamCommand _team_command;
	Stage _stage;
	int _steps;
	bool _active;
	char _name[40];

	//methods:
	void _take_step();
	void _init();

public:
	Strategy(char name[40]);
	Strategy(Stage stage);
	~Strategy(void);

	//methods:
	void change_stage(Stage stage);
	void set_global_stage(void);
	void take_step(void);

};