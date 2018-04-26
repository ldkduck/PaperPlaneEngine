#include <stdio.h>
#include "ScreenEffect_Bloom.h"

ScreenEffect_Bloom::ScreenEffect_Bloom(Mesh* _mesh)
{
	m_tarMesh = _mesh;
	m_shrinkScale = 2;

	m_shader_highlight = new ShaderBloomHighlight();
	m_shader_highlight->Init();
	m_shader_blur = new ShaderBloomBlur();
	m_shader_blur->Init();
	m_shader_add = new ShaderBloomAdd();
	m_shader_add->Init();
}

ScreenEffect_Bloom::~ScreenEffect_Bloom()
{
}

bool ScreenEffect_Bloom::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{
	

	width = WindowWidth;
	height = WindowHeight;

	//创建缩小化的bloom缓冲区以及对应的存储纹理
	glGenFramebuffers(1, &m_scaleFBO);
	glGenTextures(1, &m_scaleMap);
	glBindTexture(GL_TEXTURE_2D, m_scaleMap);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGB16F, WindowWidth / m_shrinkScale, WindowHeight / m_shrinkScale, 0, GL_RGB, GL_FLOAT, NULL
	);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_scaleFBO);
	glFramebufferTexture2D(
		GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_scaleMap, 0
	);

	//创建用于blur的两个帧缓冲对象
	
	glGenFramebuffers(2, pingpongFBO);
	glGenTextures(2, pingpongMap);
	for (GLuint i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongMap[i]);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGB16F, WindowWidth / m_shrinkScale, WindowHeight / m_shrinkScale, 0, GL_RGB, GL_FLOAT, NULL
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(
			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongMap[i], 0
		);
	}

	return true;
}

void ScreenEffect_Bloom::Process(ScreenFBO* _screenFBO)
{
	/////////////////////////////////////////////////////////////
	_screenFBO->BindForReading();
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_scaleFBO);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glBlitFramebuffer(0, 0, width, height,
					0, 0, width / m_shrinkScale, height / m_shrinkScale,
					GL_COLOR_BUFFER_BIT, GL_LINEAR);
	//此刻，渲染的内容已经被复制到一个微缩的新缓冲区内，所有的操作对这个缓冲区进行
	////////////////////////////////////////////////////////////

	//先要进行一次处理，得到图像的高亮部分并保存在pingpongFBO1中
	m_shader_highlight->Enable();
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, pingpongFBO[0]);
	m_shader_highlight->SetTextureUnit(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_scaleMap);
	glViewport(0, 0, width / m_shrinkScale, height / m_shrinkScale);
	m_tarMesh->Render();

	////////////////////////////////////////////////////////////
	//然后进行十次横向/纵向的模糊
	int horizontal = 1, first_iteration = true;
	GLuint amount = 32;
	m_shader_blur->Enable();
	m_shader_blur->SetTextureUnit(0);
	//进行amount次迭代，每次交错进行一次模糊渲染
	for (GLuint i = 0; i < amount; i++)
	{
		//即将被绘制的缓冲区是pingpong缓冲区中的某一个,如果已经是最后一次迭代，直接绘制回到scaleFBO
		glBindFramebuffer(
			GL_DRAW_FRAMEBUFFER, (i == (amount-1)) ? m_scaleFBO : pingpongFBO[horizontal]
		);
		//每次要更新horizontal 的状态，同一个着色器可以根据参数不同进行横向或者纵向的模糊
		m_shader_blur->SetBool(horizontal);
		//如果是第一次渲染，用到的源纹理来自scaleFBO
		//渲染的源不能是FBO对象，只能用对应的那张纹理
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(
			GL_TEXTURE_2D, pingpongMap[!horizontal]
		);
		glViewport(0, 0, width / m_shrinkScale, height / m_shrinkScale);
		m_tarMesh->Render();
		horizontal = (horizontal == 0 ? 1 : 0);
	}
	glViewport(0, 0, width , height );
	///////////////////////////////////////////////////////////////////
	//最后将两个纹理混合
	m_shader_add->Enable();
	_screenFBO->BindForWriting();
	m_shader_add->SetSrcTexture(0);
	m_shader_add->SetBlurTexture(1);
	_screenFBO->BindForReading(GL_TEXTURE0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, pingpongMap[0]);

	m_tarMesh->Render();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}