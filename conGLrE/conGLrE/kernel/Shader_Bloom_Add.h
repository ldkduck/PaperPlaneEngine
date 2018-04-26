#ifndef SHADER_BLOOM_ADD_H
#define SHADER_BLOOM_ADD_H

#include "ogldev_math_3d.h"
#include "ShaderManager.h"
#include "Material.h"



class ShaderBloomAdd : public ShaderManager
{
public:

	ShaderBloomAdd();

	virtual bool Init();
	virtual void UpdateRenderInfo(Transform trans, Camera* cam, LightSystem* light);

	bool BindShaderAttrib();

	void SetWVP(const Matrix4f& WVP);
	void SetSrcTexture(unsigned int TextureUnit);
	void SetBlurTexture(unsigned int TextureUnit);
	void SetBool(int b);

private:

	GLuint m_WVPLocation;
	GLuint m_srctextureLocation;
	GLuint m_blurtextureLocation;



};




#endif // !SCREEN_QUAD_SHADER_MGR_H


