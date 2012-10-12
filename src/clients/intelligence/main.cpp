#include <QtCore/QCoreApplication>
#include <iostream>
#include "Intelligence.h"
#include "config.h"

#if defined(WIN32) && defined(_DEBUG)
     #define _CRTDBG_MAP_ALLOC
     #include <stdlib.h>
     #include <crtdbg.h>
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
#endif

using namespace std;

static Intelligence* intel;
//static int winWidth, winHeight;
static QCoreApplication* app;

#ifdef SOCCER_DEBUG
#include "minimax.h"
#include "Minmax2.h"

using namespace LibIntelligence::Plays;

void reshape(int wid, int ht)
{
	//winWidth = wid;
	//winHeight = ht;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-soccer_env()->hfield_w, soccer_env()->hfield_w, 
		-soccer_env()->hfield_h, soccer_env()->hfield_h, -1.f, 1.f);
	glMatrixMode(GL_MODELVIEW);
}

void idleFunc(void)
{
	QCoreApplication::processEvents();
	((Minmax2 *)intel->play["minimax2"])->drawOpenGL();
}
#endif

int main(int argc, char *argv[])
{
#if defined(_MSC_VER) && defined(_DEBUG)
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	app = new QCoreApplication(argc, argv);

	cout << "Modulo Inteligencia" << endl;

	intel = new Intelligence(app);

#ifdef SOCCER_DEBUG
	glutInit(&argc, argv);
	glutInitWindowSize(1200, 400);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
	(void)glutCreateWindow("Soccer");
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(idleFunc);
	glutIdleFunc(idleFunc);
	glutMainLoop();
#else
	app->exec();
#endif

	//Intelligence intel(&app);

	return 0;
}
