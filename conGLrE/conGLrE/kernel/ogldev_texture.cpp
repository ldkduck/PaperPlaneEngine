/*

	Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include "ogldev_texture.h"
#include <atlimage.h>
#include <comdef.h> 


static wchar_t *GetWC(const char *c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

Texture::Texture(GLuint texIndex, const char *fileName)
{

	m_textureTarget = GL_TEXTURE_2D;
	m_fileName = GetWC(fileName);
	printf("Load file name %ls\n", m_fileName);
}



bool Texture::LoadImageBMP()
{
	BITMAP bm;
	CImage img;             //需要头文件atlimage.h  
	HRESULT hr = img.Load(m_fileName);
	if (!SUCCEEDED(hr))   //文件加载失败  
	{
		printf("unable to load the bmpfile!");
		//MessageBox(NULL, L"文件加载失败", L"ERROR", 0);
		return NULL;
	}
	HBITMAP hbmp = img;
	if (!GetObject(hbmp, sizeof(bm), &bm))
		return false;

	glGenTextures(1, &m_textureObj);
	if (m_textureObj)
	{
		glBindTexture(GL_TEXTURE_2D, m_textureObj);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glPixelStoref(GL_PACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, bm.bmWidth, bm.bmHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, bm.bmBits); //这里不是GL_RGB  
	}
	return true;
}


void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureObj);
}
