#ifndef  LIGHT_SYSTEM_H
#define  LIGHT_SYSTEM_H

#include "ogldev_lights_common.h"
#include "ogldev_shadow_map_fbo.h"

class LightSystem
{
public:
	LightSystem();
	~LightSystem();
	//灯光对象
	DirectionalLight m_directionalLight;
	SpotLight m_spotLight;
	//阴影帧缓冲对象
	ShadowMapFBO* m_shadowMapFBO;
	//投影
	PersProjInfo m_ShadowProjInfo;
	OrthoProjInfo m_DirecShadowProjInfo;
private:
	
};



#endif // ! LIGHT_SYSTEM_H
