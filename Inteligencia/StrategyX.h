#pragma once
#include "Strategy.h"

class StrategyX : public Strategy {

//protected:
public:
	StrategyX(void);//must always be called on the constructor

//public:
	StrategyX(char name[40]);
	StrategyX(Stage stage);
	~StrategyX(void);

	//methods:
	//TODO: add commonly used methods;

};