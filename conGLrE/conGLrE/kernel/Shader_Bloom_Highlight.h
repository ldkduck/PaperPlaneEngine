#ifndef SHADER_BLOOM_HIGHLIGHT_H
#define SHADER_BLOOM_HIGHLIGHT_H

#include "ogldev_math_3d.h"
#include "ShaderManager.h"
#include "Material.h"



class ShaderBloomHighlight : public ShaderManager
{
public:
	
	ShaderBloomHighlight();

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


