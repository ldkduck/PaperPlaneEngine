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


#include <stdio.h>

#include "screen_fbo.h"

ScreenFBO::ScreenFBO()
{
	m_fbo = 0;
	m_screenMap = 0;
}

ScreenFBO::~ScreenFBO()
{
	if (m_fbo != 0) {
		glDeleteFramebuffers(1, &m_fbo);
	}

	if (m_screenMap != 0) {
		glDeleteTextures(1, &m_screenMap);
	}
}

bool ScreenFBO::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{
	// Create the FBO
	glGenFramebuffers(1, &m_fbo);

	// Create the rgb buffer
	glGenTextures(1, &m_screenMap);
	glBindTexture(GL_TEXTURE_2D, m_screenMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WindowWidth, WindowHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_screenMap, 0);

	//create the depth buffer;
	glGenRenderbuffers(1, &m_screenMap_depth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_screenMap_depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, WindowWidth, WindowHeight);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_screenMap_depth);
	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		printf("FB error, status: 0x%x\n", Status);
		return false;
	}
	return true;
}


void ScreenFBO::BindForWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
}


void ScreenFBO::BindForReading(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, m_screenMap);
}

void ScreenFBO::BindForReading()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
}

GLuint ScreenFBO::GetTexture()
{
	return m_screenMap;
}
