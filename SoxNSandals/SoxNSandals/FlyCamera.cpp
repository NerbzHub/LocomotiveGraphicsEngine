#include "FlyCamera.h"

FlyCamera::FlyCamera()
{
	//INSERT LOOK AT STUFF FROM THE MAIN
}


FlyCamera::~FlyCamera()
{
}

void FlyCamera::update(float deltaTime, GLFWwindow * a_glfwWindow)
{
	// Calculate delta XY of mouse
	glfwGetCursorPos(a_glfwWindow, &m_dMouseX, &m_dMouseY);
	// Radians to degrees
	m_dDeltaMouseX = (400 - m_dMouseX) * 0.0174533;
	m_dDeltaMouseY = (300 - m_dMouseX) * 0.0174533;

	// Keep mouse locked to screen
	glfwSetCursorPos(a_glfwWindow, 400, 300);

	// Calculate relative world up
	glm::vec4 up = glm::inverse(worldTransform) * glm::vec4(0, 1, 0, 0);
	glm::mat4 rotMat(1.0f);

	// Rotate around world up
	rotMat = glm::rotate((float)-m_dDeltaMouseX * deltaTime, glm::vec3(up[0], up[1], up[2]));
	viewTransform = rotMat * viewTransform;
	// Rotate up down
	rotMat = glm::rotate((float)-m_dDeltaMouseY * deltaTime, glm::vec3(1, 0, 0));
	viewTransform = rotMat * viewTransform;
	// Update world transform
	worldTransform = glm::inverse(viewTransform);

	// Keyboard input
	if (glfwGetKey(a_glfwWindow, GLFW_KEY_W))
	{
		worldTransform[3] += worldTransform[2] * deltaTime * -m_fMovementSpeed;
	}
	if (glfwGetKey(a_glfwWindow, GLFW_KEY_S))
	{
		worldTransform[3] += worldTransform[2] * deltaTime * m_fMovementSpeed;
	}
	if (glfwGetKey(a_glfwWindow, GLFW_KEY_A))
	{
		worldTransform[3] += worldTransform[0] * deltaTime * -m_fMovementSpeed;
	}
	if (glfwGetKey(a_glfwWindow, GLFW_KEY_D))
	{
		worldTransform[3] += worldTransform[2] * deltaTime * m_fMovementSpeed;
	}
	
	worldTransform[3][3] = 1.0f;

	viewTransform = glm::inverse(worldTransform);
	updateProjectionViewTransform();
}

glm::mat4 FlyCamera::getProjectionView()
{
	return projectionViewTransform;
}

void FlyCamera::setSpeed(float speed)
{
	m_fMovementSpeed = speed;
}


