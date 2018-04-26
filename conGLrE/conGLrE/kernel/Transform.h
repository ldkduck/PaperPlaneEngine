#ifndef  TRANSFORM_H
#define  TRANSFORM_H


#include "ogldev_math_3d.h"
#include "ogldev_lights_common.h"
#include "ogldev_texture.h"
class Transform
{
public:

	Transform();

	bool Init();

	void SetPosition(const Vector3f& pos);
	void SetRotation(const Vector3f& rot);
	void SetScale(const Vector3f& scale);

	Vector3f GetPosition();
	Vector3f GetRotation();
	Vector3f GetScale();

private:
	Vector3f m_pPosition;
	Vector3f m_pRotation;
	Vector3f m_pScale;
};





#endif 

