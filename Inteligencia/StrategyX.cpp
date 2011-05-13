#include "StrategyX.h"

StrategyX::StrategyX(void) : Strategy() {}

StrategyX::StrategyX(char name[40]) : Strategy(name) {}

StrategyX::StrategyX(Stage stage) : Strategy(stage) {}

StrategyX::~StrategyX(void) {}
	//{puts("DESTROYEDX!!!!!");}