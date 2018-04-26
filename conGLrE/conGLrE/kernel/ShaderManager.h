#ifndef SHADER_MANAGER_H
#define	SHADER_MANAGER_H

#include <list>
#include <GL/glew.h>
#include "ogldev_camera.h"
#include "Transform.h"
#include "LightSystem.h"


class ShaderManager
{
public:

	ShaderManager();

	~ShaderManager();

	virtual bool Init();
	virtual void UpdateRenderInfo(Transform trans, Camera* cam, LightSystem* light);
	void Enable();

protected:

	bool AddShader(GLenum ShaderType, const char* pShaderText);

	bool Finalize();

	GLint GetUniformLocation(const char* pUniformName);

private:

	GLuint m_shaderProg;

	typedef std::list<GLuint> ShaderObjList;
	ShaderObjList m_shaderObjList;
};

#endif 