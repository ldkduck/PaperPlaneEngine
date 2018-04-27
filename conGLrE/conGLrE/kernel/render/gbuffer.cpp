#include <stdio.h>

#include "gbuffer.h"
#include "../ogldev_texture.h"
#include "../ogldev_util.h"


GBuffer::GBuffer()
{
	m_fbo = 0;
	m_depthTexture = 0;
	//�Զ�����г�ʼ��������
	ZERO_MEM(m_textures);
}

bool GBuffer::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{
	//����FBO���󶨵�֡�������Բ������֡����
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	
	glGenTextures(ARRAY_SIZE_IN_ELEMENTS(m_textures), m_textures);
	glGenTextures(1, &m_depthTexture);

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_textures); i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, WindowWidth, WindowHeight, 0, GL_RGB, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
	}

	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, WindowWidth, WindowHeight, 0, GL_RGB, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0,
								GL_COLOR_ATTACHMENT1,
								GL_COLOR_ATTACHMENT2,
								GL_COLOR_ATTACHMENT3 };

	//ע�����ﴫ�����һ�����ص�����飬��˼�������Ҫ��������������ݣ�����Ƶ�ָ���Ĺ��ص㡣
	glDrawBuffers(ARRAY_SIZE_IN_ELEMENTS(DrawBuffers), DrawBuffers);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("error,status : 0x%x\n", Status);

	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	return true;

}