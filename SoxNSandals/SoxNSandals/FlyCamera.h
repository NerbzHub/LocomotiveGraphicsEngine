#pragma once
#include "soxCore.h"
#include "Camera.h"



class FlyCamera : public Camera
{
public:
	FlyCamera();
	~FlyCamera();

	void update(float deltaTime, GLFWwindow* a_glfwWindow);


	glm::mat4 getProjectionView();
	void setSpeed(float speed);

protected:
	// wasd motion
	float m_fMovementSpeed;
	//Mouse look snsitivity
	float m_fMouseSpeed;
	// to rotate around
	glm::vec3 m_v3up;

	// x and y mouse
	double m_dMouseX;
	double m_dMouseY;

	// delta XY for calculating how far to turn this frame
	double m_dDeltaMouseX;
	double m_dDeltaMouseY;
};

