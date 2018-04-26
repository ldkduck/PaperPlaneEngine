#ifndef GLAPPLICATION_H
#define GLAPPLICATION_H



#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "ogldev_math_3d.h"
#include <iostream>
#include "ogldev_pipeline.h"
#include "ogldev_util.h"
#include "ogldev_texture.h"
#include "LightShaderMgr.h"
#include <atlimage.h>
#include "ogldev_callbacks.h"
#include "Setup.h"
#include "BaseShaderMgr.h"
#include "Mesh.h"
#include "ogldev_shadow_map_fbo.h"
#include "ShadowMapShaderMgr.h"
#include "Skybox.h"
#include "GameObject.h"
#include "LightSystem.h"
#include "ScreenQuadShaderMgr.h"
#include "screen_fbo.h"
#include "ScreenEffect_Bloom.h"

#pragma comment(lib, "glew32.lib")

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600


class GLApplication :public ICallbacks
{
public:
	GLApplication();
	~GLApplication();
	

	bool Init();
	void Run();
	virtual void RenderSceneCB();
	virtual void KeyboardCB_App(OGLDEV_KEY OgldevKey, OGLDEV_KEY_STATE OgldevKeyState = OGLDEV_KEY_STATE_PRESS) ;
	virtual void KeyboardCBUp_App(OGLDEV_KEY OgldevKey, OGLDEV_KEY_STATE OgldevKeyState = OGLDEV_KEY_STATE_RELEASE) ;
	virtual void PassiveMouseCB(int x, int y);

private:
	//渲染器的一些逻辑处理
	void LogicUpdate();

	//最后渲染到屏幕mesh
	void RenderScreenQuad();



	//天空盒对象
	Skybox* m_pSkybox;

	//光照渲染着色器
	LightShaderMgr* m_pEffect;
	//阴影渲染着色器
	ShadowMapShaderMgr* m_shadowMapShader;
	//最后用来渲染显示mesh的着色器
	ScreenQuadShaderMgr* m_screenQuadShader;
	
	//bloom特效脚本
	ScreenEffect_Bloom* m_screenEft_Bloom;

	//最后用来装载渲染数据的FBO
	ScreenFBO* m_screenFBO;

	//场景内mesh
	Mesh* m_pMesh;
	Mesh* m_pMesh_terrian;
	
	//最后渲染用的mesh
	Mesh* m_pMesh_screenQuad;

	//摄像机
	Camera* m_pGameCamera;
	Camera* m_pShadowCamera;

	//灯光对象
	LightSystem* m_lightSystem;
	


	//摄像机透视投影参数
	PersProjInfo m_persProjInfo;

	PersProjInfo m_ShadowProjInfo;

	OrthoProjInfo m_DirecShadowProjInfo;

	
	
	Texture* m_pTexture1;
	Texture* m_pTexture2;
	Texture* m_pTexture3;
	//MATERIALS
	Material_DK* m_pMat_plane;
	Material_DK* m_pMat_terrian;

	//gameobjects
	GameObject* m_pPlane;
	GameObject* m_pTerrian;
	

};

#endif // !GLAPPLICATION_H