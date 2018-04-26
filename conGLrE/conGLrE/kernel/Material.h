#ifndef  MATERIAL_DK_H
#define  MATERIAL_DK_H


#include "ogldev_math_3d.h"
#include "ogldev_lights_common.h"
#include "ogldev_texture.h"
#include "ogldev_camera.h"

#include "Transform.h"
#include "LightSystem.h"
//#include "LightShaderMgr.h"
#include "ShaderManager.h"
class Material_DK
{
public:

	Material_DK();
	void ShadowPreUpdate(Transform trans,Camera* cam,LightSystem* light);
	void Update(Transform trans, Camera* cam, LightSystem* light);
	bool Init(Texture* diffuseTex, Texture* normalTex, Vector2f scale);
	void SetDiffuseTex(Texture* tex);
	void SetNormalTex(Texture* tex);
	void SetTexScale(Vector2f scale);
	void SetShader(ShaderManager* shader, ShaderManager* shadowShader);
	Vector2f GetTexScale();
private:
	Vector2f m_texScale;
	Texture* m_diffuseTexture;
	Texture* m_normalTexture;
	Vector3f m_basicColor;
	ShaderManager* m_shader;
	ShaderManager* m_shadowShader;
};





#endif // ! MATERIAL_H

