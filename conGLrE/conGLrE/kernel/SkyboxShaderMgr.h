#ifndef SKYBOX_SHADER_MGR_H
#define SKYBOX_SHADER_MGR_H

#include "ShaderManager.h"
#include "ogldev_math_3d.h"
#include "ogldev_lights_common.h"

class SkyboxShaderMgr : public ShaderManager
{
public:
	
	SkyboxShaderMgr();
	virtual bool Init();
	void SetWVP(const Matrix4f& WVP);
	void SetTextureUnit(unsigned int TextureUnit);
	
	
private:
	GLuint m_WVPLocation;
	GLuint m_textureLocation;

};




#endif // !SKYBOX_SHADER_MGR_H


