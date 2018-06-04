#pragma once
#include "soxCore.h"
#include "Camera.h"



class FlyCamera : public Camera
{
public:
	FlyCamera();
	~FlyCamera();

	void update(double deltaTime, GLFWwindow * a_GLWindow);

	double m_dMouseX;
	double m_dMouseY;

	double deltaMouseX;
	double deltaMouseY;

	float mouseX;
	float mouseY;

	float fMouseSensitivity;

	float fMoveSpeed;
};

