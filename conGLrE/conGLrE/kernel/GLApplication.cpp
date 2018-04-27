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
#include "LightShaderMgr.h"
#include "mesh.h"


#pragma comment(lib, "glew32.lib")

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 800

GLuint scaleFBO;
GLuint scaleMap;

	GLApplication::GLApplication()
	{
		m_pGameCamera = NULL;
		m_pShadowCamera = NULL;
		m_pTexture1 = NULL;
		m_pTexture2 = NULL;
		m_pEffect = NULL;
		
		//初始化投影参数
		m_persProjInfo.FOV = 60.0f;
		m_persProjInfo.Height = WINDOW_HEIGHT;
		m_persProjInfo.Width = WINDOW_WIDTH;
		m_persProjInfo.zNear = 0.1f;
		m_persProjInfo.zFar = 100.0f;

		glGenFramebuffers(1, &scaleFBO);
		glGenTextures(1, &scaleMap);
		glBindTexture(GL_TEXTURE_2D, scaleMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 1280/4, 800/4, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, scaleFBO);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, scaleMap, 0);
	}

	GLApplication::~GLApplication()
	{
		delete m_pEffect;
		delete m_pGameCamera;
		delete m_pTexture1;
		delete m_pTexture2;
		delete m_pMesh;
		delete m_pMesh_terrian;
	}

	bool GLApplication::Init()
	{
		//初始化摄像机
		m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);
		m_pGameCamera->SetProjInfo(m_persProjInfo);
		

		//纹理对象初始化
		m_pTexture1 = new Texture(GL_TEXTURE_2D, "Resource/Small Passenger Plane Diffuse.jpg");
		m_pTexture3 = new Texture(GL_TEXTURE_2D, "Resource/Small Passenger Plane Normal.jpg");
		m_pTexture2 = new Texture(GL_TEXTURE_2D, "Resource/mesh.bmp");
		if (!m_pTexture1->LoadImageBMP()) {
			return false;
		}
		if (!m_pTexture2->LoadImageBMP()) {
			return false;
		}
		if (!m_pTexture3->LoadImageBMP()) {
			return false;
		}

		//初始化渲染用mesh，后来得有个mesh类专门管理所有的mesh
		m_pMesh = new Mesh();
		m_pMesh->LoadMesh("Resource/plane_2.obj");
		m_pMesh_terrian = new Mesh();
		m_pMesh_terrian->LoadMesh("Resource/quad.obj");

		m_pMesh_screenQuad = new Mesh();
		m_pMesh_screenQuad->LoadMesh("Resource/screencube.obj");
		
		//初始化模型shader
		//光照的渲染器
		m_lightSystem = new LightSystem();
		
		m_pEffect = new LightShaderMgr();
		if (!m_pEffect->Init())
		{

			return false;
		}
		//阴影贴图渲染器
		m_shadowMapShader = new ShadowMapShaderMgr();
		if (!m_shadowMapShader->Init())
		{
			return false;
		}

		m_screenQuadShader = new ScreenQuadShaderMgr();
		if (!m_screenQuadShader->Init())
		{
			return false;
		}


		m_screenFBO = new ScreenFBO();
		m_screenFBO->Init(WINDOW_WIDTH,WINDOW_HEIGHT);

		m_screenEft_Bloom = new ScreenEffect_Bloom(m_pMesh_screenQuad);
		m_screenEft_Bloom->Init(WINDOW_WIDTH, WINDOW_HEIGHT);

		//初始化天空盒
		m_pSkybox = new Skybox(m_pGameCamera, m_persProjInfo);
		if (!m_pSkybox->Init("Resource/Skybox/",
			"Resource/Skybox/DawnDusk_front.jpg",
			"Resource/Skybox/DawnDusk_back.jpg",
			"Resource/Skybox/DawnDusk_down.jpg",
			"Resource/Skybox/DawnDusk_up.jpg",
			"Resource/Skybox/DawnDusk_right.jpg",
			"Resource/Skybox/DawnDusk_left.jpg")) {
			
			return false;
		}

		//Materials initialization
		m_pMat_plane = new Material_DK();
		m_pMat_plane->SetShader(m_pEffect,m_shadowMapShader);
		m_pMat_plane->Init(m_pTexture1,m_pTexture3,Vector2f(1.0f,1.0f));
		/*m_pMat_terrian = new Material_DK();
		m_pMat_terrian->SetShader(m_pEffect, m_shadowMapShader);
		m_pMat_terrian->Init(m_pTexture2, Vector2f(10.0f, 10.0f));*/

		
		//基础的东西都已经初始化完毕，现在开始整合到gameobject对象中
		m_pPlane = new GameObject();
		m_pPlane->GetTransform()->SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
		m_pPlane->GetTransform()->SetRotation(Vector3f(0.0f, 90.0f, 0.0f));
		m_pPlane->GetTransform()->SetScale(Vector3f(0.05f, 0.05f, 0.05f));
		m_pPlane->SetMesh(m_pMesh);
		m_pPlane->SetMaterial(m_pMat_plane);

		
		m_pTerrian = new GameObject();
		m_pTerrian->GetTransform()->SetPosition(Vector3f(0.0f, -2.0f, 0.0f));
		m_pTerrian->GetTransform()->SetRotation(Vector3f(0.0f, 0.0f, 0.0f));
		m_pTerrian->GetTransform()->SetScale(Vector3f(1.0f, 1.0f, 1.0f));
		m_pTerrian->SetMesh(m_pMesh_terrian);
		m_pTerrian->SetMaterial(m_pMat_terrian);


		return true;
	}


	int curTime;
	int preTime;

	float _rotAccel = 0.05f;
	float _rotSpeed = 0;
	float _rot = 0;
	bool isleftAccel = false;
	bool isrightAccel = false;

	void GLApplication::LogicUpdate()
	{
		if (isleftAccel) {
			_rotSpeed += _rotAccel;
		}
		if (isrightAccel) {
			_rotSpeed -= _rotAccel;
		}

		_rotSpeed *= 0.95f;
		_rot += _rotSpeed;
		m_pPlane->GetTransform()->SetRotation(Vector3f(0, 75.0f, _rot));

	}

	

	void GLApplication::RenderSceneCB()
	{
		//显示帧速
		/*SYSTEMTIME sys;
		GetLocalTime(&sys);
		curTime = sys.wMilliseconds;
		printf("%.2f\n", 1000.0f/(curTime-preTime));
		preTime = curTime;*/
		//摄像机渲染，主要应该是处理相机移动相关。
		//m_scale += 0.2f;

		m_pGameCamera->OnEnter();
		
		//逻辑处理
		LogicUpdate();

		//阴影纹理渲染区域
		glClear(GL_DEPTH_BUFFER_BIT);
		m_pPlane->ShadowPreRender(m_pGameCamera, m_lightSystem);
		
		//mesh渲染区域
		m_screenFBO->BindForWriting();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_pPlane->Render(m_pGameCamera, m_lightSystem);
		
		//skybox渲染
		m_pSkybox->Render();

		
		
		m_screenEft_Bloom->Process(m_screenFBO);
		
		//直接将预缓冲区内的内容blit到系统帧缓冲中，并渲染到系统帧缓冲
		m_screenFBO->BindForReading();
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			GL_COLOR_BUFFER_BIT, GL_LINEAR);
		

		glutSwapBuffers();
	}


	void GLApplication::KeyboardCB_App(OGLDEV_KEY OgldevKey, OGLDEV_KEY_STATE OgldevKeyState)
	{

		if (OgldevKey == OGLDEV_KEY_a)
		{
			m_pGameCamera->SetLeft(true);
		}
		if (OgldevKey == OGLDEV_KEY_d)
		{
			m_pGameCamera->SetRight(true);
		}
		if (OgldevKey == OGLDEV_KEY_w)
		{
			m_pGameCamera->SetForward(true);
		}
		if (OgldevKey == OGLDEV_KEY_s)
		{
			m_pGameCamera->SetBackward(true);
		}
		if (OgldevKey == OGLDEV_KEY_LEFT)
		{
			isleftAccel = true;
		}
		if (OgldevKey == OGLDEV_KEY_RIGHT)
		{
			isrightAccel = true;
		}

		if (OgldevKey == OGLDEV_KEY_Z || OgldevKey == OGLDEV_KEY_z)
		{
			m_pGameCamera->ActiveMouseRotation(true);
		}

	}


	void GLApplication::KeyboardCBUp_App(OGLDEV_KEY OgldevKey, OGLDEV_KEY_STATE OgldevKeyState)
	{
		
		if (OgldevKey == OGLDEV_KEY_a)
		{
			m_pGameCamera->SetLeft(false);
		}
		if (OgldevKey == OGLDEV_KEY_d)
		{
			m_pGameCamera->SetRight(false);
		}
		if (OgldevKey == OGLDEV_KEY_w)
		{
			m_pGameCamera->SetForward(false);
		}
		if (OgldevKey == OGLDEV_KEY_s)
		{
			m_pGameCamera->SetBackward(false);
		}
		if (OgldevKey == OGLDEV_KEY_LEFT)
		{
			isleftAccel = false;
		}
		if (OgldevKey == OGLDEV_KEY_RIGHT)
		{
			isrightAccel = false;
		}

		if (OgldevKey == OGLDEV_KEY_Z || OgldevKey == OGLDEV_KEY_z) 
		{
			m_pGameCamera->ActiveMouseRotation(false);
		}

		if (OgldevKey == OGLDEV_KEY_Q || OgldevKey == OGLDEV_KEY_q)
		{
			exit(0);
		}
	}

	//鼠标移动响应
	void GLApplication::PassiveMouseCB(int x, int y)
	{
		m_pGameCamera->OnMouse(x, y);
	}


	void GLApplication::Run()
	{
		//这个函数主要是渲染前期的一些参数调节，比如是否有cull，depth开不开启，以及激活循环回调函数
		GLUTSetupRun(this);
	}

	//void DSGeometryPass()
	//{
	//	m_DSGeomPassTech.Enable();
	//	m_gbuffer.BindForDrawing();
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	Pipeline p;
	//	p.Scale(0.1f, 0.1f, 0.1f);
	//	p.Rotate(0.0f, 0.0f, 0.0f);
	//	p.WorldPos(0.0f, 0.0f, 0.0f);
	//	p.SetCamera(camera.getInfo);
	//	p.SetPerspectivePorj(persProj);

	//	m_DSGeomPassTech.SetWVP(p.GetWVPTrans());
	//	m_DSGeomPassTech.SetWorldMatrix(p.GetWorldTrans());
	//	//按道理来说，这次render结束以后，GBUFFER里面的所有纹理都应该已经被填充了内容了
	//	m_mesh.Render();
	//}

	//void DSLightPass()
	//{
	//	//接下来的pass实际上就开始要读取gbuffer里面的内容，并分别将内容贴到  屏幕缓存的四部分。
	//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	m_gbuffer.BindForReading();
	//	GLsizei halfWidth = (GLsizei)(window_width / 2.0f);
	//	GLsizei halfHeight = (GLsizei)(window_height) / 2.0f);
	//	m_gbuffer.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	//	glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, halfWidth, halfHeight,GL_COLOR_BUFFER_BIT,GL_LINEAR);
	//	m_gbuffer.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	//	glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, halfWidth, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	//	m_gbuffer.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
	//	glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, halfwidth, halfheight, WINDOW_WIDTH, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	//	m_gbuffer.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_TEXCOORD);
	//	glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, halfwidth, halfheight, WINDOW_WIDTH, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	//	//然后关键还是看shader里面是怎么写的

	//
	//}

	//{
	//	(geometry_pass.vs)
	//		#version 330
	//		layout(location = 0) in vec3 Position;
	//	layout(location = 1)in vec2 Texcoord;
	//	layout(location = 2)in vec3 Normal;

	//	uniform mat4 gWVP;
	//	uniform mat4 gWorld;
	//	out vec2 Texcoord0;
	//	out vec3 normal0;
	//	out vec3 WorldPos0;

	//	void main()
	//	{
	//		gl_Position = gWVP * vec4(Position, 1.0);
	//		TexCoord0 = Texcoord;
	//		Normal0 = (gWorld * vec4(Normal, 0.0)).xyz;
	//		worldPos0 = (gWrold * vec4(Position, 1.0)).xyz;
	//	}
	//}

	//{
	//	(geometry_pass.fs)
	//		#version 330
	//		in vec2 Texcoord0;
	//	in vec3 Normal0;
	//	in vec3 WorldPos0;
	//	layout(location = 0)out vec3 WorldPosOut;
	//	layout(location = 1)out vec3 DiffuseOut;
	//	layout(location = 2)out vec3 NormalOut;
	//	layout(location = 3)out vec3 TexcoordOut;

	//	uniform sampler2D gColorMap;
	//	void Main()
	//	{
	//		WorldPosOut = WorldPos0;
	//		DiffuseOut = texture(gColorMap, TexCoord0).xyz;
	//		normalOut = normalize(Normal0);
	//		TexCoordOut = vec3(Texcoord0, 0);

	//	}

	//}






