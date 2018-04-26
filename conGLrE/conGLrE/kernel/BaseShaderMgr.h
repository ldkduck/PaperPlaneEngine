#pragma once
#ifndef BASE_SHADER_MGR_H
#define BASE_SHADER_MGR_H

#include "ShaderManager.h"
#include "ogldev_math_3d.h"

class BaseShaderMgr : public ShaderManager
{
public:
	BaseShaderMgr();

	virtual bool Init();

	void SetWVP(const Matrix4f& WVP);
	void SetTextureUnit(unsigned int TextureUnit);
private:
	GLuint m_WVPLocation;
	GLuint m_samplerLocation;


};




#endif // !LIGHT_SHADER_MGR_H


