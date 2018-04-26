#include "LightShaderMgr.h"
#include "ogldev_pipeline.h"

LightShaderMgr::LightShaderMgr()
{

}

//每一套shader有不同的参数，在继承基类加载函数的基础上，
//子类负责确定具体shader有哪些参数，先把接口找到。
bool LightShaderMgr::Init()
{
	if (!ShaderManager::Init()) {
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "lighting.vs"))
	{
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "lighting.fs"))
	{
		return false;
	}

	if (!Finalize())
	{
		return false;
	}

	BindShaderAttrib();
	

	return true;

}

bool LightShaderMgr::BindShaderAttrib()
{
	m_textureScaleLocation = GetUniformLocation("gTexScale");
	m_WVPLocation = GetUniformLocation("gWVP");
	m_LightWVPLocation = GetUniformLocation("gLightWVP");
	m_WorldMatrixLocation = GetUniformLocation("gWorld");
	m_samplerLocation = GetUniformLocation("gSampler");
	m_normalSamplerLocation = GetUniformLocation("gNormalMap");
	m_shadowMapLocation = GetUniformLocation("gShadowMap");
	m_textureLocation = GetUniformLocation("gCubemapTexture");
	m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
	m_dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Base.Color");
	m_dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
	m_dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
	m_dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
	m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
	m_matSpecularPowerLocation = GetUniformLocation("gSpecularPower");
	m_numPointLightsLocation = GetUniformLocation("gNumPointLights");
	m_numSpotLightsLocation = GetUniformLocation("gNumSpotLights");

	if (m_dirLightLocation.AmbientIntensity == INVALID_UNIFORM_LOCATION ||
		m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_LightWVPLocation == INVALID_UNIFORM_LOCATION ||
		m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
		m_samplerLocation == INVALID_UNIFORM_LOCATION ||
		m_shadowMapLocation == INVALID_UNIFORM_LOCATION ||
		m_eyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
		m_dirLightLocation.Color == INVALID_UNIFORM_LOCATION ||
		m_dirLightLocation.DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
		m_dirLightLocation.Direction == INVALID_UNIFORM_LOCATION ||
		m_matSpecularIntensityLocation == INVALID_UNIFORM_LOCATION ||
		m_matSpecularPowerLocation == INVALID_UNIFORM_LOCATION ||
		m_numPointLightsLocation == INVALID_UNIFORM_LOCATION ||
		m_numSpotLightsLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}


	for (uint i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_pointLightsLocation); i++) {
		char Name[128];
		memset(Name, 0, sizeof(Name));
		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.Color", i);
		m_pointLightsLocation[i].Color = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.AmbientIntensity", i);
		m_pointLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Position", i);
		m_pointLightsLocation[i].Position = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.DiffuseIntensity", i);
		m_pointLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Constant", i);
		m_pointLightsLocation[i].Atten.Constant = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Linear", i);
		m_pointLightsLocation[i].Atten.Linear = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Exp", i);
		m_pointLightsLocation[i].Atten.Exp = GetUniformLocation(Name);

		if (m_pointLightsLocation[i].Color == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].AmbientIntensity == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].Position == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].Atten.Constant == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].Atten.Linear == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].Atten.Exp == INVALID_UNIFORM_LOCATION) {
			return false;
		}
	}

	for (uint i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_spotLightsLocation); i++) {
		char Name[128];
		memset(Name, 0, sizeof(Name));
		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.Color", i);
		m_spotLightsLocation[i].Color = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.AmbientIntensity", i);
		m_spotLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Position", i);
		m_spotLightsLocation[i].Position = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Direction", i);
		m_spotLightsLocation[i].Direction = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Cutoff", i);
		m_spotLightsLocation[i].Cutoff = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.DiffuseIntensity", i);
		m_spotLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Constant", i);
		m_spotLightsLocation[i].Atten.Constant = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Linear", i);
		m_spotLightsLocation[i].Atten.Linear = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Exp", i);
		m_spotLightsLocation[i].Atten.Exp = GetUniformLocation(Name);

		if (m_spotLightsLocation[i].Color == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].AmbientIntensity == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Position == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Direction == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Cutoff == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Atten.Constant == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Atten.Linear == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Atten.Exp == INVALID_UNIFORM_LOCATION) {
			return false;
		}
	}
}

