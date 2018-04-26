#include "Shader_Bloom_Highlight.h"
#include "ogldev_pipeline.h"

ShaderBloomHighlight::ShaderBloomHighlight()
{

}

//ÿһ��shader�в�ͬ�Ĳ������ڼ̳л�����غ����Ļ����ϣ�
//���ฺ��ȷ������shader����Щ�������Ȱѽӿ��ҵ���
bool ShaderBloomHighlight::Init()
{
	if (!ShaderManager::Init()) {
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "shader/shader_bloom_highlight.vs"))
	{
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "shader/shader_bloom_highlight.fs"))
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

bool ShaderBloomHighlight::BindShaderAttrib()
{
	m_textureLocation = GetUniformLocation("gSampler");

	return false;

}

//�ú�����������Ⱦ֮ǰ�趨��Ҫ�ĸ�������
void ShaderBloomHighlight::UpdateRenderInfo(Transform trans, Camera* cam, LightSystem* light)
{

}

void ShaderBloomHighlight::SetTextureUnit(uint TextureUnit)
{
	glUniform1i(m_textureLocation, TextureUnit);
}


