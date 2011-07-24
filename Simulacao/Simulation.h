#pragma once

#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <time.h>

// Physics code
#undef random
#include "NxPhysics.h"
#include "UserAllocator.h"
#include "ErrorStream.h"
#include "NxCooking.h"
#include "Stream.h"

#include "Timing.h"
#include "MediaPath.h"
#include "cooking.h"
#include "NXU_helper.h"  // NxuStream helper functions.
//#include "Utilities.h"
//#include "SamplesVRDSettings.h"

#include "NxRobot.h"
#include "NxAllRobots.h"

#include "NxScene1.h"
#include "NxRobot.h"

using namespace std;

class MyUserNotify;

class Simulation
{
private:
	static bool gPause;
	static bool gSave;
	static int	gLoad;
	static bool gClear;

	static NxPhysicsSDK *gPhysicsSDK;
	static const NxU32 gMaxScenes = 100;
	static /*NxArray<NxScene1*>*/NxScene1* gScenes[gMaxScenes];
	static int nbExistScenes;
	static NxU32 gBaseScene;
	static NxVec3 gDefaultGravity;
	static UserAllocator *gMyAllocator;
	static ErrorStream gErrorStream;
	static MyUserNotify gUserNotify;
	//extern NxUserContactReport * robotContactReport;

	//Velocidades para controle das rodas
	static NxArray<NxReal*> lastWheelSpeeds;
	static NxArray<NxReal*> lastDesiredWheelSpeeds;
	static NxArray<NxReal*> lastWheelTorques; 

	static float timeStep;
	static time_t timeLastSimulate;

	static float widthBorderField;
	static float heightBorderField;

	friend class MyUserNotify;
	friend class UDPServerSimInt;
	friend class SimulationView;
private:
	static void releaseScene(NxScene &scene);
	static void CreateCube(const NxVec3 &pos, int size, const NxVec3 *initial_velocity = NULL);
	static void CreateStack(int size);
	static void CreateTower(int size);
	static bool InitNx();
	static bool InitBlankScene();
	static void ReleaseNx();

	static NxActor* cloneActor(NxActor* actorSource, int indexDestScene);
	static NxJoint* cloneJoint(NxJoint* jointSource, int indexDestScene);
	static void buildModelRobotWithDesc(int indexRobot, int indexScene);

	//Math
	static NxF32 calcDistanceVec2D( NxF32 x1, NxF32 y1, NxF32 x2, NxF32 y2 );
	static NxReal getBiggestAbsoluteValue(NxReal* values, int size);

	static NxActor* getActorBall(int indexScene);
	static NxActor* getActorRobot(int indexScene, int indexRobot);
	static NxActor* getActorRobotByLabel(int indexScene, string robotLabel);
	static NxActor* getActorWheel(int indexScene, int indexRobot, int indexWheel);
	static int getNumberWheels(int indexScene, int indexRobot);
	static NxJoint* getJoint(int indexScene, int indexJoint, int indexRobot);
	static NxArray<NxJoint*> getJoints(int indexScene, int indexRobot);
	static NxActor* getActorDribbler(int indexScene, int indexRobot);
	static NxActor* getActorKicker(int indexScene, int indexRobot);

	Simulation(void);
	~Simulation(void);
public:
	/**
	* Metodos para Inteligencia
	*/
	//build simulation
	static void cloneRobot(int indexRobot, int indexScene, int indexRobotSource, NxVec3 newPosition, int indexDestScene);
	static void cloneScene(int indexSource);

	//advance simulation
	static void simulate();
	static void simulate( int indexScene );
	static void simulate( int indexScene, float dt );

	//setters
	static void setRobotGlobalPose(NxMat34 pose, int indexScene, int indexRobot);
	static void setBallGlobalPos(NxVec3 pos, int indexScene);
	static void setRobotLinearVelocity(NxVec3 linVel, int indexScene, int indexRobot);
	static void setRobotAngularVelocity(NxVec3 angVel, int indexScene, int indexRobot);
	static void setBallLinearVelocity(NxVec3 linVel, int indexScene);
	static void setAngVelocityDribbler(NxReal velocityX, int indexRobot, int indexScene);

	//getters
	static NxVec3 getRobotGlobalPos( int indexRobot, int indexScene );
	static NxVec3 getBallGlobalPos( int indexScene );
	static NxMat33 getRobotGlobalOrientation( int indexRobot, int indexScene );
	static NxReal getAngle2DFromRobot( int indexRobot, int indexScene );
	static NxVec3 getFieldExtents(int indexScene);

