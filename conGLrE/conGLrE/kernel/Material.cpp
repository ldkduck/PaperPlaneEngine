#include "Material.h"
#include "ogldev_camera.h"

Material_DK::Material_DK()
{
	
}



bool Material_DK::Init(Texture* diffuseTex, Texture* normalTex,Vector2f scale)
{
	m_normalTexture = normalTex;
	m_diffuseTexture = diffuseTex;
	m_texScale = scale;
	return true;
}

void Material_DK::ShadowPreUpdate(Transform trans, Camera* cam, LightSystem* light)
{
	//����Ӱ����󶨵���ȾĿ����
	light->m_shadowMapFBO->BindForWriting();
	m_shadowShader->UpdateRenderInfo(trans, cam, light);
	
	
}

void Material_DK::Update(Transform trans,Camera* cam,LightSystem* light)
{
	//������������󶨵�����Ԫ��
	m_diffuseTexture->Bind(GL_TEXTURE0);
	//����������󶨵�����Ԫ��
	m_normalTexture->Bind(GL_TEXTURE2);
	//����Ӱ����󶨵�����Ԫ��
	light->m_shadowMapFBO->BindForReading(GL_TEXTURE1);
	
	m_shader->UpdateRenderInfo(trans,cam,light);

}

void Material_DK::SetDiffuseTex(Texture* tex)
{
	m_diffuseTexture = tex;
}

void Material_DK::SetNormalTex(Texture* tex)
{
	m_normalTexture = tex;
}

void Material_DK::SetTexScale(Vector2f scale)
{
	m_texScale = scale;

}

Vector2f Material_DK::GetTexScale()
{
	return m_texScale;
}

void Material_DK::SetShader(ShaderManager* shader,ShaderManager* shadowShader)
{
	m_shader = shader;
	m_shadowShader = shadowShader;
}
