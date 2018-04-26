#include "LightSystem.h"
#include "GLApplication.h"

LightSystem::LightSystem()
{
	m_shadowMapFBO = new ShadowMapFBO();
	m_shadowMapFBO->Init(1280, 800);

	//初始化spotlight阴影投影参数
	m_ShadowProjInfo.FOV = 60.0f;
	m_ShadowProjInfo.Height = 800;
	m_ShadowProjInfo.Width = 800;
	m_ShadowProjInfo.zNear = -50.0f;
	m_ShadowProjInfo.zFar = 100.0f;

	//初始化directionallight阴影投影参数
	m_DirecShadowProjInfo.Height = WINDOW_HEIGHT;
	m_DirecShadowProjInfo.Width = WINDOW_WIDTH;
	m_DirecShadowProjInfo.Size = 30.0f;
	m_DirecShadowProjInfo.zNear = 0.1f;
	m_DirecShadowProjInfo.zFar = 100.0f;

	//平行光
	m_directionalLight.AmbientIntensity = 0.1f;
	m_directionalLight.Color = Vector3f(244.0f / 255.0f, 98.0f / 255.0f, 30.0f / 255.0f);
	m_directionalLight.DiffuseIntensity = 4.0f;
	m_directionalLight.Direction = Vector3f(-1.0f, -0.1f, 0.1f);
	//放射光
	m_spotLight.AmbientIntensity = 0.8f;
	m_spotLight.DiffuseIntensity = 2.0f;
	m_spotLight.Color = Vector3f(254.0f / 255.0f, 176.0f / 255.0f, 94.0f / 255.0f);
	m_spotLight.Attenuation.Linear = 0.01f;
	m_spotLight.Position = Vector3f(0.0f, 30.0f, 0.0f);
	m_spotLight.Direction = Vector3f(0.0f, -1.0f, -0.01f);
	m_spotLight.Cutoff = 200.0f;
}