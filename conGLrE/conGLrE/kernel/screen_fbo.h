#ifndef SCREEN_FBO_H
#define	SCREEN_FBO_H

#include <GL/glew.h>

class ScreenFBO
{
public:
	ScreenFBO();

	~ScreenFBO();

	bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

	void BindForWriting();
	void BindForReading(GLenum TextureUnit);
	void BindForReading();
	GLuint GetTexture();
private:
	GLuint m_fbo;
	GLuint m_screenMap;
	GLuint m_screenMap_depth;
};


#endif	/* SCREEN_MAP_FBO_H */
