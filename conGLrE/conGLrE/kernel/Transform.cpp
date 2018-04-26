#include "Transform.h"

Transform::Transform()
{

}

bool Transform::Init()
{
	m_pPosition = Vector3f(0.0f, 0.0f, 0.0f);
	m_pRotation = Vector3f(0.0f, 0.0f, 0.0f);
	m_pScale = Vector3f(1.0f, 1.0f, 1.0f);
	return true;
}

void Transform::SetPosition(const Vector3f& pos)
{
	m_pPosition = pos;
}

void Transform::SetRotation(const Vector3f& rot)
{
	
	m_pRotation = rot;
}
void Transform::SetScale(const Vector3f& scale)
{
	
	m_pScale = scale;
	printf("%f\n", m_pScale.x);
}

Vector3f Transform::GetPosition()
{
	return m_pPosition;
}
Vector3f Transform::GetRotation()
{
	return m_pRotation;
}
Vector3f Transform::GetScale()
{
	return m_pScale;
}