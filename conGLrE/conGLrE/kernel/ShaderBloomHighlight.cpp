#include "Shader_Bloom_Highlight.h"
#include "ogldev_pipeline.h"

ShaderBloomHighlight::ShaderBloomHighlight()
{

}

//每一套shader有不同的参数，在继承基类加载函数的基础上，
//子类负责确定具体shader有哪些参数，先把接口找到。
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

//该函数用于在渲染之前设定必要的更新数据
void ShaderBloomHighlight::UpdateRenderInfo(Transform trans, Camera* cam, LightSystem* light)
{

}

void ShaderBloomHighlight::SetTextureUnit(uint TextureUnit)
{
	glUniform1i(m_textureLocation, TextureUnit);
}


