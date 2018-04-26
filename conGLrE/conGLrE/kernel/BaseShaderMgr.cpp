#include "BaseShaderMgr.h"

BaseShaderMgr::BaseShaderMgr()
{

}

//每一套shader有不同的参数，在继承基类加载函数的基础上，
//子类负责确定具体shader有哪些参数，先把接口找到。
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

	//获取shader参数的id
	//WVP矩阵ID
	m_WVPLocation = GetUniformLocation("gWVP");

	//纹理ID
	m_samplerLocation = GetUniformLocation("gSampler");

	return true;

}

//这边为具体接口对上程序内变量提供接口
void BaseShaderMgr::SetWVP(const Matrix4f& WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);

}

void BaseShaderMgr::SetTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_samplerLocation, TextureUnit);
}


