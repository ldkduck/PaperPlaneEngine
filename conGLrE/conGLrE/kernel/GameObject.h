#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "LightSystem.h"
class GameObject
{
public:
	GameObject();
	~GameObject();
	void Init(Mesh* mesh);
	void ShadowPreRender(Camera* cam, LightSystem* light);
	void Render(Camera* cam,LightSystem* lightSys);
	void SetMaterial(Material_DK* material);
	void SetMesh(Mesh* mesh);
	Mesh* GetMesh();
	Transform* GetTransform();

private:
	Material_DK* m_pMaterial;
	Mesh* m_pMesh;
	Transform m_pTransform;

};



#endif // !GAME_OBJECT_H

