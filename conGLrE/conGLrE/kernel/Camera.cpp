#include "ogldev_camera.h"
#include <Windows.h>
#include <glut.h>
const static float STEP_SCALE = 1.0f;
const static float EDGE_STEP = 0.5f;
const static int MARGIN = 10;

Camera::Camera(int WindowWidth, int WindowHeight)
{
	m_windowWidth = WindowWidth;
	m_windowHeight = WindowHeight;
	m_pos = Vector3f(0.0f, 0.0f, -3.0f);
	m_target = Vector3f(0.0f, 0.0f, 0.0f);
	m_dir_forward = Vector3f(0.0f,0.0f, 1.0f);
	m_dir_forward.Normalize();
	m_dir_up = Vector3f(0.0f, 1.0f, 0.0f);

	m_right = false;
	m_left = false;
	m_forward = false;
	m_backward = false;
	//tempdata for stepsize 
	StepSize = 0.1f;

	m_mouseRotate = false;
	SetCursorPos(100, 100);

	Init();
}

void Camera::SetProjInfo(PersProjInfo pInfo)
{
	m_projInfo = pInfo;
}

PersProjInfo Camera::GetPersProj()
{
	return m_projInfo;
}

void Camera::Init()
{
	Vector3f HTarget(m_dir_forward.x, 0.0, m_dir_forward.z);
	HTarget.Normalize();

	if (HTarget.z >= 0.0f)
	{
		if (HTarget.x >= 0.0f)
		{
			m_AngleH = 360.0f - ToDegree(asin(HTarget.z));
		}
		else
		{
			m_AngleH = 180.0f + ToDegree(asin(HTarget.z));
		}
	}
	else
	{
		if (HTarget.x >= 0.0f)
		{
			m_AngleH = ToDegree(asin(-HTarget.z));
		}
		else
		{
			m_AngleH = 180.0f - ToDegree(asin(-HTarget.z));
		}
	}

	m_AngleV = -ToDegree(asin(m_dir_forward.y));

	m_OnUpperEdge = false;
	m_OnLowerEdge = false;
	m_OnLeftEdge = false;
	m_OnRightEdge = false;
	m_mousePos.x = m_windowWidth / 2;
	m_mousePos.y = m_windowHeight / 2;
}



void Camera::SetRight(bool b)
{
	m_right = b;
}
void Camera::SetLeft(bool b)
{
	m_left = b;
}
void Camera::SetForward(bool b)
{
	m_forward = b;
}
void Camera::SetBackward(bool b)
{
	m_backward = b;
}

void Camera::ActiveMouseRotation(bool b)
{
	m_mouseRotate = b;
}

void Camera::OnEnter()
{
	if (m_mouseRotate) {
		ShowCursor(false);
		int startX = glutGet(GLUT_WINDOW_X); //获得当前显示窗口左上角相对于屏幕左上角的x坐标位置。GLUT_WINDOW_WIDTH获得当前显示窗口宽度，GLUT_SCREEN_WIDTH获得屏幕宽度。
		int startY = glutGet(GLUT_WINDOW_Y);
		int curWidth = glutGet(GLUT_WINDOW_WIDTH);
		int curHeight = glutGet(GLUT_WINDOW_HEIGHT);
		m_screenCenterX = startX + curWidth / 2;
		m_screenCenterY = startY + curHeight / 2;
		SetCursorPos(m_screenCenterX, m_screenCenterY);
	}
	else
	{
		ShowCursor(true);
	}
	
	if (m_left && !m_right)
	{
		Vector3f Left = m_dir_forward.Cross(m_dir_up);	
		Left.Normalize();
		Left *= StepSize;
		m_pos += Left;
	}
	if (!m_left && m_right)
	{
		Vector3f Right = m_dir_up.Cross(m_dir_forward);
		Right.Normalize();
		Right *= StepSize;
		m_pos += Right;
	}
	if (m_forward && !m_backward)
	{
		Vector3f forward = m_dir_forward;
		forward.Normalize();
		forward *= StepSize;
		m_pos += forward;
	}
	if (!m_forward && m_backward)
	{
		Vector3f backward = m_dir_forward;
		backward.Normalize();
		backward *= StepSize;
		m_pos -= backward;
	}
	
}

void Camera::OnMouse(int x, int y)
{
	if (!m_mouseRotate)
		return;
	//取每一帧鼠标的偏移量
	const int DeltaX = x - glutGet(GLUT_WINDOW_WIDTH)/2;
	const int DeltaY = y - glutGet(GLUT_WINDOW_HEIGHT)/2;

	//转化成水平/垂直方向的角度偏移
	m_AngleH += (float)DeltaX / 20.0f;
	m_AngleV += (float)DeltaY / 20.0f;

	if (DeltaX == 0) {
		if (x <= MARGIN) {
			m_OnLeftEdge = true;
		}
		else if (x >= (m_windowWidth - MARGIN)) {
			m_OnRightEdge = true;
		}
	}
	else {
		m_OnLeftEdge = false;
		m_OnRightEdge = false;
	}

	if (DeltaY == 0) {
		if (y <= MARGIN) {
			m_OnUpperEdge = true;
		}
		else if (y >= (m_windowHeight - MARGIN)) {
			m_OnLowerEdge = true;
		}
	}
	else {
		m_OnUpperEdge = false;
		m_OnLowerEdge = false;
	}

	Update();
}

void Camera::Update()
{
	const Vector3f Vaxis(0.0f, 1.0f, 0.0f);

	// Rotate the view vector by the horizontal angle around the vertical axis
	Vector3f View(1.0f, 0.0f, 0.0f);
	View.Rotate(m_AngleH, Vaxis);
	View.Normalize();

	// Rotate the view vector by the vertical angle around the horizontal axis
	Vector3f Haxis = Vaxis.Cross(View);
	Haxis.Normalize();
	View.Rotate(m_AngleV, Haxis);

	m_dir_forward = View;
	m_dir_forward.Normalize();

	m_dir_up = m_dir_forward.Cross(Haxis);
	m_dir_up.Normalize();
}