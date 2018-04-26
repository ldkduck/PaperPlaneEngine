#include <limits.h>
#include <string.h>

#include "SkyboxShaderMgr.h"
#include "ogldev_util.h"

SkyboxShaderMgr::SkyboxShaderMgr()
{

}

bool SkyboxShaderMgr::Init()
{
	if (!ShaderManager::Init())
	{
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "skybox.vs"))
	{
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "skybox.fs"))
	{
		return false;
	}

	if (!Finalize())
	{
		return false;
	}

	m_WVPLocation = GetUniformLocation("gWVP");
	m_textureLocation = GetUniformLocation("gCubemapTexture");

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_textureLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}

void SkyboxShaderMgr::SetWVP(const Matrix4f& WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}


void SkyboxShaderMgr::SetTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_textureLocation, TextureUnit);
}
