#pragma once
#ifndef  SKY_BOX_MATERIAL
#define  SKY_BOX_MATERIAL

#include "ogldev_camera.h"
#include "Mesh.h"
#include "SkyboxShaderMgr.h"
#include "Cubemap_Texture.h"
class Skybox
{
public:
	Skybox(const Camera* pCamera, const PersProjInfo& p);

	~Skybox();

	bool Init(const string& Directory,
		const string& PosXFilename,
		const string& NegXFilename,
		const string& PosYFilename,
		const string& NegYFilename,
		const string& PosZFilename,
		const string& NegZFilename);

	void Render();

private:
	SkyboxShaderMgr* m_pSkyboxShaderMgr;
	const Camera* m_pCamera;
	CubemapTexture* m_pCubemapTex;
	Mesh* m_pMesh;
	PersProjInfo m_pPersProjInfo;


};



#endif // ! SKY_BOX_MATERIAL


