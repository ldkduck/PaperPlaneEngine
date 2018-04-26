#include "GameObject.h"


GameObject::GameObject()
{
	m_pTransform.Init();
}

Transform* GameObject::GetTransform()
{
	return &m_pTransform;
}

void GameObject::ShadowPreRender(Camera* cam, LightSystem* light)
{
	m_pMaterial->ShadowPreUpdate(m_pTransform, cam, light);
	m_pMesh->Render();
}

void GameObject::Render(Camera* cam,LightSystem* light)
{
	m_pMaterial->Update(m_pTransform,cam,light);
	m_pMesh->Render();
}

void GameObject::SetMaterial(Material_DK* material)
{
	m_pMaterial = material;
}

void GameObject::SetMesh(Mesh* mesh)
{
	m_pMesh = mesh;

}