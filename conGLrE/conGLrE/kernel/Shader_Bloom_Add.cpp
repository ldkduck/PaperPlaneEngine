#include "Shader_Bloom_Add.h"
#include "ogldev_pipeline.h"

ShaderBloomAdd::ShaderBloomAdd()
{

}

//ÿһ��shader�в�ͬ�Ĳ������ڼ̳л�����غ����Ļ����ϣ�
//���ฺ��ȷ������shader����Щ�������Ȱѽӿ��ҵ���
bool ShaderBloomAdd::Init()
{
	if (!ShaderManager::Init()) {
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "shader/shader_bloom_add.vs"))
	{
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "shader/shader_bloom_add.fs"))
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

bool ShaderBloomAdd::BindShaderAttrib()
{
	m_srctextureLocation = GetUniformLocation("gSrcSampler");
	m_blurtextureLocation = GetUniformLocation("gBlurSampler");
	return false;

}

//�ú�����������Ⱦ֮ǰ�趨��Ҫ�ĸ�������
void ShaderBloomAdd::UpdateRenderInfo(Transform trans, Camera* cam, LightSystem* light)
{

}

void ShaderBloomAdd::SetSrcTexture(unsigned int TextureUnit)
{
	glUniform1i(m_srctextureLocation, TextureUnit);
}
void ShaderBloomAdd::SetBlurTexture(unsigned int TextureUnit)
{
	glUniform1i(m_blurtextureLocation, TextureUnit);
}


