#pragma once

#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>
using namespace std;

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Physics code
#undef random
#include "NxPhysics.h"
#include "UserAllocator.h"
#include "ErrorStream.h"
#include "NxCooking.h"
#include "Stream.h"
#include "DrawObjects.h"
//#include "PerfRenderer.h"
#include "Timing.h"
#include "DebugRenderer.h"
#include "MediaPath.h"
//#include "Utilities.h"
//#include "SamplesVRDSettings.h"
#include "cooking.h"
#include "NXU_helper.h"  // NxuStream helper functions.

#include "NxVehicle.h"
#include "NxAllVehicles.h"

#include "NxScene1.h"
//#include "UDPServerThread.h";
//#include "UDPServerSimInt.h"
//#include "MyUserNotify.h"

#ifdef __PPCGEKKO__
#include "GLFontRenderer.h"
printf("__PPCGEKKO__");
#endif

class MyUserNotify;

class Simulation
{
private:
	// static variables
	static bool gPause;
	static NxPhysicsSDK *gPhysicsSDK;
	static const NxU32 gMaxScenes = 1;
	static NxScene1 *gScenes[gMaxScenes];
	static NxU32 gCurrentScene;
	static NxVec3 gDefaultGravity;
	static UserAllocator *gMyAllocator;
	static ErrorStream gErrorStream;
	static DebugRenderer gDebugRenderer;
	//static PerfRenderer    gPrefRenderer;

	static int gMainHandle;
	static NxVec3 gEye;
	static NxVec3 gDirection;
	static NxVec3 gNormal;
	static int gMouseX;
	static int gMouseY;

	static MyUserNotify gUserNotify;

	static bool gSave;
	static int	gLoad;
	static bool gClear;

	//static Thread* Simulation::udpServerThread;

	//Velocidades para controle das rodas
	static NxReal lastWheelSpeeds[10][4];
	static NxReal lastDesiredWheelSpeeds[10][4];
	static NxReal lastWheelTorques[10][4];

	//Robot
	//extern NxUserContactReport * robotContactReport;
	static bool keyDown[256];

	static float timeStep;

	friend class MyUserNotify;
	friend class UDPServerSimInt;
private:
	static void releaseScene(NxScene &scene);
	static NX_BOOL LoadScene(const char *pFilename,NXU::NXU_FileType type);
	static void SaveScene(const char *pFilename);
	static void CreateCube(const NxVec3 &pos, int size, const NxVec3 *initial_velocity = NULL);
	static void CreateStack(int size);
	static void CreateTower(int size);
	static bool InitNx();
	static bool InitBlankScene();
	static void ReleaseNx();
	static void appKey(unsigned char key, bool down);
	static void callback_keyUp(unsigned char c, int x, int y);
	static void callback_key(unsigned char c, int x, int y);
	static void ArrowKeyCallback(int key, int x, int y);
	static void MouseCallback(int button, int state, int x, int y);
	static void MotionCallback(int x, int y);
	static bool FileExistTestSimple(const char *fname);
	static void RenderCallback();
	static void setupCamera();
	static void ReshapeCallback(int width, int height);
	static void IdleCallback();
	static void CSL_Scene();

	//static void refreshDataFromServer();
	//static void parserDataFromServer();

	//Robot
	static void createRobotWithDesc(int indexRobot);
	//Math
	static NxF32 calcDistanceVec2D( NxF32 x1, NxF32 y1, NxF32 x2, NxF32 y2 );
	static NxReal getBiggestAbsoluteValue(NxReal* values, int size);

public:
	static bool flagRender;

	static NxActor* getActorBall(int indexScene);
	static NxActor* getActorRobot(int indexScene, int indexRobot);
	static NxJoint* getJoint(int indexScene, int indexJoint, int indexRobot);
	static NxActor* getActorDribbler(int indexScene, int indexRobot);
	static NxActor* getActorKicker(int indexScene, int indexRobot);
	static NxVec3 getFieldExtents(int indexScene);

	Simulation(void);
	~Simulation(void);
	static void function(int argc, char **argv);

	//Metodos para Inteligencia
	static void simulate();
	static void simulate( int indexScene );

	static void setRobotGlobalPose(NxMat34 pose, int indexScene, int indexRobot);
	static void setBallGlobalPos(NxVec3 pos, int indexScene);
	static void setRobotLinearVelocity(NxVec3 linVel, int indexScene, int indexRobot);
	static void setRobotAngularVelocity(NxVec3 angVel, int indexScene, int indexRobot);
	static void setBallLinearVelocity(NxVec3 linVel, int indexScene);
	static void setAngVelocityDribbler(NxReal velocityX);

	static NxVec3 getRobotGlobalPos( int indexRobot, int indexScene );
	static NxVec3 getBallGlobalPos( int indexScene );
	static NxMat33 getRobotGlobalOrientation( int indexRobot, int indexScene );
	static NxReal getAngle2DFromRobot( int indexRobot, int indexScene );

	static void controlRobot( NxReal* wheelsSpeeds, NxReal dribblerSpeed, int indexScene, NxI32 indexRobot );

	static void addLocalTorqueDribbler(NxReal torqueX);

	//Metodos que devem estar no modulo inteligencia
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