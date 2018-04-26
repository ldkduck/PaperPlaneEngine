#ifndef CUBEMAP_TEXTURE_H
#define	CUBEMAP_TEXTURE_H

#include <string>
#include <GL/glew.h>

using namespace std;
class CubemapTexture
{
public:
	CubemapTexture(const string& Directory,
		const string& PosXFilename,
		const string& NegXFilename,
		const string& PosYFilename,
		const string& NegYFilename,
		const string& PosZFilename,
		const string& NegZFilename);

	~CubemapTexture();

	bool LoadImageBMP();

	void Bind(GLenum TextureUnit);

private:

	string m_fileNames[6];
	GLuint m_textureObj;
};

#endif