//该函数用于在渲染之前设定必要的更新数据
void LightShaderMgr::UpdateRenderInfo(Transform trans,Camera* cam,LightSystem* light)
{
	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//启用当前着色器
	Enable();

	//设置高光反射系统
	SetMatSpecularIntensity(10.0f);
	//数值越高表面越光滑
	SetMatSpecularPower(512);
	SetReflectTextureUnit(3);

	//绑定着色器中漫反射纹理在纹理单元中的位置
	SetTextureUnit(0);

	//绑定着色器中法线纹理在纹理单元中的位置
	SetNormalTextureUnit(2);

	//绑定着色器中阴影反射纹理在纹理单元中的位置
	SetShadowMapTextureUnit(1);

	//设定相机世界坐标位置
	SetEyeWorldPos(cam->GetPos());
	//bind
	light->m_shadowMapFBO->BindForReading(GL_TEXTURE1);
	//设定光照信息
	SetDirectionalLight(light->m_directionalLight);
	//SetSpotLights(1, &(light->m_spotLight));

	//设定transform
	/////////////////////////////////////////////////////////////////////////////////
	Pipeline p;
	p.SetPerspectiveProj(cam->GetPersProj());
	p.Scale(trans.GetScale().x,trans.GetScale().y,trans.GetScale().z);
	p.WorldPos(trans.GetPosition().x, trans.GetPosition().y, trans.GetPosition().z);
	p.Rotate(trans.GetRotation().x, trans.GetRotation().y, trans.GetRotation().z);
	p.SetCamera(cam->GetPos(), cam->GetForwardDir(), cam->GetUpDir());
	//发送MVP矩阵
	SetWVP(p.GetWVPTrans());
	//发送M矩阵
	SetWorldMatrix(p.GetWorldTrans());
	//////////////////////////////////////////////////////////////////////////////////
	
	//设置并发送阴影纹理矩阵
	/////////////////////////////////////////////////////////////////////////////////
	p.SetOrthographicProj(light->m_DirecShadowProjInfo);
	p.SetCamera(Vector3f(light->m_directionalLight.Direction.x * -10, light->m_directionalLight.Direction.y * -10, light->m_directionalLight.Direction.z * -10), light->m_directionalLight.Direction, Vector3f(0.0f, 1.0f, 0.0f));
	
	SetLightWVP(p.GetWVOrthoPTrans());

	
	/////////////////////////////////////////////////////////////////////////////////

	//发送纹理缩放比例
	SetTexScale(Vector2f(1.0f,1.0f));
}

void LightShaderMgr::SetWVP(const Matrix4f& WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}


void LightShaderMgr::SetLightWVP(const Matrix4f& LightWVP)
{
	glUniformMatrix4fv(m_LightWVPLocation, 1, GL_TRUE, (const GLfloat*)LightWVP.m);
}


void LightShaderMgr::SetWorldMatrix(const Matrix4f& WorldInverse)
{
	glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)WorldInverse.m);
}

void LightShaderMgr::SetReflectTextureUnit(uint TexutureUnit)
{
	glUniform1i(m_textureLocation, TexutureUnit);
}

void LightShaderMgr::SetTextureUnit(uint TextureUnit)
{
	glUniform1i(m_samplerLocation, TextureUnit);
}


void LightShaderMgr::SetNormalTextureUnit(uint normalTexUnit)
{
	glUniform1i(m_normalSamplerLocation, normalTexUnit);
}

void LightShaderMgr::SetShadowMapTextureUnit(uint TextureUnit)
{
	glUniform1i(m_shadowMapLocation, TextureUnit);
}


void LightShaderMgr::SetDirectionalLight(const DirectionalLight& Light)
{
	glUniform3f(m_dirLightLocation.Color, Light.Color.x, Light.Color.y, Light.Color.z);
	glUniform1f(m_dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
	Vector3f Direction = Light.Direction;
	Direction.Normalize();
	glUniform3f(m_dirLightLocation.Direction, Direction.x, Direction.y, Direction.z);
	glUniform1f(m_dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
}

void LightShaderMgr::SetTexScale(const Vector2f& texScale)
{
	glUniform2f(m_textureScaleLocation, texScale.x, texScale.y);
}


void LightShaderMgr::SetEyeWorldPos(const Vector3f& EyeWorldPos)
{
	glUniform3f(m_eyeWorldPosLocation, EyeWorldPos.x, EyeWorldPos.y, EyeWorldPos.z);
}


void LightShaderMgr::SetMatSpecularIntensity(float Intensity)
{
	glUniform1f(m_matSpecularIntensityLocation, Intensity);
}


void LightShaderMgr::SetMatSpecularPower(float Power)
{
	glUniform1f(m_matSpecularPowerLocation, Power);
}


void LightShaderMgr::SetPointLights(uint NumLights, const PointLight* pLights)
{
	glUniform1i(m_numPointLightsLocation, NumLights);

	for (uint i = 0; i < NumLights; i++) {
		glUniform3f(m_pointLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
		glUniform1f(m_pointLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
		glUniform1f(m_pointLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
		glUniform3f(m_pointLightsLocation[i].Position, pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
		glUniform1f(m_pointLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
		glUniform1f(m_pointLightsLocation[i].Atten.Linear, pLights[i].Attenuation.Linear);
		glUniform1f(m_pointLightsLocation[i].Atten.Exp, pLights[i].Attenuation.Exp);
	}
}


void LightShaderMgr::SetSpotLights(uint NumLights, const SpotLight* pLights)
{
	glUniform1i(m_numSpotLightsLocation, NumLights);

	for (uint i = 0; i < NumLights; i++) {
		glUniform3f(m_spotLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
		glUniform1f(m_spotLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
		glUniform1f(m_spotLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
		glUniform3f(m_spotLightsLocation[i].Position, pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
		Vector3f Direction = pLights[i].Direction;
		Direction.Normalize();
		glUniform3f(m_spotLightsLocation[i].Direction, Direction.x, Direction.y, Direction.z);
		glUniform1f(m_spotLightsLocation[i].Cutoff, cosf(ToRadian(pLights[i].Cutoff)));
		glUniform1f(m_spotLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
		glUniform1f(m_spotLightsLocation[i].Atten.Linear, pLights[i].Attenuation.Linear);
		glUniform1f(m_spotLightsLocation[i].Atten.Exp, pLights[i].Attenuation.Exp);
	}
}