	//controlers
	static void controlDribbler( float dribblerSpeed, int indexRobot, int indexScene );
	static void executeKicker( float kickerSpeed, int indexRobot, int indexScene );
	static void controlWheels( NxReal* wheelsSpeeds, int indexScene, NxI32 indexRobot );
	static void controlRobot(float speedX, float speedY, float speedAng, float dribblerSpeed, float kickerSpeed, int indexRobot, int indexScene);
	static void controlRobotByWheels(float speedWheel1, float speedWheel2, float speedWheel3, float speedWheel4, float dribblerSpeed, float kickerSpeed, int indexRobot, int indexScene);
	static void addLocalTorqueDribbler(NxReal torqueX, int indexRobot, int indexScene);
	static void addLocalForceKicker(NxReal forceX, int indexRobot, int indexScene);

	//math
	static NxReal getAngle2DFromMat33( NxMat33 matrixOrientation );

	//Metodos da inteligencia
	static NxReal calcTorqueFromWheelSpeed(NxReal currentDesiredWheelSpeed, NxReal currentWheelSpeed, int indexScene, int indexRobot, int indexWheel);
	static NxReal* calcWheelSpeedFromRobotSpeed( NxReal speedAng, NxReal speedX, NxReal speedY, int indexRobot, int indexScene );
	static void goToThisPose( NxReal x, NxReal y, NxReal angle, int indexRobot, int indexScene );
	static void infinitePath( int indexRobot );
};

/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////CLASS MyUserNotify////////////////////////////////////////////////////////////////////

class MyUserNotify: public NXU_userNotify, public NXU_errorReport
{
public:
	virtual void	NXU_errorMessage(bool isError, const char *str);

	virtual void	NXU_notifyScene(NxU32 sno,	NxScene	*scene,	const	char *userProperties);

	virtual void	NXU_notifyJoint(NxJoint	*joint,	const	char *userProperties);

	virtual void	NXU_notifyActor(NxActor	*actor,	const	char *userProperties);

	virtual void	NXU_notifyCloth(NxCloth	*cloth,	const	char *userProperties);

	virtual void	NXU_notifyFluid(NxFluid	*fluid,	const	char *userProperties);

	virtual void 	NXU_notifyTriangleMesh(NxTriangleMesh *t,const char *userProperties);

	virtual void 	NXU_notifyConvexMesh(NxConvexMesh *c,const char *userProperties);

	virtual void 	NXU_notifyClothMesh(NxClothMesh *t,const char *userProperties);

	virtual void 	NXU_notifyCCDSkeleton(NxCCDSkeleton *t,const char *userProperties);

	virtual void 	NXU_notifyHeightField(NxHeightField *t,const char *userProperties);

	virtual NxScene *NXU_preNotifyScene(unsigned	int	sno, NxSceneDesc &scene, const char	*userProperties);

	virtual bool	NXU_preNotifyJoint(NxJointDesc &joint, const char	*userProperties);

	virtual bool	NXU_preNotifyActor(NxActorDesc &actor, const char	*userProperties);

	virtual bool 	NXU_preNotifyTriangleMesh(NxTriangleMeshDesc &t,const char *userProperties);

	virtual bool 	NXU_preNotifyConvexMesh(NxConvexMeshDesc &t,const char *userProperties);

	virtual bool 	NXU_preNotifyClothMesh(NxClothMeshDesc &t,const char *userProperties);

	virtual bool 	NXU_preNotifyCCDSkeleton(NxSimpleTriangleMesh &t,const char *userProperties);

	virtual bool 	NXU_preNotifyHeightField(NxHeightFieldDesc &t,const char *userProperties);

	virtual bool 	NXU_preNotifySceneInstance(const char *name,const char *sceneName,const char *userProperties,NxMat34 &rootNode,NxU32 depth);

	virtual void	NXU_notifySceneFailed(unsigned	int	sno, NxSceneDesc &scene, const char	*userProperties);

	virtual void	NXU_notifyJointFailed(NxJointDesc &joint, const char	*userProperties);

	virtual void	NXU_notifyActorFailed(NxActorDesc &actor, const char	*userProperties);

	virtual void 	NXU_notifyTriangleMeshFailed(NxTriangleMeshDesc &t,const char *userProperties);

	virtual void 	NXU_notifyConvexMeshFailed(NxConvexMeshDesc &t,const char *userProperties);

	virtual void 	NXU_notifyClothMeshFailed(NxClothMeshDesc &t,const char *userProperties);

	virtual void 	NXU_notifyCCDSkeletonFailed(NxSimpleTriangleMesh &t,const char *userProperties);

	virtual void 	NXU_notifyHeightFieldFailed(NxHeightFieldDesc &t,const char *userProperties);

	MyUserNotify(void);
	~MyUserNotify(void);
};