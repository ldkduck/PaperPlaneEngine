
#include "Cubemap_Texture.h"
#include "ogldev_texture.h"
#include <iostream>
#include "ogldev_util.h"
#include <atlimage.h>
#include <comdef.h> 
static const GLenum types[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

static wchar_t *GetWC(const char *c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

CubemapTexture::CubemapTexture(const string& Directory,
	const string& PosXFilename,
	const string& NegXFilename,
	const string& PosYFilename,
	const string& NegYFilename,
	const string& PosZFilename,
	const string& NegZFilename)
{
	string::const_iterator it = Directory.end();
	it--;
	string BaseDir = (*it == '/') ? Directory : Directory + "/";
	/*m_fileNames[0] = BaseDir + PosXFilename;
	m_fileNames[1] = BaseDir + NegXFilename;
	m_fileNames[2] = BaseDir + PosYFilename;
	m_fileNames[3] = BaseDir + NegYFilename;
	m_fileNames[4] = BaseDir + PosZFilename;
	m_fileNames[5] = BaseDir + NegZFilename;*/
	m_fileNames[0] = PosXFilename;
	m_fileNames[1] = NegXFilename;
	m_fileNames[2] = PosYFilename;
	m_fileNames[3] = NegYFilename;
	m_fileNames[4] = PosZFilename;
	m_fileNames[5] = NegZFilename;
	m_textureObj = 0;
}

CubemapTexture::~CubemapTexture()
{
	if (m_textureObj != 0)
	{
		glDeleteTextures(1, &m_textureObj);
	}
}

bool CubemapTexture::LoadImageBMP()
{
	glGenTextures(1, &m_textureObj);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);

	
	for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++)
	{
		BITMAP bm;
		CImage img;
		HBITMAP hbmp;
		const char* _fileName = m_fileNames[i].c_str();
		wchar_t* lname = GetWC(_fileName);
		HRESULT hr = img.Load(lname);
		
		if (!SUCCEEDED(hr))   //文件加载失败  
		{
			printf("unable to load the bmpfile!");
			//MessageBox(NULL, L"文件加载失败", L"ERROR", 0);
			return NULL;
		}

		hbmp = img;
		if (!GetObject(hbmp, sizeof(bm), &bm))
			return false;

		if (m_textureObj)
		{
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexImage2D(types[i], 0, 3, bm.bmWidth, bm.bmHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, bm.bmBits); //这里不是GL_RGB 
			
		}
		img.Destroy();
	}

	return true;
}


void CubemapTexture::Bind(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
}