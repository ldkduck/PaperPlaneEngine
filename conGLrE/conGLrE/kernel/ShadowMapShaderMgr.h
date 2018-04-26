
#ifndef SHADOW_MAP_SHADER_MGR_H
#define SHADOW_MAP_SHADER_MGR_H

#include "ShaderManager.h"
#include "ogldev_math_3d.h"

class ShadowMapShaderMgr : public ShaderManager
{
public:

	ShadowMapShaderMgr();

	virtual bool Init();
	virtual void UpdateRenderInfo(Transform trans, Camera* cam, LightSystem* light);

	void SetWVP(const Matrix4f& WVP);
	void SetWVOP(const Matrix4f& WVP);
	void SetTextureUnit(unsigned int TextureUnit);
private:
	GLuint m_WVPLocation;
	GLuint m_WVOPLocation;

	GLuint m_textureLocation;


};


#endif