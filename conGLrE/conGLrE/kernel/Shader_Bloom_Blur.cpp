#include "Shader_Bloom_Blur.h"
#include "ogldev_pipeline.h"

ShaderBloomBlur::ShaderBloomBlur()
{

}

//ÿһ��shader�в�ͬ�Ĳ������ڼ̳л�����غ����Ļ����ϣ�
//���ฺ��ȷ������shader����Щ�������Ȱѽӿ��ҵ���
bool ShaderBloomBlur::Init()
{
	if (!ShaderManager::Init()) {
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "shader/shader_bloom_blur.vs"))
	{
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "shader/shader_bloom_blur.fs"))
	{
		return false;
	}

	if (!Finalize())
	{
		return false;
	}

	BindShaderAttrib();


	return true;

}

bool ShaderBloomBlur::BindShaderAttrib()
{
	m_textureLocation = GetUniformLocation("gSampler");
	m_horizon = GetUniformLocation("horizontal");
	return false;

}

//�ú�����������Ⱦ֮ǰ�趨��Ҫ�ĸ�������
void ShaderBloomBlur::UpdateRenderInfo(Transform trans, Camera* cam, LightSystem* light)
{

}

void ShaderBloomBlur::SetTextureUnit(uint TextureUnit)
{
	glUniform1i(m_textureLocation, TextureUnit);
}

void ShaderBloomBlur::SetBool(int b)
{
	glUniform1i(m_horizon, b);
}


