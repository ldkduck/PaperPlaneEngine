#include "Setup.h"


#ifndef WIN32
#include <unistd.h>
#endif
#include <stdio.h>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glut.h"
#include "ogldev_util.h"


#pragma comment(lib, "glew32.lib")

// Points to the object implementing the ICallbacks interface which was delivered to
// GLUTBackendRun(). All events are forwarded to this object.
static ICallbacks* s_pCallbacks = NULL;

static bool sWithDepth = false;
static bool sWithStencil = false;

OGLDEV_KEY GLUTKeyToOGLDEVKey(uint Key)
{
	switch (Key) {

	case GLUT_KEY_F1:
		return OGLDEV_KEY_F1;
	case GLUT_KEY_F2:
		return OGLDEV_KEY_F2;
	case GLUT_KEY_F3:
		return OGLDEV_KEY_F3;
	case GLUT_KEY_F4:
		return OGLDEV_KEY_F4;
	case GLUT_KEY_F5:
		return OGLDEV_KEY_F5;
	case GLUT_KEY_F6:
		return OGLDEV_KEY_F6;
	case GLUT_KEY_F7:
		return OGLDEV_KEY_F7;
	case GLUT_KEY_F8:
		return OGLDEV_KEY_F8;
	case GLUT_KEY_F9:
		return OGLDEV_KEY_F9;
	case GLUT_KEY_F10:
		return OGLDEV_KEY_F10;
	case GLUT_KEY_F11:
		return OGLDEV_KEY_F11;
	case GLUT_KEY_F12:
		return OGLDEV_KEY_F12;
	case GLUT_KEY_LEFT:
		return OGLDEV_KEY_LEFT;
	case GLUT_KEY_UP:
		return OGLDEV_KEY_UP;
	case GLUT_KEY_RIGHT:
		return OGLDEV_KEY_RIGHT;
	case GLUT_KEY_DOWN:
		return OGLDEV_KEY_DOWN;
	case GLUT_KEY_PAGE_UP:
		return OGLDEV_KEY_PAGE_UP;
	case GLUT_KEY_PAGE_DOWN:
		return OGLDEV_KEY_PAGE_DOWN;
	case GLUT_KEY_HOME:
		return OGLDEV_KEY_HOME;
	case GLUT_KEY_END:
		return OGLDEV_KEY_END;
	case GLUT_KEY_INSERT:
		return OGLDEV_KEY_INSERT;

	default:
		OGLDEV_ERROR0("Unimplemented GLUT key");
		exit(1);
	}

	return OGLDEV_KEY_UNDEFINED;
}

static OGLDEV_MOUSE GLUTMouseToOGLDEVMouse(uint Button)
{
	switch (Button) {
	case GLUT_LEFT_BUTTON:
		return OGLDEV_MOUSE_BUTTON_LEFT;
	case GLUT_RIGHT_BUTTON:
		return OGLDEV_MOUSE_BUTTON_LEFT;
	case GLUT_MIDDLE_BUTTON:
		return OGLDEV_MOUSE_BUTTON_LEFT;
	default:
		OGLDEV_ERROR0("Unimplemented GLUT mouse button");
	}

	return OGLDEV_MOUSE_UNDEFINED;
}

static void SpecialKeyboardCB(int Key, int x, int y)
{
	OGLDEV_KEY OgldevKey = GLUTKeyToOGLDEVKey(Key);
	s_pCallbacks->KeyboardCB_App(OgldevKey);
}

static void SpecialKeyboardUpCB(int Key, int x, int y)
{
	OGLDEV_KEY OgldevKey = GLUTKeyToOGLDEVKey(Key);
	s_pCallbacks->KeyboardCBUp_App(OgldevKey);
}


static void KeyboardCBUp(unsigned char Key, int x, int y)
{
	if (
		((Key >= '+') && (Key <= '9')) ||
		((Key >= 'A') && (Key <= 'Z')) ||
		((Key >= 'a') && (Key <= 'z'))
		) {
		OGLDEV_KEY OgldevKey = (OGLDEV_KEY)Key;
		s_pCallbacks->KeyboardCBUp_App(OgldevKey);
	}
	else {
		//printf("%d\n", Key);
		//OGLDEV_ERROR0("Unimplemented GLUT key");
	}
}

static void KeyboardCB(unsigned char Key, int x, int y)
{
	if (
		((Key >= '+') && (Key <= '9')) ||
		((Key >= 'A') && (Key <= 'Z')) ||
		((Key >= 'a') && (Key <= 'z'))
		) {
		OGLDEV_KEY OgldevKey = (OGLDEV_KEY)Key;
		s_pCallbacks->KeyboardCB_App(OgldevKey);
	}
	else {
		printf("%d\n", Key);
		OGLDEV_ERROR0("Unimplemented GLUT key");
	}

}



static void PassiveMouseCB(int x, int y)
{
	s_pCallbacks->PassiveMouseCB(x, y);
}

static void RenderSceneCB()
{
	s_pCallbacks->RenderSceneCB();
}

static void IdleCB()
{
	s_pCallbacks->RenderSceneCB();
}


static void MouseCB(int Button, int State, int x, int y)
{
	OGLDEV_MOUSE OgldevMouse = GLUTMouseToOGLDEVMouse(Button);
	OGLDEV_KEY_STATE OgldevKeyState = (State == GLUT_DOWN) ? OGLDEV_KEY_STATE_PRESS : OGLDEV_KEY_STATE_RELEASE;

	s_pCallbacks->MouseCB(OgldevMouse, OgldevKeyState, x, y);
}

void InitCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(IdleCB);
	glutSpecialFunc(SpecialKeyboardCB);
	glutSpecialUpFunc(SpecialKeyboardUpCB);
	glutPassiveMotionFunc(PassiveMouseCB);
	glutKeyboardFunc(KeyboardCB);
	glutKeyboardUpFunc(KeyboardCBUp);
	glutMouseFunc(MouseCB);
}



void GLUTSetupRun(ICallbacks* pCallbacks)
{
	if (!pCallbacks) {
		fprintf(stderr, "%s : callbacks not specified!\n", __FUNCTION__);
		return;
	}

	//渲染基本参数
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	//if (sWithDepth) {
	printf("enable depth test");
		glEnable(GL_DEPTH_TEST);
	//}

	s_pCallbacks = pCallbacks;
	
	//初始化回调函数
	InitCallbacks();
	glutMainLoop();
}


void GLUTSetupSwapBuffers()
{
	glutSwapBuffers();
}

void GLUTSetupLeaveMainLoop()
{
	//glutLeaveMainLoop();
}