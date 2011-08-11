#pragma once


#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Simulation.h"
#include "DrawObjects.h"
#ifdef __PPCGEKKO__
#include "GLFontRenderer.h"
printf("__PPCGEKKO__");
#endif
#include "GLFontRenderer.h"
#include "DebugRenderer.h"
//#include "PerfRenderer.h"

class SimulationView
{
private:
	//static FILE * outputfile;
	static bool gravar;
	static int count;
	static bool keyDown[256];
	static int gMainHandle;
	static NxVec3 gEye;
	static NxVec3 Dir;
	static NxVec3 Up;
	static NxVec3 N;
	static GLdouble zNear;
	static GLdouble zFar;
	static int mx;
	static int my;
	static DebugRenderer gDebugRenderer;
	//static PerfRenderer    gPrefRenderer;
private:
	static void appKey(unsigned char key, bool down);
	static void callback_keyUp(unsigned char c, int x, int y);
	static void callback_key(unsigned char c, int x, int y);
	static void ArrowKeyCallback(int key, int x, int y);
	static void MouseCallback(int button, int state, int x, int y);
	static void MotionCallback(int x, int y);
	static void RenderCallback();
	static void RenderSimulationCallback();
	static void setupCamera();
	static void ReshapeCallback(int width, int height);
	static void IdleCallback();
	static NX_BOOL LoadScene(const char *pFilename,NXU::NXU_FileType type);
	static void SaveScene(const char *pFilename);
	static bool FileExistTestSimple(const char *fname);
	static void CSL_Scene();

	friend class Simulation;
public:
	SimulationView(void);
	~SimulationView(void);

	//main loop simulation
	static void mainLoop(int argc, char **argv);
	static void mainSimulationLoop(int argc, char **argv);
};