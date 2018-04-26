#include "ScreenQuadShaderMgr.h"
#include "ogldev_pipeline.h"

ScreenQuadShaderMgr::ScreenQuadShaderMgr()
{

}

//ÿһ��shader�в�ͬ�Ĳ������ڼ̳л�����غ����Ļ����ϣ�
//���ฺ��ȷ������shader����Щ�������Ȱѽӿ��ҵ���
bool ScreenQuadShaderMgr::Init()
{
	if (!ShaderManager::Init()) {
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "shader/screenquad.vs"))
	{
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "shader/screenquad.fs"))
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

bool ScreenQuadShaderMgr::BindShaderAttrib()
{
	m_textureLocation = GetUniformLocation("hdrBuffer");

	return false;

}

//�ú�����������Ⱦ֮ǰ�趨��Ҫ�ĸ�������
void ScreenQuadShaderMgr::UpdateRenderInfo(Transform trans, Camera* cam, LightSystem* light)
{

}

void ScreenQuadShaderMgr::SetTextureUnit(uint TextureUnit)
{
	glUniform1i(m_textureLocation, TextureUnit);
}


