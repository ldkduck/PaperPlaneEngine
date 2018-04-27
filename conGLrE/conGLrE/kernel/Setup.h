#ifndef SETUP_H
#define SETUP_H 

#include "ogldev_types.h"
#include "ogldev_callbacks.h"


void GLUTSetupRun(ICallbacks* pCallbacks);

void GLUTSetupSwapBuffers();

void GLUTSetupLeaveMainLoop();


void InitCallbacks();

OGLDEV_KEY GLUKeyToOGLDEVKey(uint Key);



#endif // ! SETUP_H
