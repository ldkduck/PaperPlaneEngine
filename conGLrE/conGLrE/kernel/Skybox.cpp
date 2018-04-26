#include "Skybox.h"
#include "ogldev_pipeline.h"
#include "ogldev_util.h"

Skybox::Skybox(const Camera* pCamera,
	const PersProjInfo& p)
{
	m_pCamera = pCamera;
	m_pPersProjInfo = p;

	m_pSkyboxShaderMgr = NULL;
	m_pCubemapTex = NULL;
	m_pMesh = NULL;

}

Skybox::~Skybox()
{
	SAFE_DELETE(m_pSkyboxShaderMgr);
	SAFE_DELETE(m_pCubemapTex);
	SAFE_DELETE(m_pMesh);
}

bool Skybox::Init(const string& Directory,
	const string& PosXFilename,
	const string& NegXFilename,
	const string& PosYFilename,
	const string& NegYFilename,
	const string& PosZFilename,
	const string& NegZFilename)
{
	m_pSkyboxShaderMgr = new SkyboxShaderMgr();

	if (!m_pSkyboxShaderMgr->Init()) {
		printf("Error initializing the skybox technique\n");
		return false;
	}

	m_pSkyboxShaderMgr->Enable();
	m_pSkyboxShaderMgr->SetTextureUnit(3);

	m_pCubemapTex = new CubemapTexture(Directory,
		PosXFilename,
		NegXFilename,
		PosYFilename,
		NegYFilename,
		PosZFilename,
		NegZFilename);

	if (!m_pCubemapTex->LoadImageBMP()) {
		return false;
	}
	m_pMesh = new Mesh();

	return m_pMesh->LoadMesh("Resource/Cube.obj");
}

void Skybox::Render()
{
	m_pSkyboxShaderMgr->Enable();

	GLint OldCullFaceMode;
	glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
	GLint OldDepthMode;
	glGetIntegerv(GL_DEPTH_FUNC, &OldDepthMode);

	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);

	Pipeline p;
	p.Scale(1.0f, 1.0f, 1.0f);
	p.Rotate(0.0f, 0.0f, 0.0f);
	//p.WorldPos(0.0f,0.0f,0.0f);
	p.WorldPos(m_pCamera->GetPos().x, m_pCamera->GetPos().y-1.0f, m_pCamera->GetPos().z);
	p.SetCamera(m_pCamera->GetPos(), m_pCamera->GetForwardDir(), m_pCamera->GetUpDir());
	p.SetPerspectiveProj(m_pPersProjInfo);
	m_pSkyboxShaderMgr->SetWVP(p.GetWVPTrans());
	m_pCubemapTex->Bind(GL_TEXTURE3);
	m_pMesh->Render();

	glCullFace(OldCullFaceMode);
	glDepthFunc(OldDepthMode);




}