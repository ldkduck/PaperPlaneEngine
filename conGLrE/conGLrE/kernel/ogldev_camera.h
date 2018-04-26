/*

	Copyright 2010 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CAMERA_H
#define	CAMERA_H

#include "ogldev_math_3d.h"
#include "ogldev_keys.h"
#include "ogldev_atb.h"

class Camera
{
public:

    Camera(int WindowWidth, int WindowHeight);

    Camera(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up);

    bool OnKeyboard(OGLDEV_KEY Key);

    void OnMouse(int x, int y);

    void OnEnter();

    const Vector3f& GetPos() const
    {
        return m_pos;
    }

    const Vector3f& GetForwardDir() const
    {
		return m_dir_forward;
    }

    const Vector3f& GetUpDir() const
    {
        return m_dir_up;
    }
	void SetProjInfo(PersProjInfo pInfo);
	PersProjInfo GetPersProj();
	void SetRight(bool b);
	void SetLeft(bool b);
	void SetForward(bool b);
	void SetBackward(bool b);
	void ActiveMouseRotation(bool b);
    void AddToATB(TwBar* bar);

private:

    void Init();
    void Update();

	PersProjInfo m_projInfo;

	float StepSize;
    Vector3f m_pos;
    Vector3f m_target;
	Vector3f m_dir_forward;
    Vector3f m_dir_up;

    int m_windowWidth;
    int m_windowHeight;

    float m_AngleH;
    float m_AngleV;

    bool m_OnUpperEdge;
    bool m_OnLowerEdge;
    bool m_OnLeftEdge;
    bool m_OnRightEdge;

	bool m_right;
	bool m_left;
	bool m_forward;
	bool m_backward;

	bool m_mouseRotate;
	int m_screenCenterX;
	int m_screenCenterY;
    Vector2i m_mousePos;
};

#endif	/* CAMERA_H */

