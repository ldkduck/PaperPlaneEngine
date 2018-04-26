#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "ogldev_math_3d.h"
#include <iostream>
#include "ogldev_pipeline.h"
#include "ogldev_util.h"
#include "ogldev_texture.h"
#include <atlimage.h>
#include "GLApplication.h"
#include "Setup.h"

#pragma comment(lib, "glew32.lib")

using namespace std;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1280, 800);
	glutInitWindowPosition(500, 100);

	glutCreateWindow("PAPERPLANE ENGINE");

	//InitializeGlutCallbacks();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}
	
	//InitCallbacks();

	GLApplication* pApp = new GLApplication();
	
	if (!pApp->Init()) {
		
		return 1;
	}

	pApp->Run();

	delete pApp;

	return 0;
}
