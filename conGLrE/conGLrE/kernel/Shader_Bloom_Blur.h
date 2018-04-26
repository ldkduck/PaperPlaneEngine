#ifndef SHADER_BLOOM_BLUR_H
#define SHADER_BLOOM_BLUR_H

#include "ogldev_math_3d.h"
#include "ShaderManager.h"
#include "Material.h"



class ShaderBloomBlur : public ShaderManager
{
public:

	ShaderBloomBlur();

	virtual bool Init();
	virtual void UpdateRenderInfo(Transform trans, Camera* cam, LightSystem* light);

	bool BindShaderAttrib();

	void SetWVP(const Matrix4f& WVP);
	void SetTextureUnit(unsigned int TextureUnit);
	void SetBool(int b);

private:
	GLuint m_textureScaleLocation;

	GLuint m_WVPLocation;
	GLuint m_textureLocation;
	GLuint m_horizon;



};




#endif // !SCREEN_QUAD_SHADER_MGR_H


