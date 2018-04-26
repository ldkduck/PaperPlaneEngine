#include "ogldev_util.h"
#include "ShadowMapShaderMgr.h"
#include "ogldev_pipeline.h"


ShadowMapShaderMgr::ShadowMapShaderMgr()
{

}

bool ShadowMapShaderMgr::Init()
{
	if (!ShaderManager::Init()) {
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "shadow_map.vs"))
	{
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "shadow_map.fs"))
	{
		return false;
	}

	if (!Finalize())
	{
		return false;
	}

	m_WVPLocation = GetUniformLocation("gWVP");
	//m_WVOPLocation = GetUniformLocation("g")
	m_textureLocation = GetUniformLocation("gShadowMap");
	

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_textureLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}

void ShadowMapShaderMgr::SetWVP(const Matrix4f& WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}

void ShadowMapShaderMgr::SetWVOP(const Matrix4f& WVOP)
{
	glUniformMatrix4fv(m_WVOPLocation, 1, GL_TRUE, (const GLfloat*)WVOP.m);
}

void ShadowMapShaderMgr::SetTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_textureLocation, TextureUnit);
}


//该函数用于在渲染之前设定必要的更新数据
void ShadowMapShaderMgr::UpdateRenderInfo(Transform trans, Camera* cam, LightSystem* light)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	//启用当前着色器
	Enable();
	//设定transform
	Pipeline p;
	p.Scale(trans.GetScale().x, trans.GetScale().y, trans.GetScale().z);
	p.WorldPos(trans.GetPosition().x, trans.GetPosition().y, trans.GetPosition().z);
	p.Rotate(trans.GetRotation().x, trans.GetRotation().y, trans.GetRotation().z);

	p.SetCamera(Vector3f(light->m_directionalLight.Direction.x * -10, light->m_directionalLight.Direction.y * -10, light->m_directionalLight.Direction.z * -10), light->m_directionalLight.Direction, Vector3f(0.0f, 1.0f, 0.0f));
	p.SetOrthographicProj(light->m_DirecShadowProjInfo);
	SetWVP(p.GetWVOrthoPTrans());
}