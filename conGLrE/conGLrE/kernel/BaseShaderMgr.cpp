#include "BaseShaderMgr.h"

BaseShaderMgr::BaseShaderMgr()
{

}

//ÿһ��shader�в�ͬ�Ĳ������ڼ̳л�����غ����Ļ����ϣ�
//���ฺ��ȷ������shader����Щ�������Ȱѽӿ��ҵ���
bool BaseShaderMgr::Init()
{
	if (!ShaderManager::Init()) {
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "shader.vs"))
	{
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "shader.fs"))
	{
		return false;
	}

	if (!Finalize())
	{
		return false;
	}

	//��ȡshader������id
	//WVP����ID
	m_WVPLocation = GetUniformLocation("gWVP");

	//����ID
	m_samplerLocation = GetUniformLocation("gSampler");

	return true;

}

//���Ϊ����ӿڶ��ϳ����ڱ����ṩ�ӿ�
void BaseShaderMgr::SetWVP(const Matrix4f& WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);

}

void BaseShaderMgr::SetTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_samplerLocation, TextureUnit);
}


