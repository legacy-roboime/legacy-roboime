#ifndef NX_ALL_ROBOTS
#define NX_ALL_ROBOTS

#include <set>
#include "NxRobot.h"

class NxAllRobots {
private:
	static std::set<NxRobot*> _allRobots;
	static NxArray<NxRobot*> _allRobotsSequential;
	static std::set<NxRobot*> _allChildRobots;
	
	static NxI32 _activeRobot;
	static NxRobot* _activeRobotP;
	static void setActiveRobotP();
public:
	static void AddRobot(NxRobot* v);
	static void AddChildRobot(NxRobot* v);
	//static void RemoveRobot(NxRobot* v);

	static void updateAllRobots(NxReal lastTimeStep);
	static void drawRobots(bool debug = false);

	static bool isRobot(NxRobot* v);
	static void handlePair(NxContactPair& pair, NxU32 events);

	static NxU32 getNumberOfRobots() { return (NxU32)_allRobots.size(); }
	static void setActiveRobot(NxI32 v) { _activeRobot = v; setActiveRobotP(); }
	static NxRobot* getActiveRobot() { return _activeRobotP; }
	static NxI32 getActiveRobotNumber() { return _activeRobot; }
	static void selectNext();
	
	static NxRobot* getRobotById(int indexRobot);
	static NxRobot* getRobot(int indexRobot, int indexScene, int idTeam);
	static int getBiggestIndexRobot();
	~NxAllRobots();
};

#endif
