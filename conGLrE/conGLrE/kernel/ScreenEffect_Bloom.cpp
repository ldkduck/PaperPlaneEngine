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

	//������С����bloom�������Լ���Ӧ�Ĵ洢����
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

	//��������blur������֡�������
	
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
	//�˿̣���Ⱦ�������Ѿ������Ƶ�һ��΢�����»������ڣ����еĲ������������������
	////////////////////////////////////////////////////////////

	//��Ҫ����һ�δ����õ�ͼ��ĸ������ֲ�������pingpongFBO1��
	m_shader_highlight->Enable();
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, pingpongFBO[0]);
	m_shader_highlight->SetTextureUnit(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_scaleMap);
	glViewport(0, 0, width / m_shrinkScale, height / m_shrinkScale);
	m_tarMesh->Render();

	////////////////////////////////////////////////////////////
	//Ȼ�����ʮ�κ���/�����ģ��
	int horizontal = 1, first_iteration = true;
	GLuint amount = 32;
	m_shader_blur->Enable();
	m_shader_blur->SetTextureUnit(0);
	//����amount�ε�����ÿ�ν������һ��ģ����Ⱦ
	for (GLuint i = 0; i < amount; i++)
	{
		//���������ƵĻ�������pingpong�������е�ĳһ��,����Ѿ������һ�ε�����ֱ�ӻ��ƻص�scaleFBO
		glBindFramebuffer(
			GL_DRAW_FRAMEBUFFER, (i == (amount-1)) ? m_scaleFBO : pingpongFBO[horizontal]
		);
		//ÿ��Ҫ����horizontal ��״̬��ͬһ����ɫ�����Ը��ݲ�����ͬ���к�����������ģ��
		m_shader_blur->SetBool(horizontal);
		//����ǵ�һ����Ⱦ���õ���Դ��������scaleFBO
		//��Ⱦ��Դ������FBO����ֻ���ö�Ӧ����������
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
	//�������������
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