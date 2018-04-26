#ifndef SCREEN_EFFECT_BLOOM_H
#define	SCREEN_EFFECT_BLOOM_H

#include <GL/glew.h>
#include "screen_fbo.h"
#include "Mesh.h"
#include "Shader_Bloom_Highlight.h"
#include "Shader_Bloom_Blur.h"
#include "Shader_Bloom_Add.h"

class ScreenEffect_Bloom
{
public:
	ScreenEffect_Bloom(Mesh* _mesh);

	~ScreenEffect_Bloom();

	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

	void Process(ScreenFBO* _screenFBO);

private:
	Mesh* m_tarMesh;

	//用于提取/输出纹理的缓冲区
	GLuint m_scaleFBO;
	GLuint m_scaleMap;

	//用于blur的缓冲区
	GLuint pingpongFBO[2];
	GLuint pingpongMap[2];

	//bloom纹理缩小倍数
	int m_shrinkScale;

	//width,height
	int height;
	int width;

	//两个用于渲染的shader
	ShaderBloomHighlight* m_shader_highlight;
	ShaderBloomBlur* m_shader_blur;
	ShaderBloomAdd* m_shader_add;

};


#endif	/* SCREEN_MAP_FBO_H */
