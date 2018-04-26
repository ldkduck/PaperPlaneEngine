#include "Shader_Bloom_Add.h"
#include "ogldev_pipeline.h"

ShaderBloomAdd::ShaderBloomAdd()
{

}

//每一套shader有不同的参数，在继承基类加载函数的基础上，
//子类负责确定具体shader有哪些参数，先把接口找到。
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

//该函数用于在渲染之前设定必要的更新数据
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


