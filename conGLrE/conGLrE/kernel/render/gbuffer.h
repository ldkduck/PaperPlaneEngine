#ifndef GBUFFER_H
#define GBUFFER_H

#include <GL\glew.h>

#pragma once

#define GBUFFER_POSITION_TEXTURE_UNIT	0
#define GBUFFER_DIFFUSE_TEXTURE_UNIT	1
#define GBUFFER_NORMAL_TEXTURE_UNIT		2
#define GBUFFER_TEXCOORD_TEXTURE_UNIT	3

class GBuffer
{
public:
	enum GBUFFER_TEXTURE_TYPE {
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_DIFFUSE,
		GBUFFER_TEXTURE_NORMAL,
		GBUFFER_TEXTURE_TEXCOORD,
		GBUFFER_NUM_TEXTURES

	};
	
	GBuffer();
	~GBuffer();

	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
	void BindForWriting();
	void BindForReading();

	void SetReadBuffer(GBUFFER_TEXTURE_TYPE textureType);

private:
	GLuint m_fbo;
	GLuint m_textures[GBUFFER_NUM_TEXTURES];
	GLuint m_depthTexture;

};













#endif
