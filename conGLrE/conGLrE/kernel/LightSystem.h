#ifndef  LIGHT_SYSTEM_H
#define  LIGHT_SYSTEM_H

#include "ogldev_lights_common.h"
#include "ogldev_shadow_map_fbo.h"

class LightSystem
{
public:
	LightSystem();
	~LightSystem();
	//�ƹ����
	DirectionalLight m_directionalLight;
	SpotLight m_spotLight;
	//��Ӱ֡�������
	ShadowMapFBO* m_shadowMapFBO;
	//ͶӰ
	PersProjInfo m_ShadowProjInfo;
	OrthoProjInfo m_DirecShadowProjInfo;
private:
	
};



#endif // ! LIGHT_SYSTEM_H
