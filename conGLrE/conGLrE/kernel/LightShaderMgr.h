#ifndef LIGHT_SHADER_MGR_H
#define LIGHT_SHADER_MGR_H


#include "ogldev_math_3d.h"
#include "ogldev_lights_common.h"
#include "ShaderManager.h"
#include "Material.h"



class LightShaderMgr : public ShaderManager
{
public:
	static const unsigned int MAX_POINT_LIGHT = 2;
	static const unsigned int MAX_SPOT_LIGHT = 2;

	LightShaderMgr();

	virtual bool Init();
	virtual void UpdateRenderInfo(Transform trans,Camera* cam,LightSystem* light);

	bool BindShaderAttrib();

	void SetWVP(const Matrix4f& WVP);
	void SetLightWVP(const Matrix4f& LightWVP);
	void SetWorldMatrix(const Matrix4f& WVP);
	void SetReflectTextureUnit(unsigned int TexutureUnit);
	void SetTextureUnit(unsigned int TextureUnit);
	void SetNormalTextureUnit(unsigned int normalTexUnit);
	void SetShadowMapTextureUnit(unsigned int TextureUnit);
	void SetDirectionalLight(const DirectionalLight& Light);
	void SetPointLights(unsigned int NumLights, const PointLight* pLights);
	void SetSpotLights(unsigned int NumLights, const SpotLight* pLights);
	void SetEyeWorldPos(const Vector3f& EyeWorldPos);
	void SetMatSpecularIntensity(float Intensity);
	void SetMatSpecularPower(float Power);
	void SetTexScale(const Vector2f& texScale);
private :
	GLuint m_textureScaleLocation;

	GLuint m_WVPLocation;
	GLuint m_LightWVPLocation;
	GLuint m_WorldMatrixLocation;
	GLuint m_samplerLocation;
	GLuint m_normalSamplerLocation;
	GLuint m_shadowMapLocation;
	GLuint m_textureLocation;
	GLuint m_eyeWorldPosLocation;
	GLuint m_matSpecularIntensityLocation;
	GLuint m_matSpecularPowerLocation;
	GLuint m_numPointLightsLocation;
	GLuint m_numSpotLightsLocation;


	struct {
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint DiffuseIntensity;
		GLuint Direction;
	} m_dirLightLocation;

	struct {
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint DiffuseIntensity;
		GLuint Position;
		struct {
			GLuint Constant;
			GLuint Linear;
			GLuint Exp;
		} Atten;
	} m_pointLightsLocation[2];

	struct {
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint DiffuseIntensity;
		GLuint Position;
		GLuint Direction;
		GLuint Cutoff;
		struct {
			GLuint Constant;
			GLuint Linear;
			GLuint Exp;
		} Atten;
	} m_spotLightsLocation[2];
};




#endif // !LIGHT_SHADER_MGR_H


