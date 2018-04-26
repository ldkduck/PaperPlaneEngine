#ifndef SCREEN_QUAD_SHADER_MGR_H
#define SCREEN_QUAD_SHADER_MGR_H


#include "ogldev_math_3d.h"
#include "ShaderManager.h"
#include "Material.h"



class ScreenQuadShaderMgr : public ShaderManager
{
public:

	ScreenQuadShaderMgr();

	virtual bool Init();
	virtual void UpdateRenderInfo(Transform trans, Camera* cam, LightSystem* light);

	bool BindShaderAttrib();

	void SetWVP(const Matrix4f& WVP);
	void SetTextureUnit(unsigned int TextureUnit);

private:
	GLuint m_textureScaleLocation;

	GLuint m_WVPLocation;
	GLuint m_textureLocation;



};




#endif // !SCREEN_QUAD_SHADER_MGR_H


