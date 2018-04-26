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
	//��Ⱦ����һЩ�߼�����
	void LogicUpdate();

	//�����Ⱦ����Ļmesh
	void RenderScreenQuad();



	//��պж���
	Skybox* m_pSkybox;

	//������Ⱦ��ɫ��
	LightShaderMgr* m_pEffect;
	//��Ӱ��Ⱦ��ɫ��
	ShadowMapShaderMgr* m_shadowMapShader;
	//���������Ⱦ��ʾmesh����ɫ��
	ScreenQuadShaderMgr* m_screenQuadShader;
	
	//bloom��Ч�ű�
	ScreenEffect_Bloom* m_screenEft_Bloom;

	//�������װ����Ⱦ���ݵ�FBO
	ScreenFBO* m_screenFBO;

	//������mesh
	Mesh* m_pMesh;
	Mesh* m_pMesh_terrian;
	
	//�����Ⱦ�õ�mesh
	Mesh* m_pMesh_screenQuad;

	//�����
	Camera* m_pGameCamera;
	Camera* m_pShadowCamera;

	//�ƹ����
	LightSystem* m_lightSystem;
	


	//�����͸��ͶӰ����
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